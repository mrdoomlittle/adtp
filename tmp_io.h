# ifndef __tmp__io
# define __tmp__io
# include <eint_t.h>
# include <stdlib.h>
# define TMP_SUCCESS 0
# define TMP_TIMEO 1
# define TMP_FAILURE -1
struct tmp_io_t {
	mdl_u8_t rx_pid, tx_pid;
	mdl_u8_t rx_ci_pid, tx_ci_pid;
	mdl_u8_t rx_co_pid, tx_co_pid;

	mdl_uint_t snd_timeo, rcv_timeo;
	mdl_uint_t snd_timeo_c, rcv_timeo_c;

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

tmp_io_buff_t tmp_io_buff(mdl_u8_t *, mdl_uint_t);

mdl_i8_t tmp_send(struct tmp_io_t*, tmp_io_buff_t);
mdl_i8_t tmp_recv(struct tmp_io_t*, tmp_io_buff_t);
mdl_i8_t tmp_recv_byte(struct tmp_io_t*, mdl_u8_t*);
mdl_i8_t tmp_send_byte(struct tmp_io_t*, mdl_u8_t);
mdl_i8_t tmp_recv_bit(struct tmp_io_t*, mdl_u8_t*);
mdl_i8_t tmp_send_bit(struct tmp_io_t*, mdl_u8_t);

mdl_i8_t tmp_send_w64(struct tmp_io_t*, mdl_u64_t);
mdl_i8_t tmp_recv_w64(struct tmp_io_t*, mdl_u64_t*);

mdl_i8_t tmp_send_w32(struct tmp_io_t*, mdl_u32_t);
mdl_i8_t tmp_recv_w32(struct tmp_io_t*, mdl_u32_t*);

mdl_i8_t tmp_send_w16(struct tmp_io_t *, mdl_u16_t);
mdl_i8_t tmp_recv_w16(struct tmp_io_t *, mdl_u16_t*);

mdl_i8_t __inline__ static tmp_send_w8(struct tmp_io_t *__tmp_io, mdl_u8_t __data) {
	return tmp_send_byte(__tmp_io, __data);}
mdl_i8_t __inline__ static tmp_recv_w8(struct tmp_io_t *__tmp_io, mdl_u8_t *__data) {
	return tmp_recv_byte(__tmp_io, __data);}

enum tmp_opt {TMP_OPT_SND_TIMEO, TMP_OPT_RCV_TIMEO};

typedef enum tmp_opt tmp_opt_t;
void tmp_set_opt(struct tmp_io_t *, tmp_opt_t, void *);
void tmp_get_opt(struct tmp_io_t *, tmp_opt_t, void *);
mdl_u8_t __inline__ static tmp_timeo(mdl_uint_t *__timeo_c, mdl_uint_t __timeo) {
	if (!__timeo) return 0;
	if (*__timeo_c >= __timeo) {*__timeo_c = 0;return 1;} else (*__timeo_c)++;
	return 0;
}

mdl_u8_t __inline__ static tmp_snd_timeo(struct tmp_io_t *__tmp_io) {
	return tmp_timeo(&__tmp_io-> snd_timeo_c, __tmp_io-> snd_timeo);}

mdl_u8_t __inline__ static tmp_rcv_timeo(struct tmp_io_t *__tmp_io) {
	return tmp_timeo(&__tmp_io-> rcv_timeo_c, __tmp_io-> rcv_timeo);}
# endif /*__tmp__io*/
