# include <pthread.h>
# include "tmp_io.h"
# include <stdio.h>
# include <string.h>
# define TMP_RX_IC_PID 2
# define TMP_RX_OC_PID 3

# define TMP_TX_IC_PID 4
# define TMP_TX_OC_PID 5

# define TMP_RX_PID 6
# define TMP_TX_PID 7

# define ONLY_SUCCESS

mdl_u8_t se_pinset[12] = {0x0}, cl_pinset[12] = {0x0};

void set_iface_no(mdl_u8_t __no) {
}

mdl_u8_t get_iface_no() {
	return 0;
}

void se_set_pin_mode(mdl_u8_t __mode, mdl_u8_t __id) {}
void se_set_pin_state(mdl_u8_t __state, mdl_u8_t __id) {
	__state = ~__state&0x1;
	if (__id == TMP_RX_OC_PID) {
		cl_pinset[TMP_RX_IC_PID] = __state;
		return;
    } else if (__id == TMP_TX_OC_PID) {
		cl_pinset[TMP_TX_IC_PID] = __state;
		return;
    } else if (__id == TMP_TX_PID) {
		cl_pinset[TMP_RX_PID] = __state;
		return;
	}
	se_pinset[__id] = __state;
}

mdl_u8_t se_get_pin_state(mdl_u8_t __id) {
	return se_pinset[__id];
}

void cl_set_pin_mode(mdl_u8_t __mode, mdl_u8_t __id) {}
void cl_set_pin_state(mdl_u8_t __state, mdl_u8_t __id) {
	__state = ~__state&0x1;
	if (__id == TMP_RX_OC_PID) {
		se_pinset[TMP_RX_IC_PID] = __state;
		return;
	} else if (__id == TMP_TX_OC_PID) {
		se_pinset[TMP_TX_IC_PID] = __state;
		return;
	} else if (__id == TMP_TX_PID) {
		se_pinset[TMP_RX_PID] = __state;
		return;
	}
	cl_pinset[__id] = __state;
}

mdl_u8_t cl_get_pin_state(mdl_u8_t __id) {
	return cl_pinset[__id];
}

# include <unistd.h>
void holdup(mdl_uint_t __holdup) {
	usleep(10);
}

mdl_u8_t data_to_send[] = "IJIjK[AH8YAA8YJU]#OI[I]i0-i9hihgs89ycxga[pu]-]9a]-08]-38]9#-2a0qiu03q=[j3q3]3]qa0''a';ps9a8suasA:S:2::";
void* se(void *__arg) {
struct tmp_io tmp_io = {
	.rx_pid = TMP_RX_PID,
	.tx_pid = TMP_TX_PID,
	.rx_ci_pid = TMP_RX_IC_PID,
	.tx_ci_pid = TMP_TX_IC_PID,
	.rx_co_pid = TMP_RX_OC_PID,
	.tx_co_pid = TMP_TX_OC_PID
};
# ifndef __TMP_LIGHT
	tmp_init(&tmp_io, &se_set_pin_mode, &se_set_pin_state, &se_get_pin_state, 0, 0);
# else
	tmp_init(&tmp_io, &se_set_pin_mode, &se_set_pin_state, &se_get_pin_state);
# endif
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t timeo = 10000;

	tmp_io.snd_holdup_ic = 2;
	tmp_io.rcv_holdup_ic = 2;
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
# ifndef __TMP_LIGHT
	tmp_io.set_iface_no_fp = &set_iface_no;
	tmp_io.get_iface_no_fp = &get_iface_no;
	tmp_err_t err;
	tmp_add_iface(&tmp_io, tmp_addr_from_str("0.0.0.0", &err), 0);
# endif
	printf("node{1} online.\n");
	while(1) {
# ifndef __TMP_LIGHT
	tmp_err_t err = tmp_send(&tmp_io, tmp_io_buff(data_to_send, sizeof(data_to_send)), 0);
# else
	tmp_err_t err = tmp_send(&tmp_io, tmp_io_buff(data_to_send, sizeof(data_to_send)));
# endif
# ifdef ONLY_SUCCESS
	if (err != TMP_SUCCESS) continue;
# endif
	fprintf(stdout, "send_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");

	}
	return NULL;
}

void* cl(void *__arg) {
struct tmp_io tmp_io = {
.rx_pid = TMP_RX_PID, .tx_pid = TMP_TX_PID,
.rx_ci_pid = TMP_RX_IC_PID,
.tx_ci_pid = TMP_TX_IC_PID,
.rx_co_pid = TMP_RX_OC_PID,
.tx_co_pid = TMP_TX_OC_PID
};
# ifndef __TMP_LIGHT
	tmp_init(&tmp_io, &cl_set_pin_mode, &cl_set_pin_state, &cl_get_pin_state, 0, 0);
# else
	tmp_init(&tmp_io, &cl_set_pin_mode, &cl_set_pin_state, &cl_get_pin_state);
# endif
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t timeo = 10000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_io.snd_holdup_ic = 2;
	tmp_io.rcv_holdup_ic = 2;
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);
# ifndef __TMP_LIGHT
	tmp_io.set_iface_no_fp = &set_iface_no;
	tmp_io.get_iface_no_fp = &get_iface_no;
	tmp_err_t err;
	tmp_add_iface(&tmp_io, tmp_addr_from_str("0.0.0.0", &err), 0);
# endif
	printf("node{0} online.\n");
	while(1) {
	mdl_u8_t data[sizeof(data_to_send)];
	memset(data, 0x0, sizeof(data_to_send));
# ifndef __TMP_LIGHT
	tmp_err_t err = tmp_recv(&tmp_io, tmp_io_buff(data, sizeof(data_to_send)), 0);
# else
	tmp_err_t err = tmp_recv(&tmp_io, tmp_io_buff(data, sizeof(data_to_send)));
# endif
# ifdef ONLY_SUCCESS
	if (err != TMP_SUCCESS) continue;
# endif
	fprintf(stdout, "recv_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");
	fprintf(stdout, "recved: %s, is_correct? %s.\n", data, !memcmp(data_to_send, data, sizeof(data_to_send))? "yes":"no");
	}
	return NULL;
}

int main() {
	tmp_err_t a;
	pthread_t se_th, cl_th;
	pthread_create(&se_th, NULL, se, NULL);
	pthread_create(&cl_th, NULL, cl, NULL);

	while(1) {
/*
		printf("se:");
		for (mdl_u8_t i = 0; i != sizeof(se_pinset); i++)
			printf("%u", se_pinset[i]);
		printf("\ncl:");
		for (mdl_u8_t i = 0; i != sizeof(cl_pinset); i++)
			printf("%u", cl_pinset[i]);
		printf("\n");
*/
	}
//	pthread_join(se_th, NULL);
//	pthread_join(cl_th, NULL);
}
