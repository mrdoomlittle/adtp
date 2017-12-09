# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <mdlint.h>
# include <unistd.h>
# include <string.h>
# include <mdl/tmp_io.h>
# include <pthread.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdatomic.h>
# include <time.h>
# define TMP_RX_IC_PID 0
# define TMP_TX_IC_PID 1
# define TMP_RX_PID 2

# define TMP_RX_OC_PID 3
# define TMP_TX_OC_PID 4
# define TMP_TX_PID 5
# define NOP "nop"
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
// bits
mdl_u8_t pins[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
mdl_u8_t port_id = 0;
atomic_uchar port_c = 0;

void set_port_id(mdl_u8_t __id) {
	pthread_mutex_lock(&m1);
	port_id = __id;
	pthread_mutex_unlock(&m1);
	__asm__(NOP);
}

mdl_u8_t get_port_id() {
	mdl_u8_t id;
	pthread_mutex_lock(&m1);
	id = port_id;
	pthread_mutex_unlock(&m1);
	__asm__(NOP);
	return id;
}

void set_pin_mode(mdl_u8_t __mode, mdl_u8_t __id) {}
void set_pin_state(mdl_u8_t __state, mdl_u8_t __id) {
	__state = ~__state&0x1;
	pthread_mutex_lock(&m1);
	if ((pins[port_id]>>__id&0x1) != __state) {
		if (__state)
			pins[port_id] |= 1<<__id;
		else
			pins[port_id] ^= 1<<__id;
	}

	pthread_mutex_unlock(&m1);
	__asm__(NOP);
}

mdl_u8_t get_pin_state(mdl_u8_t __id) {
	pthread_mutex_lock(&m1);
	mdl_u8_t ret_val = pins[port_id]>>__id&0x1;
	pthread_mutex_unlock(&m1);
	__asm__(NOP);
	return ret_val;
}

int sock;
mdl_u8_t static cc_flag = 0;
void ctrl_c(int __sig) {
	cc_flag = 0x1;
	shutdown(sock, SHUT_RDWR);
	exit(0);
}
# include <mdl/forward.h>

void* m(void *__arg_p) {
	struct tmp_io *tmp_io = (struct tmp_io*)__arg_p;

//	mdl_u8_t data = 212;
//	mdl_u8_t _port_id;
	_again:
/*
	_port_id = 0;
	for(;_port_id != port_c;_port_id++) {
		pthread_mutex_lock(&m2);
		tmp_set_port_id(tmp_io, _port_id);
		tmp_send(tmp_io, tmp_io_buff(&data, 1), 0);
		pthread_mutex_unlock(&m2);
		printf("sent: %u, to %u\n\n", data, _port_id);
	}
*/
	pthread_mutex_lock(&m2);
	tmp_forward(tmp_io);
	pthread_mutex_unlock(&m2);
	__asm__(NOP);
	goto _again;
	return NULL;
}


void holdup(mdl_uint_t __holdup) {if (__holdup != 0) usleep(__holdup);}

int main(void) {
	signal(SIGINT, ctrl_c);
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "failed to create socket.\n");
		return -1;
	}

	struct sockaddr_in dst, src;
	bzero(&dst, sizeof(struct sockaddr_in));

	dst.sin_family = AF_INET;
	dst.sin_addr.s_addr = htons(INADDR_ANY);

	dst.sin_port = htons(21299);

	int sndbuf_size = 44000;
	int rcvbuf_size = 44000;
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf_size, sizeof(int));
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, sizeof(int));

//	struct timeval tv = {
//		.tv_sec = 2,
//		.tv_usec = 0
//	};

//	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (void*)&tv, sizeof(struct timeval));
//	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (void*)&tv, sizeof(struct timeval));

	if (bind(sock, (struct sockaddr*)&dst, sizeof(struct sockaddr_in)) < 0) {
		fprintf(stderr, "failed to bind socket.\n");
		return -1;
	}

	ssize_t bc;
	socklen_t len = sizeof(struct sockaddr_in);

	pthread_t thread;
	struct tmp_io tmp_io = {
		.rx_pid = TMP_RX_PID,
		.tx_pid = TMP_TX_PID,
		.rx_ci_pid = TMP_RX_IC_PID,
		.tx_ci_pid = TMP_TX_IC_PID,
		.rx_co_pid = TMP_RX_OC_PID,
		.tx_co_pid = TMP_TX_OC_PID
	};

	tmp_io.set_port_id = &set_port_id;
	tmp_io.get_port_id = &get_port_id;
	tmp_init(&tmp_io, &set_pin_mode, &set_pin_state, &get_pin_state, 0, 0, 4);
	tmp_io.divider = _d16;

	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t cutoff = 20000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_io.snd_holdup_ic = 1;
	tmp_io.rcv_holdup_ic = 1;
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_CUTOFF, &cutoff);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_CUTOFF, &cutoff);
	tmp_err_t err;
	tmp_prepare(&tmp_io);
//	tmp_add_iface(&tmp_io, tmp_addr_from_str("0.0.0.0", &err), 0);

	pthread_create(&thread, NULL, &m, (void*)&tmp_io);

 	mdl_u16_t temp;
	mdl_u8_t my_id = 0;
	mdl_u64_t ups = 0;
	printf("now online.\n");
	struct timespec begin, now;
    clock_gettime(CLOCK_MONOTONIC, &begin);
	_loop:
	clock_gettime(CLOCK_MONOTONIC, &now);
	if ((now.tv_sec-begin.tv_sec) >= 1) {
		begin.tv_sec = now.tv_sec;
		printf("--{%lu UPS}\n", ups);
		ups = 0;
	}

	if (cc_flag) {
		pthread_kill(thread, 0);
		goto _end;
	}

	bzero(&src, sizeof(struct sockaddr_in));

	temp = 0;
	if ((bc = recvfrom(sock, &temp, sizeof(mdl_u16_t), 0, (struct sockaddr*)&src, &len)) < 0) {
		printf("error.\n");
	}
//	printf("%u\n", temp&0x7);

	if ((my_id = (temp>>8)) == 0xFF) {
		if ((bc = sendto(sock, &port_c, 1, 0, (struct sockaddr*)&src, sizeof(struct sockaddr_in))) < 0) {
			printf("error.\n");
		}

		printf("client conencted with id: %u\n", port_c);
		pthread_mutex_lock(&m2);
		tmp_add_iface(&tmp_io, tmp_addr_from_str("0.0.0.0", &err), 0);
		pthread_mutex_unlock(&m2);
		__asm__(NOP);
		my_id = port_c++;
	}

	pthread_mutex_lock(&m1);
	pins[my_id] = (pins[my_id]^(pins[my_id]&0x7))|(temp&0x7);
	temp = (pins[my_id]>>3)&0x7;
	if ((bc = sendto(sock, &temp, 1, 0, (struct sockaddr*)&src, sizeof(struct sockaddr_in))) < 0) {
		printf("error.\n");
	}
	pthread_mutex_unlock(&m1);
	__asm__(NOP);
	ups++;
	goto _loop;
	_end:
	close(sock);
	return 0;
}
