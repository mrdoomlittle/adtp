# include <pthread.h>
# include "tmp_io.h"

# define TMP_RX_IC_PID 2
# define TMP_RX_OC_PID 3

# define TMP_TX_IC_PID 4
# define TMP_TX_OC_PID 5

# define TMP_RX_PID 6
# define TMP_TX_PID 7

uint8_t se_pinset[12] = {0x0}, cl_pinset[12] = {0x0};

void se_set_pmode(uint8_t __pmode, uint8_t __pid) {}
void se_set_pstate(uint8_t __pstate, uint8_t __pid) {
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

void holdup(mdl_uint_t __holdup) {
	for (int x = 0; x != 12872; x ++){}
}

void se() {
struct tmp_io_t tmp_io = { 
	.rx_pid = TMP_RX_PID,
	.tx_pid = TMP_TX_PID,
	.rx_ci_pid = TMP_RX_IC_PID,
	.tx_ci_pid = TMP_TX_IC_PID,
	.rx_co_pid = TMP_RX_OC_PID,
	.tx_co_pid = TMP_TX_OC_PID
};
	tmp_init(&tmp_io, &se_set_pmode, &se_set_pstate, &se_get_pstate);
	tmp_set_holdup_fptr(&tmp_io, &holdup);
	mdl_uint_t timeo = 2000;

	tmp_io.snd_holdup_ic = 12;
	tmp_io.rcv_holdup_ic = 12;
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);

	while(1) {
	static mdl_u8_t hello[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	tmp_send(&tmp_io, tmp_io_buff(hello, 6));
//	holdup(0);
	static mdl_u8_t world[6] = {'W', 'o', 'r', 'l', 'd', '\0'};
	tmp_send(&tmp_io, tmp_io_buff(world, 6));
	printf("sent data.\n");
	}
}

void cl() {
struct tmp_io_t tmp_io = {
.rx_pid = TMP_RX_PID,
.tx_pid = TMP_TX_PID,
.rx_ci_pid = TMP_RX_IC_PID,
.tx_ci_pid = TMP_TX_IC_PID,
.rx_co_pid = TMP_RX_OC_PID,
.tx_co_pid = TMP_TX_OC_PID
};

	tmp_init(&tmp_io, &cl_set_pmode, &cl_set_pstate, &cl_get_pstate);
	tmp_set_holdup_fptr(&tmp_io, &holdup);
	mdl_uint_t timeo = 2000;

	tmp_io.snd_holdup_ic = 12;
	tmp_io.rcv_holdup_ic = 12;
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);
	while(1) {
	mdl_u8_t data[6] = {'\0'};
	tmp_recv(&tmp_io, tmp_io_buff(data, 6));
	printf("recved: %s\n", data);
	memset(data, '\0', 6);
	tmp_recv(&tmp_io, tmp_io_buff(data, 6));
	printf("recved: %s\n", data);
	}
}

int main() {
	pthread_t se_th, cl_th;
	pthread_create(&se_th, NULL, se, NULL);
	pthread_create(&cl_th, NULL, cl, NULL);

	pthread_join(se_th, NULL);
	pthread_join(cl_th, NULL);
}
