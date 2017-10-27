# include "forward.h"
tmp_err_t extern tmp_rcv(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
tmp_err_t extern tmp_snd(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
void tmp_forward(struct tmp_io *__tmp_io) {
	mdl_u16_t iface_no = 0x00;
	struct tmp_packet pkbuf[200];
	mdl_u8_t data_buff[200];
	mdl_uint_t bc;
	tmp_io_buf_t io_buff;
	tmp_err_t any_err;
	while((iface_no&0xFF) != __tmp_io->iface_c) {
		tmp_set_iface_no(__tmp_io, iface_no&0xFF);
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp_forward, set iface no to '%u'\n", iface_no&0xFF);
# endif
		io_buff = tmp_io_buff(data_buff, 0x0);
		if ((any_err = tmp_rcv(__tmp_io, &io_buff, 0x0, TMP_FLG_RBS, pkbuf)) != TMP_SUCCESS) goto _sk;
		bc = io_buff.bc;
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp_forward, recved %u bytes of data on iface %u. %u\n", io_buff.bc, iface_no&0xFF, *data_buff);
# endif
		iface_no<<=8;
		while((iface_no&0xFF) != __tmp_io->iface_c) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp_forward, -- iface_no: %u\n", iface_no&0xFF);
# endif
			if ((iface_no&0xFF) != iface_no>>8) {
				tmp_set_iface_no(__tmp_io, iface_no&0xFF);
				struct tmp_msg msg = {
					.kind=_msg_route,
					.lu_addr=pkbuf->dst_addr
				};
				printf("dst: %u\n", pkbuf->dst_addr);

				io_buff = tmp_io_buff(&msg, sizeof(struct tmp_msg));
				if (tmp_snd(__tmp_io, &io_buff, 0x0, TMP_FLG_MSG, NULL) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
					fprintf(stderr, "tmp_forward, failed to send message.\n");
# endif
				}
				mdl_u8_t found = 0x0;
				tmp_rcv_bit(__tmp_io, &found);
				if (found) {
# ifdef __DEBUG_ENABLED
					fprintf(stdout, "found. sending data %u to iface %u\n\n", *data_buff, iface_no&0xFF);
# endif
					mdl_u8_t route[24];
					io_buff = tmp_io_buff(route, 0x0);
					tmp_rcv(__tmp_io, &io_buff, 0x0, TMP_FLG_RBS, NULL);
					printf("-------------------> %u\n", *route);

					io_buff = tmp_io_buff(data_buff, bc);
					tmp_snd(__tmp_io, &io_buff, 0x0, 0x0, pkbuf);
					return;
				}
			}

			iface_no = (iface_no^(iface_no&0xFF))|((iface_no&0xFF)+1);
		}
		iface_no>>=8;

		_sk:
		iface_no = (iface_no^(iface_no&0xFF))|((iface_no&0xFF)+1);
	}
}
