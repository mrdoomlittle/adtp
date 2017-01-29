# include "io.h"

uint8_t init(struct io * __io, uint_t __ibuff_length, uint_t __obuff_length) {
	if (__io-> already_inited) return 1;

	__io-> dati_buff = (uint8_t *)malloc(__ibuff_length);
	memset(__io-> dati_buff, 0x0, __ibuff_length);

	__io-> ibuff_length = __ibuff_length;

	__io-> dato_buff = (uint8_t *)malloc(__obuff_length);
	memset(__io-> dato_buff, 0x0, __obuff_length);

	__io-> obuff_length = __obuff_length;

	__io-> set_pmode_fptr(DIGITAL_IN, TMP_ICLK_PID);
	__io-> set_pmode_fptr(DIGITAL_IN, TMP_OCLK_PID);

	__io-> set_pmode_fptr(DIGITAL_IN, TMP_DATI_PID);
	__io-> set_pmode_fptr(DIGITAL_OUT, TMP_DATO_PID);

	__io-> set_pmode_fptr(DIGITAL_OUT, TMP_RSEND_PID);
	__io-> set_pmode_fptr(DIGITAL_OUT, TMP_RRECV_PID);

	__io-> set_pmode_fptr(DIGITAL_IN, TMP_SINIT_PID);

	__io-> ibuff_point = 0;
	__io-> cc_till_read = TMP_RHOLDUP_CC;
	__io-> is_iclk_ready = false;
	__io-> reading_idat = false;
	__io-> idat_bpoint = 0;

	__io-> obuff_point = 0;
	__io-> cc_till_write = TMP_WHOLDUP_CC;
    __io-> is_oclk_ready = false;
    __io-> writing_odat = false;
    __io-> odat_bpoint = 0;

	__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_DATO_PID);

	__io-> set_pstate_fptr(DIGITAL_LOW, TMP_RSEND_PID);
	__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_RRECV_PID);

# ifdef F_CPU
	for (;;) {
		if (__io-> get_pstate_fptr(TMP_SINIT_PID) == DIGITAL_HIGH) break;
		if (__io-> get_pstate_fptr(TMP_ICLK_PID) == DIGITAL_HIGH)
		{
			__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_RSEND_PID);
			if (__io-> get_pstate_fptr(TMP_OCLK_PID) == DIGITAL_HIGH)
			{
				_delay_ms(100);
				__io-> set_pstate_fptr(DIGITAL_LOW, TMP_RSEND_PID);
				__io-> set_pstate_fptr(DIGITAL_LOW, TMP_RRECV_PID);

				break;
			}
		}
	}
# endif

	if (! __io-> already_inited)
		__io-> already_inited = true;

	return 0;
}

bool is_iclk_pstate(struct io * __io, uint8_t __is_t) {
	return __io-> get_pstate_fptr(TMP_ICLK_PID) == __is_t? true : false;
}

bool is_oclk_pstate(struct io * __io, uint8_t __is_t) {
	return __io-> get_pstate_fptr(TMP_OCLK_PID) == __is_t? true : false;
}

uint8_t tick(struct io * __io)
{
	if (is_iclk_pstate(__io, DIGITAL_LOW)) __io-> is_iclk_ready = true;

	if (is_iclk_pstate(__io, DIGITAL_HIGH) && __io-> is_iclk_ready)
	{
		if (__io-> ibuff_point != __io-> ibuff_length)
		{
			if (__io-> cc_till_read == 0)
			{
				if (__io-> reading_idat)
				{
					uint_t dhigh_count = 0, dlow_count = 0;
					uint8_t in = 0;

					for (size_t i = 0; i != TMP_IRRANGE; i ++) {
						in = __io-> get_pstate_fptr(TMP_DATI_PID);
						if (in == DIGITAL_HIGH) {
							dhigh_count++;
						}
						if (in == DIGITAL_LOW) {
							dlow_count++;
						}
					}

					in = dhigh_count > dlow_count? DIGITAL_HIGH : DIGITAL_LOW;

					__io-> dati_buff[__io-> ibuff_point] |= in << __io-> idat_bpoint;

					if (__io-> idat_bpoint == 7)
					{
						__io-> reading_idat = false;
						__io-> idat_bpoint = 0;
					}
					else
						__io-> idat_bpoint ++;
				}
				else
				{
					__io-> ibuff_point ++;
					__io-> reading_idat = true;
				}

				__io-> cc_till_read = TMP_RHOLDUP_CC;
			} else
				__io-> cc_till_read --;
		}

		__io-> is_iclk_ready = false;
	}

	if (is_oclk_pstate(__io, DIGITAL_LOW)) __io-> is_oclk_ready = true;

	if (is_oclk_pstate(__io, DIGITAL_HIGH) && __io-> is_oclk_ready)
	{
		if (__io-> obuff_point != -1)
		{
			if (__io-> cc_till_write == 0)
			{
				if (__io-> writing_odat)
				{
					uint8_t out = (__io-> dato_buff[__io-> obuff_point] >> __io-> odat_bpoint) & 1;

					__io-> set_pstate_fptr(out, TMP_DATO_PID);

					if (__io-> odat_bpoint == 7)
					{
						__io-> writing_odat = false;
						__io-> odat_bpoint = 0;
					}
					else
						__io-> odat_bpoint ++;

				}
				else
				{
					__io-> obuff_point --;
					__io-> writing_odat = true;
				}

				__io-> cc_till_write = TMP_WHOLDUP_CC;
			} else
				__io-> cc_till_write --;
		}

		__io-> is_oclk_ready = false;
	}
}

