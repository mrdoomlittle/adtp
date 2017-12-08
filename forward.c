# include "forward.h"
tmp_err_t tmp_rcv(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
tmp_err_t tmp_snd(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
tmp_err_t send_key_and_sync(struct tmp_io*);
tmp_err_t recv_key_and_sync(struct tmp_io*);
tmp_err_t tmp_snd_pkt(struct tmp_io*, struct tmp_packet*);
tmp_err_t tmp_rcv_pkt(struct tmp_io*, struct tmp_packet*);
tmp_err_t tmp_snd_prepare(struct tmp_io*, mdl_u8_t*, mdl_u8_t);
tmp_err_t tmp_rcv_prepare(struct tmp_io*, mdl_u8_t, mdl_u8_t*);
tmp_err_t tmp_snd_ack(struct tmp_io*, mdl_u8_t);
tmp_err_t tmp_rcv_ack(struct tmp_io*, mdl_u8_t*);
void tmp_sigwait(struct tmp_io*);
tmp_err_t tmp_signal(struct tmp_io*);
void tmp_forward(struct tmp_io *__tmp_io) {
	static struct tmp_packet pk;
	mdl_u8_t static *buf = NULL;

	if (buf == NULL)
		buf = (mdl_u8_t*)malloc(TMP_PKT_MSS);

	pk.io_buff.p = buf;

	struct tmp_port *end = __tmp_io->ports+__tmp_io->port_c;
	struct tmp_port *src = __tmp_io->ports;
	struct tmp_port *dst;
	mdl_u8_t s_flags = 0x0, r_flags = TMP_FLG_RBS;
	mdl_uint_t bc;
	while(src != end) {
		bc = 0;
		tmp_set_port_id(__tmp_io, src->id);
# ifdef __TMP_DEBUG
		fprintf(stdout, "listening port %u\n", src->id);
# endif
		if (!tmp_is_flag(src->flags, TMP_FLG_INUSE)) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "preparing...\n");
			fprintf(stdout, "sending signal.\n");
# endif
			if (_err(tmp_signal(__tmp_io))) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "failed to signal.\n");
# endif
				goto _sk;
			}
# ifndef __TMP_DEBUG
			fprintf(stdout, "signal sent.\n");
# endif
			// wait for reply
			tmp_sigwait(__tmp_io);

			if (_err(tmp_rcv_prepare(__tmp_io, r_flags, &s_flags))) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "failed to prepare.\n");
# endif
				goto _sk;
			}
			if (_err(tmp_rcv_16l(__tmp_io, (mdl_u16_t*)&bc))) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "failed to recv buffer size.\n");
# endif
				goto _sk;
			}
# ifdef __TMP_DEBUG
			fprintf(stdout, "finished preparing. total to be recved %u\n", bc);
# endif
		}

		pk.io_buff.bc = bc;
		if (_err(tmp_rcv_pkt(__tmp_io, &pk))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "failed to recv packet.\n");
# endif
			if (tmp_is_flag(src->flags, TMP_FLG_INUSE)) {
				src->left = 0;
				tmp_tog_flag(&src->flags, TMP_FLG_INUSE);
				src->by = NULL;
			}
			goto _sk;
		}

		tmp_snd_ack(__tmp_io, ACK_SUCCESS);
		if (!tmp_is_flag(src->flags, TMP_FLG_INUSE)) {
			if (bc > TMP_PKT_MSS) {
				src->left = bc;
				tmp_tog_flag(&src->flags, TMP_FLG_INUSE);
			}
		}

# ifdef __TMP_DEBUG
		fprintf(stdout, "recved packet. %u\n", *buf);
# endif
		if (src->by != NULL) {
			if (_err(tmp_snd_pkt(__tmp_io, &pk))) goto _sk;
		} else {

		dst = __tmp_io->ports;
		while(dst != end) {
			if (dst != src) {
			tmp_set_port_id(__tmp_io, dst->id);
			struct tmp_msg msg = {
				.kind=_msg_route,
				.lu_addr=pk.dst_addr
			};

			tmp_io_buf_t io_buff = tmp_io_buff(&msg, sizeof(struct tmp_msg));
			if (_err(tmp_snd(__tmp_io, &io_buff, 0x0, TMP_FLG_MSG, NULL))) goto _sk;

			mdl_u8_t found = 0x0;
			if (_err(tmp_rcv_bit(__tmp_io, &found))) goto _sk;
			if (found) {
				mdl_u8_t route[24];
				io_buff = tmp_io_buff(route, 0x0);
				if (_err(tmp_rcv(__tmp_io, &io_buff, 0x0, TMP_FLG_RBS, NULL))) goto _sk;
				if (_err(tmp_snd_prepare(__tmp_io, 0x0, 0x0))) goto _sk;

				if (_err(tmp_snd_pkt(__tmp_io, &pk))) goto _sk;
				if (tmp_is_flag(src->flags, TMP_FLG_INUSE))
					src->by = dst;
				break;
			}
			}
			dst++;
		}

		}

		if (tmp_is_flag(src->flags, TMP_FLG_INUSE)) {
			src->left-= pk.io_buff.bc;
			if (src->left == 0)
				tmp_tog_flag(&src->flags, TMP_FLG_INUSE);
			src->by = NULL;
		}

		_sk:
		src++;
	}

	return;
