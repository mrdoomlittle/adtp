# include "tmp_io.h"
mdl_u8_t tmp_gpio_high = 0x1, tmp_gpio_low = 0x0;
mdl_u8_t tmp_gpio_in = 0x0, tmp_gpio_out = 0x1;

mdl_u8_t rx_clk_trig_val;
mdl_u8_t tx_clk_trig_val;

mdl_i8_t tmp_init(struct tmp_io_t *__tmp_io, void (* __set_pmode_fptr) (mdl_u8_t, mdl_u8_t), void (* __set_pstate_fptr) (mdl_u8_t, mdl_u8_t), mdl_u8_t (* __get_pstate_fptr) (mdl_u8_t)) {
	__tmp_io-> set_pmode_fptr = __set_pmode_fptr;
	__tmp_io-> set_pstate_fptr = __set_pstate_fptr;
	__tmp_io-> get_pstate_fptr = __get_pstate_fptr;
	__tmp_io-> holdup_fptr = NULL;

	tmp_set_pmode(__tmp_io, tmp_gpio_in, __tmp_io-> rx_pid);
	tmp_set_pmode(__tmp_io, tmp_gpio_in, __tmp_io-> rx_ci_pid); // msg: me recv data
	tmp_set_pmode(__tmp_io, tmp_gpio_out, __tmp_io-> rx_co_pid); // msg: node recv data

	tmp_set_pmode(__tmp_io, tmp_gpio_out, __tmp_io-> tx_pid);
	tmp_set_pmode(__tmp_io, tmp_gpio_in, __tmp_io-> tx_ci_pid); // msg: me send data
	tmp_set_pmode(__tmp_io, tmp_gpio_out, __tmp_io-> tx_co_pid); // msg: node send data

	rx_clk_trig_val = tmp_gpio_low;
	tx_clk_trig_val = tmp_gpio_low;

	tmp_set_pstate(__tmp_io, ~rx_clk_trig_val & 0x1, __tmp_io-> rx_co_pid);
	tmp_set_pstate(__tmp_io, tmp_gpio_low, __tmp_io-> tx_pid);
	tmp_set_pstate(__tmp_io, ~tx_clk_trig_val & 0x1, __tmp_io-> tx_co_pid);

	__tmp_io-> snd_timeo = 0;
	__tmp_io-> snd_timeo_ic = 0;

	__tmp_io-> rcv_timeo = 0;
	__tmp_io-> rcv_timeo_ic = 0;

	__tmp_io-> snd_holdup_ic = 0;
	__tmp_io-> rcv_holdup_ic = 0;
    __tmp_io-> snd_holdup = 0;
	__tmp_io-> rcv_holdup = 0;
	__tmp_io-> snd_optflags = 0;
	__tmp_io-> rcv_optflags = 0;

	tmp_holdup(__tmp_io, 200, 0);
	return 0;
}

void tmp_set_holdup_fptr(struct tmp_io_t *__tmp_io, void (* __holdup_fptr)(mdl_uint_t)) {
	__tmp_io-> holdup_fptr = __holdup_fptr;}

void tmp_holdup(struct tmp_io_t *__tmp_io, mdl_uint_t __holdup_ic, mdl_uint_t __holdup) {
	if (!__tmp_io-> holdup_fptr || !__holdup_ic) return;
	mdl_uint_t ic = 0;
	while(ic != __holdup_ic) {__tmp_io-> holdup_fptr(__holdup);ic++;}
}

void tmp_snd_holdup(struct tmp_io_t *__tmp_io){tmp_holdup(__tmp_io, __tmp_io-> snd_holdup_ic, __tmp_io-> snd_holdup);}
void tmp_rcv_holdup(struct tmp_io_t *__tmp_io){tmp_holdup(__tmp_io, __tmp_io-> rcv_holdup_ic, __tmp_io-> rcv_holdup);}
void tmp_flip_rx_clk_trig_val() {rx_clk_trig_val = ~rx_clk_trig_val & 0x1;}
mdl_u8_t tmp_is_rx_clk_trig_val(mdl_u8_t __trig_val) {return rx_clk_trig_val == __trig_val? 1 : 0;}

