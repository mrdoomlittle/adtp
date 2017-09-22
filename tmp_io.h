# ifndef __tmp__io
# define __tmp__io
# include <mdlint.h>
# include <stdlib.h>
# include <math.h>
# ifdef __AVR
#	include <avr/interrupt.h>
# endif

# ifdef __DEBUG_ENABLED
#	include <stdio.h>
# endif

# define __TMP_LIGHT

# define TMP_SUCCESS 0
# define TMP_TIMEO 1
# define TMP_FAILURE -1

# define ACK_SUCCESS 1
# define ACK_FAILURE 0

# define TMP_FLIP_BIT_OPT 0b10000000
# define TMP_INVERT_TX_TRIG_VAL_OPT 0b01000000
# define TMP_INVERT_RX_TRIG_VAL_OPT 0b00100000
typedef mdl_u32_t tmp_addr_t;
typedef mdl_u8_t tmp_version_t;

/*
	tmp_opt and optflags are diffrent as optflags have no value & tmp_opt effects all not just snd or rcv oporations
*/

struct tmp_io {
	mdl_u8_t rx_pid, tx_pid;
	mdl_u8_t rx_ci_pid, tx_ci_pid;
	mdl_u8_t rx_co_pid, tx_co_pid;

	mdl_uint_t snd_timeo, rcv_timeo;
	mdl_uint_t snd_timeo_ic, rcv_timeo_ic;

	mdl_uint_t snd_holdup_ic, rcv_holdup_ic;
	mdl_uint_t snd_holdup, rcv_holdup;
	mdl_u8_t snd_optflags, rcv_optflags;

	void(*set_pin_mode_fp)(mdl_u8_t, mdl_u8_t);
	void(*set_pin_state_fp)(mdl_u8_t, mdl_u8_t);
	mdl_u8_t(*get_pin_state_fp)(mdl_u8_t);
	void(*holdup_fp)(mdl_uint_t);
# ifndef __TMP_LIGHT
	tmp_addr_t iface_addr;
# endif
};

# ifndef __TMP_LIGHT
void __inline__ static tmp_set_iface_addr(struct tmp_io *__tmp_io, tmp_addr_t __iface_addr) {
	__tmp_io->iface_addr = __iface_addr;}
# endif

typedef mdl_i8_t tmp_err_t;

# ifndef __TMP_LIGHT
mdl_u32_t tmp_addr_from_str(char unsigned const*, tmp_err_t*);
# endif

typedef struct {
	mdl_u8_t *p;
	mdl_uint_t bc;
} tmp_io_buff_t;

# define TMP_PACKET_LENGTH 126
# define TMP_PK_HEADER_LEN 96
struct tmp_packet_t {
	tmp_addr_t dst_addr, src_addr;
	mdl_u32_t dsec_hash;
	tmp_io_buff_t io_buff;
};

tmp_err_t tmp_seti_speed(struct tmp_io*, mdl_uint_t);
tmp_err_t tmp_seto_speed(struct tmp_io*, mdl_uint_t);

# ifndef __TMP_LIGHT
tmp_err_t tmp_send_packet(struct tmp_io*, struct tmp_packet_t*);
tmp_err_t tmp_recv_packet(struct tmp_io*, struct tmp_packet_t*);
# endif

mdl_u8_t extern tmp_errno;

void tmp_set_pmode(struct tmp_io*, mdl_u8_t, mdl_u8_t);
void tmp_set_pstate(struct tmp_io*, mdl_u8_t, mdl_u8_t);
mdl_u8_t tmp_get_pstate(struct tmp_io*, mdl_u8_t);

tmp_err_t tmp_init(struct tmp_io*, void(*)(mdl_u8_t, mdl_u8_t), void(*)(mdl_u8_t, mdl_u8_t), mdl_u8_t(*)(mdl_u8_t));

void tmp_set_holdup_fp(struct tmp_io*, void(*)(mdl_uint_t));
void tmp_holdup(struct tmp_io*, mdl_uint_t, mdl_uint_t);

tmp_io_buff_t tmp_io_buff(mdl_u8_t*, mdl_uint_t);

void tmp_flip_rx_clk_trig_val();
mdl_u8_t tmp_is_rx_clk_trig_val(mdl_u8_t);

void tmp_flip_tx_clk_trig_val();
mdl_u8_t tmp_is_tx_clk_trig_val(mdl_u8_t);

tmp_err_t tmp_raw_send(struct tmp_io*, tmp_io_buff_t);
tmp_err_t tmp_raw_recv(struct tmp_io*, tmp_io_buff_t);

