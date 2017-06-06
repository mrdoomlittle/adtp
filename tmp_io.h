# ifndef __tmp__io
# define __tmp__io
# include <eint_t.h>
# include <stdlib.h>
# define TMP_SUCCESS 0
# define TMP_TIMEO 1
# define TMP_FAILURE -1

# define TMP_FLIP_BIT_OPT 0b10000000
struct tmp_io_t {
	mdl_u8_t rx_pid, tx_pid;
	mdl_u8_t rx_ci_pid, tx_ci_pid;
	mdl_u8_t rx_co_pid, tx_co_pid;

	mdl_uint_t snd_timeo, rcv_timeo;
	mdl_uint_t snd_timeo_ic, rcv_timeo_ic;

	mdl_uint_t snd_holdup_ic, rcv_holdup_ic;
	mdl_uint_t snd_holdup, rcv_holdup;
	mdl_u8_t snd_optflags, rcv_optflags;

	void (*set_pmode_fptr) (mdl_u8_t, mdl_u8_t);
	void (*set_pstate_fptr) (mdl_u8_t, mdl_u8_t);
	mdl_u8_t (*get_pstate_fptr) (mdl_u8_t);
	void (*holdup_fptr)(mdl_uint_t);
};

mdl_u8_t extern tmp_errno;

void tmp_set_pmode(struct tmp_io_t*, mdl_u8_t, mdl_u8_t);
void tmp_set_pstate(struct tmp_io_t*, mdl_u8_t, mdl_u8_t);
mdl_u8_t tmp_get_pstate(struct tmp_io_t*, mdl_u8_t);

mdl_i8_t tmp_init(struct tmp_io_t*, void (*) (mdl_u8_t, mdl_u8_t), void (*) (mdl_u8_t, mdl_u8_t), mdl_u8_t (*) (mdl_u8_t));

void tmp_set_holdup_fptr(struct tmp_io_t*, void (*)(mdl_uint_t));
void tmp_holdup(struct tmp_io_t*, mdl_uint_t, mdl_uint_t);

typedef struct {
	mdl_u8_t *ptr;
	mdl_uint_t bytes;
} tmp_io_buff_t;

tmp_io_buff_t tmp_io_buff(mdl_u8_t*, mdl_uint_t);

void tmp_flip_rx_clk_trig_val();
mdl_u8_t tmp_is_rx_clk_trig_val(mdl_u8_t);

void tmp_flip_tx_clk_trig_val();
mdl_u8_t tmp_is_tx_clk_trig_val(mdl_u8_t);

mdl_i8_t tmp_send(struct tmp_io_t*, tmp_io_buff_t);
mdl_i8_t tmp_recv(struct tmp_io_t*, tmp_io_buff_t);
mdl_i8_t tmp_recv_nibble(struct tmp_io_t*, mdl_u8_t*);
mdl_i8_t tmp_send_nibble(struct tmp_io_t*, mdl_u8_t);
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
mdl_u8_t __inline__ static tmp_timeo(mdl_uint_t *__timeo_ic, mdl_uint_t __timeo) {
	if (!__timeo) return 0;
	if (*__timeo_ic >= __timeo) {*__timeo_ic = 0;return 1;} else (*__timeo_ic)++;
	return 0;
}

mdl_u8_t __inline__ static tmp_snd_timeo(struct tmp_io_t *__tmp_io) {
	mdl_u8_t result = tmp_timeo(&__tmp_io-> snd_timeo_ic, __tmp_io-> snd_timeo);
	tmp_holdup(__tmp_io, 1, 1);
	return result;
}

mdl_u8_t __inline__ static tmp_rcv_timeo(struct tmp_io_t *__tmp_io) {
	mdl_u8_t result = tmp_timeo(&__tmp_io-> rcv_timeo_ic, __tmp_io-> rcv_timeo);
	tmp_holdup(__tmp_io, 1, 1);
	return result;
}

mdl_u8_t tmp_is_optflag(mdl_u8_t, mdl_u8_t);
void tmp_tog_optflag(mdl_u8_t*, mdl_u8_t);

void __inline__ static tmp_tog_snd_optflag(struct tmp_io_t *__tmp_io, mdl_u8_t __optflag) {
	tmp_tog_optflag(&__tmp_io-> snd_optflags, __optflag);}
mdl_u8_t __inline__ static tmp_is_snd_optflag(struct tmp_io_t *__tmp_io, mdl_u8_t __optflag) {
	return tmp_is_optflag(__tmp_io-> snd_optflags, __optflag);}

void __inline__ static tmp_tog_rcv_optflag(struct tmp_io_t *__tmp_io, mdl_u8_t __optflag) {
	tmp_tog_optflag(&__tmp_io-> rcv_optflags, __optflag);}
mdl_u8_t __inline__ static tmp_is_rcv_optflag(struct tmp_io_t *__tmp_io, mdl_u8_t __optflag) {
	return tmp_is_optflag(__tmp_io-> rcv_optflags, __optflag);}


void invert_rcv_tx_trig_val();
void uinvert_rcv_tx_trig_val();

void invert_rcv_rx_trig_val();
void uinvert_rcv_rx_trig_val();

void invert_snd_tx_trig_val();
void uinvert_snd_tx_trig_val();

void invert_snd_rx_trig_val();
void uinvert_snd_rx_trig_val();
# endif /*__tmp__io*/