uint8_t * get_from_ibuff(struct io * __io, size_t __bytes) {
	int_t old_ibuff_pos = 0;
	bool first = false;
	if (__io-> ibuff_point < __bytes) {
		for (;;) {
			if (__io-> ibuff_point >= __bytes) break;
			old_ibuff_pos = __io-> ibuff_point;

			for (;;) {
				__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_DATO_PID);

				if (first) {
					if (__io-> ibuff_point == (old_ibuff_pos + 1))break;
					__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_DATO_PID);
					tick(__io);
					__io-> set_pstate_fptr(DIGITAL_LOW, TMP_DATO_PID);
				}

				if (__io-> ibuff_point == (old_ibuff_pos + 1))break;
				__io-> set_pstate_fptr(DIGITAL_LOW, TMP_RSEND_PID);
# ifdef F_CPU
            	if (TMP_SRWAIT_MS != 0) _delay_ms(TMP_SRWAIT_MS);
# endif
				__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_DATO_PID);
				tick(__io);
				__io-> set_pstate_fptr(DIGITAL_LOW, TMP_DATO_PID);
				__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_RSEND_PID);
# ifdef F_CPU
            	if (TMP_SRWAIT_MS != 0) _delay_ms(TMP_SRWAIT_MS);
# endif
				first = true;
			}
		}
	}

	uint8_t * data = (uint8_t *)malloc(__bytes);
	memset(data, 0x0, __bytes);

	for (size_t i = 0; i != __bytes; i ++)
		data[i] = __io-> dati_buff[((__io-> ibuff_point - 1) - i)];

	__io-> ibuff_point -= __bytes;

	return data;
}


void add_to_obuff(struct io * __io, uint8_t * __data, size_t __bytes) {
	for (size_t i = 0; i != __bytes; i ++)
		__io-> dato_buff[(__io-> obuff_point + i)] = __data[i];

	__io-> obuff_point += __bytes-1;

	int_t old_obuff_pos = 0;
	bool first = false;
	if (__io-> obuff_point != 0) {
		for (;;) {
			if (__io-> obuff_point == -1) break;
			old_obuff_pos = __io-> obuff_point;

			for (;;) {
				if (first) {
					if (__io-> obuff_point == (old_obuff_pos -1)) break;
					tick(__io);
					for (;;) if (__io-> get_pstate_fptr(TMP_DATI_PID) == DIGITAL_LOW) break;
				}

				if (__io-> obuff_point == (old_obuff_pos -1)) break;
				__io-> set_pstate_fptr(DIGITAL_LOW, TMP_RRECV_PID);
# ifdef F_CPU
            	if (TMP_SRWAIT_MS != 0) _delay_ms(TMP_SRWAIT_MS);
# endif
				tick(__io);
				for (;;) if (__io-> get_pstate_fptr(TMP_DATI_PID) == DIGITAL_LOW) break;
				__io-> set_pstate_fptr(DIGITAL_HIGH, TMP_RRECV_PID);
# ifdef F_CPU
                if (TMP_SRWAIT_MS != 0) _delay_ms(TMP_SRWAIT_MS);
# endif
				first = true;
			}
		}
	}
	__io-> obuff_point = 0;
}

io_buff_t * io_buff(uint8_t * __ptr_to_data, size_t __amount_of_bytes)
{
	io_buff_t * to_return = (io_buff_t *)malloc(sizeof(io_buff_t));

	to_return-> ptr_to_data = __ptr_to_data;
	to_return-> amount_of_bytes = __amount_of_bytes;

	return to_return;
}

void clear_ibuff(struct io * __io)
{
	/* clear the input buffer by replaceing all elements to 0x0
	*/
	memset(__io-> dati_buff, 0x0, __io-> ibuff_length);
}

void clear_obuff(struct io * __io)
{
	/* clear the output buffer by replaceing all elements to 0x0
	*/
	memset(__io-> dato_buff, 0x0, __io-> obuff_length);
}

void send(struct io * __io, io_buff_t * __io_buff)
{
	clear_obuff(__io);

	add_to_obuff(__io, __io_buff-> ptr_to_data, __io_buff-> amount_of_bytes);

	free(__io_buff);
}

void recv(struct io * __io, io_buff_t * __io_buff)
{
	if (__io_buff == NULL) return;

	clear_ibuff(__io);

	__io_buff-> ptr_to_data = get_from_ibuff(__io, __io_buff-> amount_of_bytes);

	free(__io_buff);
}
