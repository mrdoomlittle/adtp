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
void set_port_id(mdl_u8_t __id) {
}

mdl_u8_t get_port_id() {
	return 0;
}

mdl_u8_t id = 0xFF;
mdl_u8_t pins = 0;
void io_set_direct(mdl_u8_t __dir, mdl_u8_t __id) {}
void io_set_val(mdl_u8_t __val, mdl_u8_t __id) {
	__val = ~__val&0x1;
	pthread_mutex_lock(&mutex);
	if ((pins>>__id&0x1) != __val) {
	if (__val)
			pins |= 1<<__id;
		else
			pins ^= 1<<__id;
	}

	pthread_mutex_unlock(&mutex);
	__asm__(NOP);
}

mdl_u8_t io_get_val(mdl_u8_t __id) {
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
	exit(0);
}

enum {
	OP_SND,
	OP_RCV
};

tmp_addr_t to_addr;
tmp_addr_t from_addr;
mdl_u8_t op = 0;
# define BUFF_SIZE 70
void* m(void *__arg_p) {
	struct tmp_io *tmp_io = (struct tmp_io*)__arg_p;
	char static *buf = NULL;
	if (buf == NULL)
		buf = (char*)malloc(BUFF_SIZE);
	tmp_err_t err;
	_again:
	memset(buf, '\0', BUFF_SIZE);
	if (op == OP_SND) {
		sprintf(buf, "|------< https://github.com/mrdoomlittle/tmp >------| -> %u", id);
		err = tmp_send(tmp_io, tmp_io_buff(buf, BUFF_SIZE), to_addr);

		printf("sent: %s\n", buf);
		fprintf(stdout, "send_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");
	} else if (op == OP_RCV) {
		err = tmp_recv(tmp_io, tmp_io_buff(buf, BUFF_SIZE), from_addr);

		printf("recved: %s\n", buf);
		fprintf(stdout, "recv_success?: %s.\n", err == TMP_SUCCESS? "yes":"no");
	}
	goto _again;
	return NULL;
}

void holdup(mdl_uint_t __holdup) {if (__holdup != 0) usleep(__holdup);}
int main(int __argc, char const *__argv[]) {
	tmp_err_t err;
	if (__argc != 4) {
		fprintf(stdout, "usage: [s,r] [to/from addr] [interface addr]\n");
		return -1;
	}

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
	inet_pton(AF_INET, "127.0.0.1", &dst.sin_addr);

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
	tmp_init(&tmp_io, &io_set_direct, &io_set_val, &io_get_val, &holdup, 0, 0, 1);
	tmp_io.divider = _d32;
	mdl_uint_t cutoff = 100000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_io.snd_holdup_ic = 1;
	tmp_io.rcv_holdup_ic = 1;
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_CUTOFF, &cutoff);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_CUTOFF, &cutoff);
	tmp_io.set_port_id = &set_port_id;
	tmp_io.get_port_id = &get_port_id;
	tmp_prepare(&tmp_io);

	if (op == OP_SND)
		tmp_add_iface(&tmp_io, tmp_addr_from_str(__argv[2], &err), 0);
	else if (op == OP_RCV)
		tmp_add_iface(&tmp_io, tmp_addr_from_str(__argv[2], &err), 0);
	io_set_val(1, 3);
	pthread_create(&thread, NULL, &m, (void*)&tmp_io);
	mdl_u16_t temp;
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
//	printf(".\n");
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
	usleep(1000);
	goto _loop;
	_end:
	close(sock);
}