/*
	mdl_u16_t iface_no = 0x00;
	struct tmp_packet pk;
	mdl_u8_t from_initc[I__];
	mdl_u8_t to_initc[I__];
	mdl_u16_t left[I__*8];

	mdl_u8_t data_buff[200];
	mdl_uint_t bc;
	tmp_io_buf_t io_buff;
	tmp_err_t any_err;
	mdl_u8_t s_flags = 0x0, r_flags = TMP_FLG_RBS;
	while((iface_no&0xFF) != __tmp_io->iface_c) {
		tmp_set_iface_no(__tmp_io, iface_no&0xFF);
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp_forward, set iface no to '%u'\n", iface_no&0xFF);
# endif
		mdl_u8_t iface = iface_no&0xFF;
		if (!(from_initc[iface>>4]&(0x1<<(iface-((iface>>4)<<4))))) {
			if (send_key_and_sync(__tmp_io) != TMP_SUCCESS) goto _sk;
			if (recv_key_and_sync(__tmp_io) != TMP_SUCCESS) goto _sk;

			if (tmp_snd_nib(__tmp_io, r_flags) != TMP_SUCCESS) goto _sk;
			if (tmp_rcv_nib(__tmp_io, &s_flags) != TMP_SUCCESS) goto _sk;

			if (tmp_rcv_16l(__tmp_io, &(left[iface])) != TMP_SUCCESS) goto _sk;
			SET_INIT(from_initc, iface);
		} else {
			if (!left[iface]) {
				USET_INIT(from_initc, iface);
				goto _sk;
			}
			tmp_rcv_pkt(__tmp_io, &pk);
			if (pk.io_buff.bc > left[iface]) {
				//err
				goto _sk;
			}
			left[iface] -= pk.io_buff.bc;
		}
//		io_buff = tmp_io_buff(data_buff, 0x0);
//		if ((any_err = tmp_rcv(__tmp_io, &io_buff, 0x0, TMP_FLG_RBS, pkbuf)) != TMP_SUCCESS) goto _sk;
//		bc = io_buff.bc;
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp_forward, recved %u bytes of data on iface %u.\n", io_buff.bc, iface_no&0xFF);
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
					.lu_addr=pk.dst_addr
				};
				printf("dst: %u\n", pk.dst_addr);

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
					fprintf(stdout, "found. iface %u\n\n", iface_no&0xFF);
# endif
					mdl_u8_t route[24];
					io_buff = tmp_io_buff(route, 0x0);
					tmp_rcv(__tmp_io, &io_buff, 0x0, TMP_FLG_RBS, NULL);
					printf("-------------------> %u\n", *route);

				//	io_buff = tmp_io_buff(data_buff, bc);
				//	tmp_snd(__tmp_io, &io_buff, 0x0, 0x0, pkbuf);

					mdl_u8_t iface = iface_no&0xFF, from_iface = iface_no>>8;
					if (!(to_initc[iface>>4]&(0x1<<(iface-((iface>>4)<<4))))) {
						if (send_key_and_sync(__tmp_io) != TMP_SUCCESS) goto _sk;
						if (recv_key_and_sync(__tmp_io) != TMP_SUCCESS) goto _sk;

						if (tmp_snd_nib(__tmp_io, r_flags) != TMP_SUCCESS) goto _sk;
						if (tmp_rcv_nib(__tmp_io, NULL) != TMP_SUCCESS) goto _sk;
						SET_INIT(to_initc, iface);
					}

					if (tmp_snd_pkt(__tmp_io, &pk) != TMP_SUCCESS) goto _sk;

					if (!(left[from_iface]-pk.io_buff.bc)) {
						USET_INIT(to_initc, iface);
					}

					return;
				}
			}

			iface_no = (iface_no^(iface_no&0xFF))|((iface_no&0xFF)+1);
		}
		iface_no>>=8;

		_sk:
		iface_no = (iface_no^(iface_no&0xFF))|((iface_no&0xFF)+1);
	}
*/
}
