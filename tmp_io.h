# ifndef __tmp__io
# define __tmp__io
# include <eint_t.h>
# include <stdlib.h>
struct tmp_io_t {
	mdl_u8_t rx_pid, tx_pid;
	mdl_u8_t rx_ci_pid, tx_ci_pid;
	mdl_u8_t rx_co_pid, tx_co_pid;

	void (* set_pmode_fptr) (mdl_u8_t, mdl_u8_t);
	void (* set_pstate_fptr) (mdl_u8_t, mdl_u8_t);
	mdl_u8_t (* get_pstate_fptr) (mdl_u8_t);
};

void tmp_set_pmode(struct tmp_io_t*, mdl_u8_t, mdl_u8_t);
void tmp_set_pstate(struct tmp_io_t*, mdl_u8_t, mdl_u8_t);
mdl_u8_t tmp_get_pstate(struct tmp_io_t*, mdl_u8_t);

mdl_i8_t tmp_init(struct tmp_io_t*, void (*) (mdl_u8_t, mdl_u8_t), void (*) (mdl_u8_t, mdl_u8_t), mdl_u8_t (*) (mdl_u8_t));

typedef struct {
	mdl_u8_t *ptr;
	mdl_uint_t bytes;
} tmp_io_buff_t;

tmp_io_buff_t* tmp_io_buff(mdl_u8_t *, mdl_uint_t);

mdl_i8_t tmp_send(struct tmp_io_t*, tmp_io_buff_t*);
mdl_i8_t tmp_recv(struct tmp_io_t*, tmp_io_buff_t*);
mdl_i8_t tmp_recv_byte(struct tmp_io_t*, mdl_u8_t*);
mdl_i8_t tmp_send_byte(struct tmp_io_t*, mdl_u8_t);
mdl_i8_t tmp_recv_bit(struct tmp_io_t*, mdl_u8_t*);
mdl_i8_t tmp_send_bit(struct tmp_io_t*, mdl_u8_t);
# endif /*__tmp__io*/