void tmp_flip_tx_clk_trig_val() {tx_clk_trig_val = ~tx_clk_trig_val & 0x1;}
mdl_u8_t tmp_is_tx_clk_trig_val(mdl_u8_t __trig_val) {return tx_clk_trig_val == __trig_val? 1 : 0;}

mdl_i8_t tmp_recv_nibble(struct tmp_io_t *__tmp_io, mdl_u8_t *__nibble) {
	mdl_i8_t any_err;
	for (mdl_u8_t bit_point = 0; bit_point != 4; bit_point++) {
		mdl_u8_t bit_val;
		if ((any_err = tmp_recv_bit(__tmp_io, &bit_val)) != TMP_SUCCESS) return any_err;
		*__nibble |= bit_val << bit_point;
	}
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_nibble(struct tmp_io_t *__tmp_io, mdl_u8_t __nibble) {
	mdl_i8_t any_err;
	for (mdl_u8_t bit_point = 0; bit_point != 4; bit_point++)
		if ((any_err = tmp_send_bit(__tmp_io, (__nibble >> bit_point) & 1)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_byte(struct tmp_io_t *__tmp_io, mdl_u8_t *__byte) {
	mdl_u8_t any_err, nibble_val;

	nibble_val = 0x0;
	if ((any_err = tmp_recv_nibble(__tmp_io, &nibble_val)) != TMP_SUCCESS) return any_err;
	*__byte |= nibble_val;

	nibble_val = 0x0;
	if ((any_err = tmp_recv_nibble(__tmp_io, &nibble_val)) != TMP_SUCCESS) return any_err;
	*__byte |= nibble_val << 4;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_byte(struct tmp_io_t *__tmp_io, mdl_u8_t __byte) {
	mdl_i8_t any_err;
	if ((any_err = tmp_send_nibble(__tmp_io, __byte)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_send_nibble(__tmp_io, __byte >> 4)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_u8_t _invert_rcv_tx_trig_val = 0x0;
mdl_u8_t _invert_rcv_rx_trig_val = 0x0;

void invert_rcv_tx_trig_val() {_invert_rcv_tx_trig_val = 0x1;}
void uinvert_rcv_tx_trig_val() {_invert_rcv_tx_trig_val = 0x0;}

void invert_rcv_rx_trig_val() {_invert_rcv_rx_trig_val = 0x1;}
void uinvert_rcv_rx_trig_val() {_invert_rcv_rx_trig_val = 0x0;}

mdl_u8_t _invert_snd_tx_trig_val = 0x0;
mdl_u8_t _invert_snd_rx_trig_val = 0x0;

void invert_snd_tx_trig_val() {_invert_snd_tx_trig_val = 0x1;}
void uinvert_snd_tx_trig_val() {_invert_snd_tx_trig_val = 0x0;}

void invert_snd_rx_trig_val() {_invert_snd_rx_trig_val = 0x1;}
void uinvert_snd_rx_trig_val() {_invert_snd_rx_trig_val = 0x0;}

mdl_i8_t tmp_recv_bit(struct tmp_io_t *__tmp_io, mdl_u8_t *__bit) {
	mdl_u8_t _tx_clk_trig_val = _invert_rcv_tx_trig_val? ~tx_clk_trig_val & 0x1 : tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = _invert_rcv_rx_trig_val? ~rx_clk_trig_val & 0x1 : rx_clk_trig_val;

	tmp_set_pstate(__tmp_io, _tx_clk_trig_val, __tmp_io-> tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io-> rcv_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != _rx_clk_trig_val) {
		if (tmp_rcv_timeo(__tmp_io)) {tmp_set_pstate(__tmp_io, ~_tx_clk_trig_val & 0x1, __tmp_io-> tx_co_pid);return TMP_TIMEO;}}

	tmp_rcv_holdup(__tmp_io);

	*__bit = tmp_get_pstate(__tmp_io, __tmp_io-> rx_pid);
	tmp_rcv_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, ~_tx_clk_trig_val & 0x1, __tmp_io-> tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io-> rcv_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != (~_rx_clk_trig_val & 0x1)) {if (tmp_rcv_timeo(__tmp_io)) return TMP_TIMEO;}

	tmp_rcv_holdup(__tmp_io);
	if (tmp_is_rcv_optflag(__tmp_io, TMP_FLIP_BITS_OPT)) *__bit = ~(*__bit);
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_bit(struct tmp_io_t *__tmp_io, mdl_u8_t __bit) {
	mdl_u8_t _tx_clk_trig_val = _invert_snd_tx_trig_val? ~tx_clk_trig_val & 0x1 : tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = _invert_snd_rx_trig_val? ~rx_clk_trig_val & 0x1 : rx_clk_trig_val;

	if (tmp_is_snd_optflag(__tmp_io, TMP_FLIP_BITS_OPT)) __bit = ~__bit;

	__tmp_io-> snd_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != _tx_clk_trig_val){if (tmp_snd_timeo(__tmp_io))return TMP_TIMEO;}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, __bit, __tmp_io-> tx_pid);
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, _rx_clk_trig_val, __tmp_io-> rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	__tmp_io-> snd_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != (~_tx_clk_trig_val & 0x1)){
		if (tmp_snd_timeo(__tmp_io)) {tmp_set_pstate(__tmp_io, ~_rx_clk_trig_val & 0x1, __tmp_io-> rx_co_pid);return TMP_TIMEO;}}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, ~_rx_clk_trig_val & 0x1, __tmp_io-> rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	// save power
	if (__bit) tmp_set_pstate(__tmp_io, tmp_gpio_low, __tmp_io-> tx_pid);
	return TMP_SUCCESS;
}

void tmp_set_pmode(struct tmp_io_t *__tmp_io, mdl_u8_t __pmode, mdl_u8_t __pid) {
	__tmp_io-> set_pmode_fptr(__pmode, __pid);}

void tmp_set_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pstate, mdl_u8_t __pid) {
	__tmp_io-> set_pstate_fptr(__pstate, __pid);}

mdl_u8_t tmp_get_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pid) {
	return __tmp_io-> get_pstate_fptr(__pid);}

# define KEY 300
mdl_i8_t send_key_and_sync(struct tmp_io_t *__tmp_io) {
	mdl_i8_t any_err;

	while(1) {
		if ((any_err = tmp_send_w64(__tmp_io, KEY)) != TMP_SUCCESS) return any_err;
		mdl_u8_t recved_ack = 0;
		if ((any_err = tmp_recv_bit(__tmp_io, &recved_ack)) != TMP_SUCCESS) return any_err;
		if (!recved_ack) break;
	}
	return TMP_SUCCESS;
}

mdl_i8_t recv_key_and_sync(struct tmp_io_t *__tmp_io) {
	mdl_i8_t any_err;

	while(1) {
		mdl_u64_t recved_key = 0x0;
		if ((any_err = tmp_recv_w64(__tmp_io, &recved_key)) != TMP_SUCCESS) return any_err;
		if (recved_key != KEY) {
			mdl_u8_t dummy;
			tmp_recv_bit(__tmp_io, &dummy);
			tmp_send_bit(__tmp_io, 1);
		} else {tmp_send_bit(__tmp_io, 0);break;}
	}
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send(struct tmp_io_t *__tmp_io, tmp_io_buff_t __io_buff) {
	mdl_i8_t any_err;

	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;

	for (mdl_u8_t *ptr = __io_buff.ptr; ptr != __io_buff.ptr + __io_buff.bytes; ptr ++)
		if ((any_err = tmp_send_byte(__tmp_io, *ptr)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv(struct tmp_io_t *__tmp_io, tmp_io_buff_t __io_buff) {
	mdl_i8_t any_err;

	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;

	for (mdl_u8_t *ptr = __io_buff.ptr; ptr != __io_buff.ptr + __io_buff.bytes; ptr ++)
		if ((any_err = tmp_recv_byte(__tmp_io, ptr)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

tmp_io_buff_t tmp_io_buff(mdl_u8_t *__ptr, mdl_uint_t __bytes) {
	tmp_io_buff_t io_buff = {.ptr = __ptr, .bytes = __bytes};
	return io_buff;}

mdl_i8_t tmp_send_w64(struct tmp_io_t *__tmp_io, mdl_u64_t __data) {
	mdl_i8_t any_err;
	mdl_u32_t _64b_part;

	_64b_part = 0;
	_64b_part = (_64b_part & 0xFFFFFFFF) | __data;
	if ((any_err = tmp_send_w32(__tmp_io, _64b_part)) != TMP_SUCCESS) return any_err;

	_64b_part = 0;
	_64b_part = (_64b_part & 0xFFFFFFFF) | __data >> 32;
	if ((any_err = tmp_send_w32(__tmp_io, _64b_part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w64(struct tmp_io_t *__tmp_io, mdl_u64_t *__data) {
	mdl_i8_t any_err;
	mdl_u32_t _64b_part;

	_64b_part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &_64b_part)) != TMP_SUCCESS) return any_err;
	*__data |= _64b_part;

	_64b_part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &_64b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u64_t)_64b_part << 32;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_w32(struct tmp_io_t *__tmp_io, mdl_u32_t __data) {
	mdl_i8_t any_err;
	mdl_u16_t _32b_part;

	_32b_part = 0;
	_32b_part |= (_32b_part & 0xFFFF) |  __data;
	if ((any_err = tmp_send_w16(__tmp_io, _32b_part)) != TMP_SUCCESS) return any_err;

	_32b_part = 0;
	_32b_part |= (_32b_part & 0xFFFF) | __data >> 16;
	if ((any_err = tmp_send_w16(__tmp_io, _32b_part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w32(struct tmp_io_t *__tmp_io, mdl_u32_t *__data) {
	mdl_i8_t any_err;
	mdl_u16_t _32b_part;

	_32b_part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &_32b_part)) != TMP_SUCCESS) return any_err;
	*__data |= _32b_part;

	_32b_part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &_32b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u32_t)_32b_part << 16;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_w16(struct tmp_io_t *__tmp_io, mdl_u16_t __data) {
	mdl_i8_t any_err;
	mdl_u8_t _16b_part;

	_16b_part = 0;
	_16b_part |= (_16b_part & 0xFF) | __data;
	if ((any_err = tmp_send_byte(__tmp_io, _16b_part)) != TMP_SUCCESS) return any_err;

	_16b_part = 0;
	_16b_part |= (_16b_part & 0xFF) | __data >> 8;
	if ((any_err = tmp_send_byte(__tmp_io, _16b_part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w16(struct tmp_io_t *__tmp_io, mdl_u16_t *__data) {
	mdl_i8_t any_err;
	mdl_u8_t _16b_part;

	_16b_part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &_16b_part)) != TMP_SUCCESS) return any_err;
	*__data |= _16b_part;

	_16b_part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &_16b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u16_t)_16b_part << 8;
	return TMP_SUCCESS;
}

void tmp_set_opt(struct tmp_io_t *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_TIMEO:
			__tmp_io-> snd_timeo = *(mdl_uint_t *)__data;
		break;
		case TMP_OPT_RCV_TIMEO:
			__tmp_io-> rcv_timeo = *(mdl_uint_t *)__data;
		break;
	}
}

void tmp_get_opt(struct tmp_io_t *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_TIMEO:
			*(mdl_uint_t *)__data = __tmp_io-> snd_timeo;
		break;
		case TMP_OPT_RCV_TIMEO:
			*(mdl_uint_t *)__data = __tmp_io-> rcv_timeo;
		break;
	}
}

mdl_u8_t tmp_is_optflag(mdl_u8_t __optflags, mdl_u8_t __optflag) {
	if ((__optflags & __optflag) == __optflag) return 1; return 0;}

void tmp_tog_optflag(mdl_u8_t *__optflags, mdl_u8_t __optflag) {
	if (tmp_is_optflag(*__optflags, __optflag))
		(*__optflags) ^= __optflag;
	else
		(*__optflags) |= __optflag;
}
