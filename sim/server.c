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
# define TMP_RX_IC_PID 0
# define TMP_TX_IC_PID 1
# define TMP_RX_PID 2

# define TMP_RX_OC_PID 3
# define TMP_TX_OC_PID 4
# define TMP_TX_PID 5
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

mdl_u8_t pins[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
mdl_u8_t iface_no = 0;
atomic_uchar iface_c = 0;

void set_iface_no(mdl_u8_t __no) {
	pthread_mutex_lock(&mutex);
	iface_no = __no;
	pthread_mutex_unlock(&mutex);
	__asm__("nop");
}

void set_pin_mode(mdl_u8_t __mode, mdl_u8_t __id) {}
void set_pin_state(mdl_u8_t __state, mdl_u8_t __id) {
	__state = ~__state&0x1;
	pthread_mutex_lock(&mutex);
	if (__state)
		pins[iface_no] |= 1<<__id;
	else
		pins[iface_no] ^= 1<<__id;
	pthread_mutex_unlock(&mutex);
	__asm__("nop");
}

mdl_u8_t get_pin_state(mdl_u8_t __id) {
	pthread_mutex_lock(&mutex);
	mdl_u8_t ret_val = (pins[iface_no]>>__id)&0x1;
	pthread_mutex_unlock(&mutex);
	__asm__("nop");
	return ret_val;
}

int sock;
mdl_u8_t static cc_flag = 0;
void ctrl_c(int __sig) {
	cc_flag = 0x1;
	shutdown(sock, SHUT_RDWR);
}

void* m(void *__arg_p) {
	struct tmp_io *tmp_io = (struct tmp_io*)__arg_p;

	mdl_u8_t data = 212;
	mdl_u8_t _iface_no;
	_again:
	_iface_no = 0;
	for(;_iface_no != iface_c;_iface_no++) {
		tmp_set_iface_no(tmp_io, _iface_no);
		tmp_send(tmp_io, tmp_io_buff(&data, 1), 0);
		printf("sent: %u, to %u\n\n", data, _iface_no);
	}

	goto _again;
	return NULL;
}


void holdup(mdl_uint_t __holdup) {usleep(30);}

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

	int sndbuf_size = 1024;
	int rcvbuf_size = 1024;
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf_size, sizeof(int));
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, sizeof(int));

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

	tmp_io.set_iface_no_fp = &set_iface_no;
	tmp_init(&tmp_io, &set_pin_mode, &set_pin_state, &get_pin_state, 0, 0);
	tmp_set_holdup_fp(&tmp_io, &holdup);
	mdl_uint_t timeo = 10000;

	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_FLIP_BIT);
	tmp_io.snd_holdup_ic = 2;
	tmp_io.rcv_holdup_ic = 2;
	tmp_tog_snd_optflag(&tmp_io, TMP_OPT_INV_TX_TRIG_VAL);
	tmp_tog_rcv_optflag(&tmp_io, TMP_OPT_INV_RX_TRIG_VAL);
	tmp_set_opt(&tmp_io, TMP_OPT_SND_TIMEO, &timeo);
	tmp_set_opt(&tmp_io, TMP_OPT_RCV_TIMEO, &timeo);

	pthread_create(&thread, NULL, &m, (void*)&tmp_io);

 	mdl_u16_t temp;
	mdl_u8_t my_id = 0;
	printf("now online.\n");
	_loop:
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
		if ((bc = sendto(sock, &iface_c, 1, 0, (struct sockaddr*)&src, sizeof(struct sockaddr_in))) < 0) {
			printf("error.\n");
		}

		printf("client conencted with id: %u\n", iface_c);
		my_id = iface_c++;
	}

	pthread_mutex_lock(&mutex);
	pins[my_id] = (pins[my_id]^(pins[my_id]&0x7))|(temp&0x7);
	temp = (pins[my_id]>>3)&0x7;
	if ((bc = sendto(sock, &temp, 1, 0, (struct sockaddr*)&src, sizeof(struct sockaddr_in))) < 0) {
		printf("error.\n");
	}
	pthread_mutex_unlock(&mutex);
	usleep(800);
	__asm__("nop");
	goto _loop;
	_end:
	close(sock);
	return 0;
}