mdl_u8_t tmp_par_arcv_sig(struct tmp_io*);
mdl_u8_t tmp_par_asnd_sig(struct tmp_io*);
# ifndef __TMP_LIGHT
tmp_err_t tmp_send(struct tmp_io*, tmp_io_buff_t, tmp_addr_t);
tmp_err_t tmp_recv(struct tmp_io*, tmp_io_buff_t, tmp_addr_t);
# else
# 	define tmp_send(__tmp_io, __io_buff) tmp_raw_send(__tmp_io, __io_buff)
#	define tmp_recv(__tmp_io, __io_buff) tmp_raw_recv(__tmp_io, __io_buff)
# endif

tmp_err_t tmp_recv_nibble(struct tmp_io*, mdl_u8_t*);
tmp_err_t tmp_send_nibble(struct tmp_io*, mdl_u8_t);
tmp_err_t tmp_recv_byte(struct tmp_io*, mdl_u8_t*);
tmp_err_t tmp_send_byte(struct tmp_io*, mdl_u8_t);

tmp_err_t tmp_recv_bit(struct tmp_io*, mdl_u8_t*);
tmp_err_t tmp_send_bit(struct tmp_io*, mdl_u8_t);

# ifndef __TMP_LIGHT
tmp_err_t tmp_send_w64(struct tmp_io*, mdl_u64_t);
tmp_err_t tmp_recv_w64(struct tmp_io*, mdl_u64_t*);

tmp_err_t tmp_send_w32(struct tmp_io*, mdl_u32_t);
tmp_err_t tmp_recv_w32(struct tmp_io*, mdl_u32_t*);

tmp_err_t tmp_send_w16(struct tmp_io*, mdl_u16_t);
tmp_err_t tmp_recv_w16(struct tmp_io*, mdl_u16_t*);

tmp_err_t __inline__ static tmp_send_w8(struct tmp_io *__tmp_io, mdl_u8_t __data) {
	return tmp_send_byte(__tmp_io, __data);}
tmp_err_t __inline__ static tmp_recv_w8(struct tmp_io *__tmp_io, mdl_u8_t *__data) {
	return tmp_recv_byte(__tmp_io, __data);}
# endif

enum tmp_opt {TMP_OPT_SND_TIMEO, TMP_OPT_RCV_TIMEO};

typedef enum tmp_opt tmp_opt_t;
void tmp_set_opt(struct tmp_io*, tmp_opt_t, void*);
void tmp_get_opt(struct tmp_io*, tmp_opt_t, void*);

mdl_u8_t __inline__ static tmp_timeo(mdl_uint_t *__timeo_ic, mdl_uint_t __timeo) {
	if (!__timeo) return 0;
	if (*__timeo_ic >= __timeo) {*__timeo_ic = 0;return 1;} else (*__timeo_ic)++;
	return 0;
}

mdl_u8_t __inline__ static tmp_snd_timeo(struct tmp_io *__tmp_io) {
	mdl_u8_t res = tmp_timeo(&__tmp_io->snd_timeo_ic, __tmp_io->snd_timeo);
	tmp_holdup(__tmp_io, 1, 1);
	return res;
}

mdl_u8_t __inline__ static tmp_rcv_timeo(struct tmp_io *__tmp_io) {
	mdl_u8_t res = tmp_timeo(&__tmp_io->rcv_timeo_ic, __tmp_io->rcv_timeo);
	tmp_holdup(__tmp_io, 1, 1);
	return res;
}

mdl_u8_t tmp_is_optflag(mdl_u8_t, mdl_u8_t);
void tmp_tog_optflag(mdl_u8_t*, mdl_u8_t);

void __inline__ static tmp_tog_snd_optflag(struct tmp_io *__tmp_io, mdl_u8_t __optflag) {
	tmp_tog_optflag(&__tmp_io->snd_optflags, __optflag);}

mdl_u8_t __inline__ static tmp_is_snd_optflag(struct tmp_io *__tmp_io, mdl_u8_t __optflag) {
	return tmp_is_optflag(__tmp_io->snd_optflags, __optflag);}

void __inline__ static tmp_tog_rcv_optflag(struct tmp_io *__tmp_io, mdl_u8_t __optflag) {
	tmp_tog_optflag(&__tmp_io->rcv_optflags, __optflag);}

mdl_u8_t __inline__ static tmp_is_rcv_optflag(struct tmp_io *__tmp_io, mdl_u8_t __optflag) {
	return tmp_is_optflag(__tmp_io->rcv_optflags, __optflag);}
# endif /*__tmp__io*/
