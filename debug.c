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

uint8_t se_pinset[12] = {0x0}, cl_pinset[12] = {0x0};

void se_set_pmode(uint8_t __pmode, uint8_t __pid) {}
void se_set_pstate(uint8_t __pstate, uint8_t __pid) {
//	usleep(1000);
	__pstate = ~__pstate & 0x1;

	if (__pid == TMP_RX_OC_PID) {
		cl_pinset[TMP_RX_IC_PID] = __pstate;
		return;
    } else if (__pid == TMP_TX_OC_PID) {
		cl_pinset[TMP_TX_IC_PID] = __pstate;
		return;
    } else if (__pid == TMP_TX_PID) {
		cl_pinset[TMP_RX_PID] = __pstate;
		return;
	}
	se_pinset[__pid] = __pstate;
}

uint8_t se_get_pstate(uint8_t __pid) {
	return se_pinset[__pid];
}

void cl_set_pmode(uint8_t __pmode, uint8_t __pid) {}
void cl_set_pstate(uint8_t __pstate, uint8_t __pid) {
	__pstate = ~__pstate & 0x1;
	if (__pid == TMP_RX_OC_PID) {
		se_pinset[TMP_RX_IC_PID] = __pstate;
		return;
	} else if (__pid == TMP_TX_OC_PID) {
		se_pinset[TMP_TX_IC_PID] = __pstate;
		return;
	} else if (__pid == TMP_TX_PID) {
		se_pinset[TMP_RX_PID] = __pstate;
		return;
	}
	cl_pinset[__pid] = __pstate;
}

uint8_t cl_get_pstate(uint8_t __pid) {
	return cl_pinset[__pid];
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
	tmp_init(&tmp_io, &se_set_pmode, &se_set_pstate, &se_get_pstate);
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t timeo = 1000000;

	tmp_io.snd_holdup_ic = 2;
	tmp_io.rcv_holdup_ic = 2;
	tmp_tog_rcv_optflag(&tmp_io, TMP_FLIP_BIT_OPT);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);
	tmp_tog_snd_optflag(&tmp_io, TMP_INVERT_TX_TRIG_VAL_OPT);
	tmp_tog_rcv_optflag(&tmp_io, TMP_INVERT_RX_TRIG_VAL_OPT);

	while(1) {
	fprintf(stdout, "send_success: %s.\n", tmp_send(&tmp_io, tmp_io_buff(data_to_send, sizeof(data_to_send))) == TMP_SUCCESS? "yes":"no");
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

	tmp_init(&tmp_io, &cl_set_pmode, &cl_set_pstate, &cl_get_pstate);
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t timeo = 1000000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_FLIP_BIT_OPT);
	tmp_io.snd_holdup_ic = 2;
	tmp_io.rcv_holdup_ic = 2;
	tmp_tog_snd_optflag(&tmp_io, TMP_INVERT_TX_TRIG_VAL_OPT);
	tmp_tog_rcv_optflag(&tmp_io, TMP_INVERT_RX_TRIG_VAL_OPT);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);
	while(1) {
	mdl_u8_t data[sizeof(data_to_send)];
	memset(data, 0x0, sizeof(data_to_send));
	fprintf(stdout, "recv_success?: %s.\n", tmp_recv(&tmp_io, tmp_io_buff(data, sizeof(data_to_send))) == TMP_SUCCESS? "yes":"no");
	fprintf(stdout, "recved: %s, is_correct? %s.\n", data, !memcmp(data_to_send, data, sizeof(data_to_send))? "yes":"no");
	}
	return NULL;
}

int main() {
	tmp_err_t a;
	pthread_t se_th, cl_th;
	pthread_create(&se_th, NULL, se, NULL);
	pthread_create(&cl_th, NULL, cl, NULL);

	pthread_join(se_th, NULL);
	pthread_join(cl_th, NULL);
}
