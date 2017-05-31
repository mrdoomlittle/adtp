# include "tmp_io.h"
mdl_i8_t tmp_init(struct tmp_io_t *__tmp_io, void (* __set_pmode_fptr) (mdl_u8_t, mdl_u8_t), void (* __set_pstate_fptr) (mdl_u8_t, mdl_u8_t), mdl_u8_t (* __get_pstate_fptr) (mdl_u8_t)) {
	__tmp_io-> set_pmode_fptr = __set_pmode_fptr;
	__tmp_io-> set_pstate_fptr = __set_pstate_fptr;
	__tmp_io-> get_pstate_fptr = __get_pstate_fptr;
	__tmp_io-> holdup_fptr = NULL;

	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> rx_pid);
	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> rx_ci_pid); // msg: me recv data
	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> rx_co_pid); // msg: node recv data

	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> tx_pid);
	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> tx_ci_pid); // msg: me send data
	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> tx_co_pid); // msg: node send data

	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> rx_co_pid);
	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_pid);
	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_co_pid);

	__tmp_io-> snd_timeo = 0;
	__tmp_io-> snd_timeo_ic = 0;

	__tmp_io-> rcv_timeo = 0;
	__tmp_io-> rcv_timeo_ic = 0;

	__tmp_io-> snd_holdup_ic = 0;
	__tmp_io-> rcv_holdup_ic = 0;
    __tmp_io-> snd_holdup = 0;
	__tmp_io-> rcv_holdup = 0;
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

mdl_i8_t tmp_recv_byte(struct tmp_io_t *__tmp_io, mdl_u8_t *__byte) {
	mdl_u8_t any_err = TMP_SUCCESS;
	for (mdl_u8_t bit_point = 0; bit_point != 8; bit_point++) {
		mdl_u8_t point_bit;
		if ((any_err = tmp_recv_bit(__tmp_io, &point_bit)) != TMP_SUCCESS) return any_err;
		*__byte |= point_bit << bit_point;
	}
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_byte(struct tmp_io_t *__tmp_io, mdl_u8_t __byte) {
	mdl_u8_t any_err = TMP_SUCCESS;
	for (mdl_u8_t bit_point = 0; bit_point != 8; bit_point++)
		if ((any_err = tmp_send_bit(__tmp_io, (__byte >> bit_point) & 1)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_bit(struct tmp_io_t *__tmp_io, mdl_u8_t *__bit) {
	tmp_set_pstate(__tmp_io, 0x1, __tmp_io-> tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io-> rcv_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != 0x1) {
		if (tmp_rcv_timeo(__tmp_io)) {tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_co_pid);return TMP_TIMEO;}}
	tmp_rcv_holdup(__tmp_io);

	*__bit = tmp_get_pstate(__tmp_io, __tmp_io-> rx_pid);
	tmp_rcv_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io-> rcv_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != 0x0){if (tmp_rcv_timeo(__tmp_io))return TMP_TIMEO;}
	tmp_rcv_holdup(__tmp_io);
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_bit(struct tmp_io_t *__tmp_io, mdl_u8_t __bit) {
	__tmp_io-> snd_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != 0x1){if (tmp_snd_timeo(__tmp_io))return TMP_TIMEO;}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, __bit, __tmp_io-> tx_pid);
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, 0x1, __tmp_io-> rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	__tmp_io-> snd_timeo_ic = 0;
	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != 0x0){
		if (tmp_snd_timeo(__tmp_io)) {tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> rx_co_pid);return TMP_TIMEO;}}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> rx_co_pid);
	tmp_snd_holdup(__tmp_io);
	return TMP_SUCCESS;
}

void tmp_set_pmode(struct tmp_io_t *__tmp_io, mdl_u8_t __pmode, mdl_u8_t __pid) {
	__tmp_io-> set_pmode_fptr(__pmode, __pid);}

void tmp_set_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pstate, mdl_u8_t __pid) {
	__tmp_io-> set_pstate_fptr(__pstate, __pid);}

mdl_u8_t tmp_get_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pid) {
	return __tmp_io-> get_pstate_fptr(__pid);}

mdl_i8_t tmp_send(struct tmp_io_t *__tmp_io, tmp_io_buff_t __io_buff) {
	mdl_u8_t any_err = TMP_SUCCESS;
	for (mdl_u8_t *ptr = __io_buff.ptr; ptr != __io_buff.ptr + __io_buff.bytes; ptr ++)
		if ((any_err = tmp_send_byte(__tmp_io, *ptr)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv(struct tmp_io_t *__tmp_io, tmp_io_buff_t __io_buff) {
	mdl_u8_t any_err = TMP_SUCCESS;
	for (mdl_u8_t *ptr = __io_buff.ptr; ptr != __io_buff.ptr + __io_buff.bytes; ptr ++)
		if ((any_err = tmp_recv_byte(__tmp_io, ptr)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

tmp_io_buff_t tmp_io_buff(mdl_u8_t *__ptr, mdl_uint_t __bytes) {
	tmp_io_buff_t io_buff = {.ptr = __ptr, .bytes = __bytes};
	return io_buff;}

mdl_i8_t tmp_send_w64(struct tmp_io_t *__tmp_io, mdl_u64_t __data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u32_t part = 0;
	part |= (part & 0xFFFFFF) | __data;
	if ((any_err = tmp_send_w32(__tmp_io, part)) != TMP_SUCCESS) return any_err;

	part = 0;
	part |= (part & 0xFFFFFF) | __data << 32;
	if ((any_err = tmp_send_w32(__tmp_io, part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w64(struct tmp_io_t *__tmp_io, mdl_u64_t *__data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u32_t part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= part;

	part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u64_t)part << 32;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_w32(struct tmp_io_t *__tmp_io, mdl_u32_t __data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u16_t part = 0;
	part |= (part & 0xFFFF) | __data;
	if ((any_err = tmp_send_w16(__tmp_io, part)) != TMP_SUCCESS) return any_err;

	part = 0;
	part |= (part & 0xFFFF) | __data << 16;
	if ((any_err = tmp_send_w16(__tmp_io, part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w32(struct tmp_io_t *__tmp_io, mdl_u32_t *__data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u16_t part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= part;

	part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u32_t)part << 16;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_send_w16(struct tmp_io_t *__tmp_io, mdl_u16_t __data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u8_t part = 0;
	part |= (part & 0xFF) | __data;
	if ((any_err = tmp_send_byte(__tmp_io, part)) != TMP_SUCCESS) return any_err;

	part = 0;
	part |= (part & 0xFF) | __data << 8;
	if ((any_err = tmp_send_byte(__tmp_io, part)) != TMP_SUCCESS) return any_err;
	return TMP_SUCCESS;
}

mdl_i8_t tmp_recv_w16(struct tmp_io_t *__tmp_io, mdl_u16_t *__data) {
	mdl_u8_t any_err = TMP_SUCCESS;
	mdl_u8_t part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= part;

	part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u16_t)part << 8;
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
