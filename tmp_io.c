# include "tmp_io.h"
mdl_i8_t tmp_init(struct tmp_io_t *__tmp_io, void (* __set_pmode_fptr) (mdl_u8_t, mdl_u8_t), void (* __set_pstate_fptr) (mdl_u8_t, mdl_u8_t), mdl_u8_t (* __get_pstate_fptr) (mdl_u8_t)) {
	__tmp_io-> set_pmode_fptr = __set_pmode_fptr;
	__tmp_io-> set_pstate_fptr = __set_pstate_fptr;
	__tmp_io-> get_pstate_fptr = __get_pstate_fptr;

	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> rx_pid);
	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> rx_ci_pid); // msg: me recv data
	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> rx_co_pid); // msg: node recv data

	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> tx_pid);
	tmp_set_pmode(__tmp_io, 0x0, __tmp_io-> tx_ci_pid); // msg: me send data
	tmp_set_pmode(__tmp_io, 0x1, __tmp_io-> tx_co_pid); // msg: node send data

	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> rx_co_pid);
	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_pid);
	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_co_pid);
	return 0;
}

mdl_i8_t tmp_recv_byte(struct tmp_io_t *__tmp_io, mdl_u8_t *__byte) {
	for (mdl_u8_t bit_point = 0; bit_point != 8; bit_point++) {
		mdl_u8_t point_bit;
		tmp_recv_bit(__tmp_io, &point_bit);
		*__byte |= point_bit << bit_point;
	}
	return 0;
}

mdl_i8_t tmp_send_byte(struct tmp_io_t *__tmp_io, mdl_u8_t __byte) {
	for (mdl_u8_t bit_point = 0; bit_point != 8; bit_point++)
		tmp_send_bit(__tmp_io, (__byte >> bit_point) & 1);
	return 0;
}

mdl_i8_t tmp_recv_bit(struct tmp_io_t *__tmp_io, mdl_u8_t *__bit) {
	tmp_set_pstate(__tmp_io, 0x1, __tmp_io-> tx_co_pid);

	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != 0x1){}

	*__bit = tmp_get_pstate(__tmp_io, __tmp_io-> rx_pid);

	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> tx_co_pid);

	while(tmp_get_pstate(__tmp_io, __tmp_io-> rx_ci_pid) != 0x0){}
	return 0;
}

mdl_i8_t tmp_send_bit(struct tmp_io_t *__tmp_io, mdl_u8_t __bit) {
	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != 0x1){}

	tmp_set_pstate(__tmp_io, __bit, __tmp_io-> tx_pid);

	tmp_set_pstate(__tmp_io, 0x1, __tmp_io-> rx_co_pid);

	while(tmp_get_pstate(__tmp_io, __tmp_io-> tx_ci_pid) != 0x0){}
	tmp_set_pstate(__tmp_io, 0x0, __tmp_io-> rx_co_pid);
	return 0;
}

void tmp_set_pmode(struct tmp_io_t *__tmp_io, mdl_u8_t __pmode, mdl_u8_t __pid) {
	__tmp_io-> set_pmode_fptr(__pmode, __pid);
}

void tmp_set_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pstate, mdl_u8_t __pid) {
	__tmp_io-> set_pstate_fptr(__pstate, __pid);
}

mdl_u8_t tmp_get_pstate(struct tmp_io_t *__tmp_io, mdl_u8_t __pid) {
	return __tmp_io-> get_pstate_fptr(__pid);
}

mdl_i8_t tmp_send(struct tmp_io_t *__tmp_io, tmp_io_buff_t *__io_buff) {
	for (mdl_u8_t *ptr = __io_buff-> ptr; ptr != __io_buff-> ptr + __io_buff-> bytes; ptr ++) tmp_send_byte(__tmp_io, *ptr);
	free(__io_buff);
}


mdl_i8_t tmp_recv(struct tmp_io_t *__tmp_io, tmp_io_buff_t *__io_buff) {
	for (mdl_u8_t *ptr = __io_buff-> ptr; ptr != __io_buff-> ptr + __io_buff-> bytes; ptr ++) tmp_recv_byte(__tmp_io, ptr);
	free(__io_buff);
}

tmp_io_buff_t* tmp_io_buff(mdl_u8_t *__ptr, mdl_uint_t __bytes) {
	tmp_io_buff_t *io_buff = (tmp_io_buff_t *)malloc(sizeof(tmp_io_buff_t));
	io_buff-> ptr = __ptr;
	io_buff-> bytes = __bytes;
	return io_buff;
}
