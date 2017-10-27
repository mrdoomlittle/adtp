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
# include <time.h>
# define TMP_RX_IC_PID 0
# define TMP_TX_IC_PID 1
# define TMP_RX_PID 2

# define TMP_RX_OC_PID 3
# define TMP_TX_OC_PID 4
# define TMP_TX_PID 5
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

# define NOP "nop"
void set_iface_no(mdl_u8_t __no) {
}

mdl_u8_t get_iface_no() {
	return 0;
}

mdl_u8_t pins = 0;
void set_pin_mode(mdl_u8_t __mode, mdl_u8_t __id) {}
void set_pin_state(mdl_u8_t __state, mdl_u8_t __id) {
	__state = ~__state&0x1;
	pthread_mutex_lock(&mutex);
	if ((pins>>__id&0x1) != __state) {
	if (__state)
			pins |= 1<<__id;
		else
			pins ^= 1<<__id;
	}

	pthread_mutex_unlock(&mutex);
	__asm__(NOP);
}

mdl_u8_t get_pin_state(mdl_u8_t __id) {
	pthread_mutex_lock(&mutex);
	mdl_u8_t ret_val = pins>>__id&0x1;
	pthread_mutex_unlock(&mutex);
	__asm__(NOP);
	return ret_val;
}

int sock;
mdl_u8_t static cc_flag = 0;
void ctrl_c(int __sig) {
	cc_flag = 0x1;
	shutdown(sock, SHUT_RDWR);
}

enum {
	OP_SND,
	OP_RCV
};

tmp_addr_t to_addr;
tmp_addr_t from_addr;

mdl_u8_t op = 0;
void* m(void *__arg_p) {
	struct tmp_io *tmp_io = (struct tmp_io*)__arg_p;

	mdl_u8_t data;
	tmp_err_t err;
	_again:
	if (op == OP_SND) {
		data = 212;
		err = tmp_send(tmp_io, tmp_io_buff(&data, 1), to_addr);

		printf("sent: %u\n", data);
		fprintf(stdout, "send_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");
	} else if (op == OP_RCV) {
		data = 0;
		err = tmp_recv(tmp_io, tmp_io_buff(&data, 1), from_addr);

		printf("recved: %u\n", data);
		fprintf(stdout, "recv_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");
	}
	goto _again;
	return NULL;
}

void holdup(mdl_uint_t __holdup) {if (__holdup != 0) usleep(__holdup);}

int main(int __argc, char const *__argv[]) {
	tmp_err_t err;
	if (*__argv[1] == 's') {
		op = OP_SND;
		to_addr = tmp_addr_from_str(__argv[3], &err);
	} else if (*__argv[1] == 'r') {
		op = OP_RCV;
		from_addr = tmp_addr_from_str(__argv[3], &err);
	}
	signal(SIGINT, ctrl_c);
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "failed to create socket.\n");
		return -1;
	}

	struct sockaddr_in dst;
    bzero(&dst, sizeof(struct sockaddr_in));

	dst.sin_family = AF_INET;
	dst.sin_port = htons(21299);
	inet_pton(AF_INET, "127.0.1", &dst.sin_addr);

	int sndbuf_size = 65536;
	int rcvbuf_size = 65536;
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf_size, sizeof(int));
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, sizeof(int));

//	struct timeval tv = {
//		.tv_sec = 2,
//		.tv_usec = 0
//	};

//	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (void*)&tv, sizeof(struct timeval));
//	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (void*)&tv, sizeof(struct timeval));

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
	tmp_init(&tmp_io, &set_pin_mode, &set_pin_state, &get_pin_state, 0, 0);
	tmp_io.divider = _d32;
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t cutoff = 10000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_io.snd_holdup_ic = 1;
	tmp_io.rcv_holdup_ic = 1;
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_CUTOFF, &cutoff);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_CUTOFF, &cutoff);
	tmp_io.set_iface_no_fp = &set_iface_no;
	tmp_io.get_iface_no_fp = &get_iface_no;
	tmp_prepare(&tmp_io);

	if (op == OP_SND)
		tmp_add_iface(&tmp_io, tmp_addr_from_str(__argv[2], &err), 0);
	else if (op == OP_RCV)
		tmp_add_iface(&tmp_io, tmp_addr_from_str(__argv[2], &err), 0);
	set_pin_state(1, 3);
	pthread_create(&thread, NULL, &m, (void*)&tmp_io);
	mdl_u16_t temp;
	mdl_u8_t id = 0xFF;
	mdl_u64_t ups = 0;
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

	pthread_mutex_lock(&mutex);
	temp = ((pins>>3)&0x7)|(id<<8);
//	printf("sent: %u\n", (pins>>3)&0x7);
	if ((bc = sendto(sock, &temp, sizeof(mdl_u16_t), 0, (struct sockaddr*)&dst, sizeof(struct sockaddr_in))) <= 0) {
		printf("error.\n");
	}

	if (id == 0xFF) {
		id = 0x0;
		if ((bc = recvfrom(sock, &id, 1, 0, (struct sockaddr*)&dst, &len)) <= 0) {
			printf("error.\n");
		}
		printf("my id is '%u'\n", id);
	}

	temp = 0;
	if ((bc = recvfrom(sock, &temp, 1, 0, (struct sockaddr*)&dst, &len)) <= 0) {
		printf("error.\n");
	}
	pins = (pins^(pins&0x7))|(temp&0x7);
	pthread_mutex_unlock(&mutex);
	__asm__(NOP);
	ups++;
	usleep(100);
	goto _loop;
	_end:
	close(sock);
}
