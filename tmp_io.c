# include "tmp_io.h"
mdl_u8_t tmp_gpio_high = 0x1, tmp_gpio_low = 0x0;
mdl_u8_t tmp_gpio_in = 0x0, tmp_gpio_out = 0x1;

mdl_u8_t rx_clk_trig_val;
mdl_u8_t tx_clk_trig_val;
mdl_uint_t tmp_null;

void static tmp_set_pin_mode(struct tmp_io*, mdl_u8_t, mdl_u8_t);
void static tmp_set_pin_state(struct tmp_io*, mdl_u8_t, mdl_u8_t);
mdl_u8_t static tmp_get_pin_state(struct tmp_io*, mdl_u8_t);

tmp_err_t tmp_init(struct tmp_io *__tmp_io, void(*__set_pin_mode_fp)(mdl_u8_t, mdl_u8_t), void(*__set_pin_state_fp)(mdl_u8_t, mdl_u8_t), mdl_u8_t(*__get_pin_state_fp)(mdl_u8_t)
# ifndef __TMP_LIGHT
, tmp_method_t __tr_method, tmp_flag_t __flags
# endif
) {
	__tmp_io->set_pin_mode_fp = __set_pin_mode_fp;
	__tmp_io->set_pin_state_fp = __set_pin_state_fp;
	__tmp_io->get_pin_state_fp = __get_pin_state_fp;
	__tmp_io->holdup_fp = NULL;

	tmp_set_pin_mode(__tmp_io, tmp_gpio_in, __tmp_io->rx_pid);
	tmp_set_pin_mode(__tmp_io, tmp_gpio_in, __tmp_io->rx_ci_pid); // msg: me recv data
	tmp_set_pin_mode(__tmp_io, tmp_gpio_out, __tmp_io->rx_co_pid); // msg: node recv data

	tmp_set_pin_mode(__tmp_io, tmp_gpio_out, __tmp_io->tx_pid);
	tmp_set_pin_mode(__tmp_io, tmp_gpio_in, __tmp_io->tx_ci_pid); // msg: me send data
	tmp_set_pin_mode(__tmp_io, tmp_gpio_out, __tmp_io->tx_co_pid); // msg: node send data

	rx_clk_trig_val = tmp_gpio_low;
	tx_clk_trig_val = tmp_gpio_low;

	tmp_set_pin_state(__tmp_io, ~rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);
	tmp_set_pin_state(__tmp_io, tmp_gpio_low, __tmp_io->tx_pid);
	tmp_set_pin_state(__tmp_io, ~tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);

	__tmp_io->snd_timeo = 0;
	__tmp_io->snd_timeo_ic = 0;

	__tmp_io->rcv_timeo = 0;
	__tmp_io->rcv_timeo_ic = 0;

	__tmp_io->snd_holdup_ic = 0;
	__tmp_io->rcv_holdup_ic = 0;
    __tmp_io->snd_holdup = 0;
	__tmp_io->rcv_holdup = 0;
	__tmp_io->snd_optflags = 0;
	__tmp_io->rcv_optflags = 0;

# ifndef __TMP_LIGHT
	__tmp_io->flags = __flags|TMP_DEF_FLAGS;
# endif
	tmp_holdup(__tmp_io, 200, 0);
	return TMP_SUCCESS;
}

# ifndef __TMP_LIGHT
mdl_u32_t tmp_cal_sv(mdl_u8_t *__p, mdl_uint_t __bc) {
	mdl_u32_t ret_val = 0;
	mdl_u8_t *itr = __p;
	while(itr != __p+__bc) ret_val += *(itr++);
	return ret_val;
}

mdl_u32_t tmp_addr_from_str(char unsigned const *__addr, tmp_err_t *__any_err) {
	mdl_u32_t addr = 0x000000, addr_off = 0;
	mdl_u8_t addr_bit = 0, no_unit = 1, nu_cald = 0;
	for (mdl_u8_t ic = 0;; ic++) {
		if (__addr[ic] == '\0') break;
		if (!nu_cald) {
			for (mdl_u8_t off = 0;; off++){if (__addr[ic+off+1] == '.' || __addr[ic+off+1] == '\0') {nu_cald = 1; break;} no_unit = no_unit*10;}
		}

		if (__addr[ic] != '.') {
			switch(__addr[ic]) {
				case '1': addr_bit += 1*no_unit; break;
				case '2': addr_bit += 2*no_unit; break;
				case '3': addr_bit += 3*no_unit; break;
				case '4': addr_bit += 4*no_unit; break;
				case '5': addr_bit += 5*no_unit; break;
				case '6': addr_bit += 6*no_unit; break;
				case '7': addr_bit += 7*no_unit; break;
				case '8': addr_bit += 8*no_unit; break;
				case '9': addr_bit += 9*no_unit; break;
			};

			if (no_unit != 1) no_unit = no_unit/10;
		} else {
			nu_cald = 0;
			addr |= (mdl_u32_t)addr_bit << addr_off;
			addr_off += 8;
			addr_bit = 0;
		}
	}

	if (addr_off != (sizeof(mdl_u32_t)-1)*8) {
		*__any_err = TMP_FAILURE;
		return 0;
	}

	addr |= (mdl_u32_t)addr_bit<<addr_off;
	*__any_err = TMP_SUCCESS;
	return addr;
}
# endif /*__TMP_LIGHT*/

tmp_err_t tmp_seti_speed(struct tmp_io *__tmp_io, mdl_uint_t __bps) {
	__tmp_io->rcv_holdup = (mdl_uint_t)(1000000/__bps);
	return TMP_SUCCESS;
}

tmp_err_t tmp_seto_speed(struct tmp_io *__tmp_io, mdl_uint_t __bps) {
	__tmp_io->snd_holdup = (mdl_uint_t)(1000000/__bps);
	return TMP_SUCCESS;
}

void tmp_set_holdup_fp(struct tmp_io *__tmp_io, void(*__holdup_fp)(mdl_uint_t)) {
	__tmp_io->holdup_fp = __holdup_fp;}

void tmp_holdup(struct tmp_io *__tmp_io, mdl_uint_t __holdup_ic, mdl_uint_t __holdup) {
	if (!__tmp_io->holdup_fp || !__holdup_ic) return;
	mdl_uint_t ic = 0;
	_again:

	if (ic == __holdup_ic) return;
	__tmp_io->holdup_fp(__holdup);
	ic++;

	goto _again;
}

void tmp_snd_holdup(struct tmp_io *__tmp_io){tmp_holdup(__tmp_io, __tmp_io->snd_holdup_ic, __tmp_io->snd_holdup);}
void tmp_rcv_holdup(struct tmp_io *__tmp_io){tmp_holdup(__tmp_io, __tmp_io->rcv_holdup_ic, __tmp_io->rcv_holdup);}
void tmp_flip_rx_clk_trig_val() {rx_clk_trig_val = ~rx_clk_trig_val&0x1;}
mdl_u8_t tmp_is_rx_clk_trig_val(mdl_u8_t __trig_val) {return rx_clk_trig_val == __trig_val? 1 : 0;}

void tmp_flip_tx_clk_trig_val() {tx_clk_trig_val = ~tx_clk_trig_val&0x1;}
mdl_u8_t tmp_is_tx_clk_trig_val(mdl_u8_t __trig_val) {return tx_clk_trig_val == __trig_val? 1 : 0;}

tmp_err_t tmp_recv_nibble(struct tmp_io *__tmp_io, mdl_u8_t *__nibble) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t bit_off = 0;
	for (;bit_off != 4; bit_off++) {
		mdl_u8_t bit_val;
		if ((any_err = tmp_recv_bit(__tmp_io, &bit_val)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, failed to receive nibble, off: %u bits.\n", bit_off);
# endif
			return any_err;
		}

		*__nibble |= bit_val << bit_off;
	}
# if defined(__DEBUG_ENABLED) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully recved nibble, {%x}\n", *__nibble);
# endif
	return any_err;
}

tmp_err_t tmp_send_nibble(struct tmp_io *__tmp_io, mdl_u8_t __nibble) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t bit_off = 0;
	for (; bit_off != 4; bit_off++) {
		if ((any_err = tmp_send_bit(__tmp_io, (__nibble >> bit_off)&1)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, failed to send nibble, off: %u bits.\n", bit_off);
# endif
			return any_err;
		}
	}
# if defined(__DEBUG_ENABLED) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully sent nibble, {%x}\n", __nibble);
# endif
	return any_err;
}

tmp_err_t tmp_recv_byte(struct tmp_io *__tmp_io, mdl_u8_t *__byte) {
	mdl_u8_t any_err = TMP_SUCCESS, nibble_val;

	nibble_val = 0;
	if ((any_err = tmp_recv_nibble(__tmp_io, &nibble_val)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp, recv_byte: failed to receive the first 4 bits.\n");
# endif
		return any_err;
	}
	*__byte |= nibble_val;

	nibble_val = 0;
	if ((any_err = tmp_recv_nibble(__tmp_io, &nibble_val)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp, recv_byte: failed to receive the last 4 bits.\n");
# endif
		return any_err;
	}
	*__byte |= nibble_val << 4;
# if defined(__DEBUG_ENABLED) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully recved byte, {%x}\n", *__byte);
# endif
	return any_err;
}

tmp_err_t tmp_send_byte(struct tmp_io *__tmp_io, mdl_u8_t __byte) {
	tmp_err_t any_err = TMP_SUCCESS;
	if ((any_err = tmp_send_nibble(__tmp_io, __byte)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp, send_byte: failed to send the first 4 bits.\n");
# endif
		return any_err;
	}

	if ((any_err = tmp_send_nibble(__tmp_io, __byte >> 4)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
		fprintf(stdout, "tmp, send_byte: failed to send the last 4 bits.\n");
# endif
		return any_err;
	}
# if defined(__DEBUG_ENABLED) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully sent byte, {%x}\n", __byte);
# endif
	return any_err;
}

mdl_u8_t tmp_par_asnd_sig(struct tmp_io *__tmp_io) {
	return (tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) == (tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val));}
mdl_u8_t tmp_par_arcv_sig(struct tmp_io *__tmp_io) {return ~tmp_par_asnd_sig(__tmp_io)&0x1;}

tmp_err_t tmp_recv_bit(struct tmp_io *__tmp_io, mdl_u8_t *__bit) {
# ifdef __AVR
	mdl_u8_t re_enable_gi = 0;
	if ((SREG >> 7)&1) {re_enable_gi = 1;cli();}
# endif
	mdl_u8_t _tx_clk_trig_val = tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_TX_TRIG_VAL)? ~tx_clk_trig_val&0x1:tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val;

	tmp_set_pin_state(__tmp_io, _tx_clk_trig_val, __tmp_io->tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io->rcv_timeo_ic = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) != _rx_clk_trig_val) {
		if (tmp_rcv_timeo(__tmp_io)) {tmp_set_pin_state(__tmp_io, ~_tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);return TMP_TIMEO;}}
	tmp_rcv_holdup(__tmp_io);

	mdl_u8_t recved_bit = tmp_get_pin_state(__tmp_io, __tmp_io->rx_pid);
	if (tmp_is_rcv_optflag(__tmp_io, TMP_OPT_FLIP_BIT))
		*__bit = ~recved_bit&0x1;
	else
		*__bit = recved_bit&0x1;
	tmp_rcv_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, ~_tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	__tmp_io->rcv_timeo_ic = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) != (~_rx_clk_trig_val&0x1)) if (tmp_rcv_timeo(__tmp_io)) return TMP_TIMEO;
	tmp_rcv_holdup(__tmp_io);
# ifdef __AVR
	if (re_enable_gi) sei();
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_send_bit(struct tmp_io *__tmp_io, mdl_u8_t __bit) {
# ifdef __AVR
	mdl_u8_t re_enable_gi = 0;
	if ((SREG >> 7)&1) {re_enable_gi = 1;cli();}
# endif
	mdl_u8_t _tx_clk_trig_val = tmp_is_snd_optflag(__tmp_io, TMP_OPT_INV_TX_TRIG_VAL)? ~tx_clk_trig_val&0x1:tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = tmp_is_snd_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val;
	if (tmp_is_snd_optflag(__tmp_io, TMP_OPT_FLIP_BIT)) __bit = ~__bit&0x1;

	__tmp_io->snd_timeo_ic = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->tx_ci_pid) != _tx_clk_trig_val) if (tmp_snd_timeo(__tmp_io))return TMP_TIMEO;
	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, __bit, __tmp_io->tx_pid);
	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, _rx_clk_trig_val, __tmp_io->rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	__tmp_io->snd_timeo_ic = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->tx_ci_pid) != (~_tx_clk_trig_val&0x1)){
		if (tmp_snd_timeo(__tmp_io)) {tmp_set_pin_state(__tmp_io, ~_rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);return TMP_TIMEO;}}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, ~_rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	if (__bit) tmp_set_pin_state(__tmp_io, tmp_gpio_low, __tmp_io->tx_pid);
# ifdef __AVR
	if (re_enable_gi) sei();
# endif
	return TMP_SUCCESS;
}

// gpio pins
void static tmp_set_pin_mode(struct tmp_io *__tmp_io, mdl_u8_t __pin_mode, mdl_u8_t __pid) {
	__tmp_io->set_pin_mode_fp(__pin_mode, __pid);
}

void static tmp_set_pin_state(struct tmp_io *__tmp_io, mdl_u8_t __pin_state, mdl_u8_t __pid) {
	__tmp_io->set_pin_state_fp(__pin_state, __pid);
}

mdl_u8_t static tmp_get_pin_state(struct tmp_io *__tmp_io, mdl_u8_t __pid) {
	return __tmp_io->get_pin_state_fp(__pid);
}

# if !defined(__TMP_LIGHT) || defined(__TMP_KOS)
tmp_err_t static send_ack(struct tmp_io *__tmp_io, mdl_u8_t __ack_val) {
	tmp_err_t any_err = TMP_SUCCESS;
	tmp_send_bit(__tmp_io, __ack_val&0x1);
	return any_err;
}


tmp_err_t static recv_ack(struct tmp_io *__tmp_io, mdl_u8_t *__ackv_p) {
	tmp_err_t any_err = TMP_SUCCESS;
	*__ackv_p = 0;
	tmp_recv_bit(__tmp_io, __ackv_p);
	return any_err;
}

# define KEY 0xc000000000000005
# ifdef __TMP_LIGHT
mdl_u64_t const key = KEY;
# endif
tmp_err_t send_key_and_sync(struct tmp_io *__tmp_io) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t recved_ack;

	_again:
# ifndef __TMP_LIGHT
	if ((any_err = tmp_send_w64(__tmp_io, KEY)) != TMP_SUCCESS) return any_err;
# else
	if ((any_err = tmp_raw_send(__tmp_io, tmp_io_buff((mdl_u8_t*)&key, sizeof(mdl_u64_t)))) != TMP_SUCCESS) return any_err;
# endif
	if ((any_err = recv_ack(__tmp_io, &recved_ack)) != TMP_SUCCESS) return any_err;
	if (recved_ack != ACK_SUCCESS) goto _again;
	return any_err;
}

tmp_err_t recv_key_and_sync(struct tmp_io *__tmp_io) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u64_t recved_key;

	_again:
	recved_key = 0x00000000000000;
# ifndef __TMP_LIGHT
	if ((any_err = tmp_recv_w64(__tmp_io, &recved_key)) != TMP_SUCCESS) return any_err;
# else
	if ((any_err = tmp_raw_send(__tmp_io, tmp_io_buff((mdl_u8_t*)&recved_key, sizeof(mdl_u64_t)))) != TMP_SUCCESS) return any_err;
# endif
	if (recved_key != KEY) {
		recv_ack(__tmp_io, (mdl_u8_t*)&tmp_null);
		send_ack(__tmp_io, ACK_FAILURE);
		goto _again;
	} else
		send_ack(__tmp_io, ACK_SUCCESS);
	return any_err;
}
# endif
tmp_err_t tmp_raw_send(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t *itr = __io_buff.p;
	while (itr != __io_buff.p+__io_buff.bc)
		if ((any_err = tmp_send_byte(__tmp_io, *(itr++))) != TMP_SUCCESS) return any_err;
	return any_err;
}

tmp_err_t tmp_raw_recv(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t *itr = __io_buff.p;
	while (itr != __io_buff.p+__io_buff.bc)
		if ((any_err = tmp_recv_byte(__tmp_io, itr++)) != TMP_SUCCESS) return any_err;
	return any_err;
}
# ifndef __TMP_LIGHT
mdl_u16_t const static pk_dt_sect_size = TMP_PACKET_SIZE-TMP_PK_HEADER_SIZE;
tmp_err_t tmp_send_packet(struct tmp_io *__tmp_io, struct tmp_packet_t *__tmp_pk) {
	if (__tmp_pk->io_buff.bc > pk_dt_sect_size) return TMP_FAILURE;
	tmp_err_t any_err = TMP_SUCCESS;

	if ((any_err = tmp_send_w32(__tmp_io, __tmp_pk->dst_addr)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_send_w32(__tmp_io, __tmp_pk->src_addr)) != TMP_SUCCESS) return any_err;

	__tmp_pk->dt_sect_sv = tmp_cal_sv(__tmp_pk->io_buff.p, __tmp_pk->io_buff.bc);
	if ((any_err = tmp_send_w32(__tmp_io, __tmp_pk->dt_sect_sv)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_raw_send(__tmp_io, __tmp_pk->io_buff)) != TMP_SUCCESS) return any_err;
	return any_err;
}

tmp_err_t tmp_recv_packet(struct tmp_io *__tmp_io, struct tmp_packet_t *__tmp_pk) {
	if (__tmp_pk->io_buff.bc > pk_dt_sect_size) return TMP_FAILURE;
	tmp_err_t any_err = TMP_SUCCESS;

	if ((any_err = tmp_recv_w32(__tmp_io, &__tmp_pk->dst_addr)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_recv_w32(__tmp_io, &__tmp_pk->src_addr)) != TMP_SUCCESS) return any_err;

	__tmp_pk->dt_sect_sv = 0x000000;
	if ((any_err = tmp_recv_w32(__tmp_io, &__tmp_pk->dt_sect_sv)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_raw_recv(__tmp_io, __tmp_pk->io_buff)) != TMP_SUCCESS) return any_err;

	if (tmp_cal_sv(__tmp_pk->io_buff.p, __tmp_pk->io_buff.bc) != __tmp_pk->dt_sect_sv) return TMP_FAILURE;
	return any_err;
}
# endif /*__TMP_LIGHT*/

# ifndef __TMP_LIGHT
tmp_err_t tmp_send(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff, tmp_addr_t __to_addr) {
	tmp_err_t any_err = TMP_SUCCESS;
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	}

	struct tmp_packet_t tmp_packet = {
		.dst_addr = __to_addr,
		.src_addr = __tmp_io->iface_addr
	};
# ifdef __DEBUG_ENABLED
	mdl_u8_t pk_c = 0;
# endif
	mdl_u8_t *begin = __io_buff.p;
	mdl_u8_t *itr = begin;
	mdl_u8_t ack;
	while(itr != begin+__io_buff.bc) {
		mdl_uint_t off = itr-begin;
		mdl_uint_t left = __io_buff.bc-off;

		mdl_uint_t bc = left >= pk_dt_sect_size? pk_dt_sect_size:left;
		tmp_packet.io_buff = tmp_io_buff(itr, bc);

		mdl_u8_t try_c = 0;
		_try_again:
		if (try_c++ >= TMP_MAX_TRY_C) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, max try count exceed, failed to send packet.\n");
# endif
			return TMP_FAILURE;
		}

		if ((any_err = tmp_send_packet(__tmp_io, &tmp_packet)) != TMP_SUCCESS) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, failed to send packet.\n");
# endif
			return any_err;
		}

		recv_ack(__tmp_io, &ack);
		if (ack == ACK_FAILURE) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, ack reported the packet failed to send.\n");
# endif
			if (tmp_is_flag(__tmp_io->flags, TMP_FLG_NORET)) {
# ifdef __DEBUG_ENABLED
				fprintf(stdout, "tmp, going to try again to send packet.\n");
# endif
				goto _try_again;
			}
		}

		itr+= bc;
# ifdef __DEBUG_ENABLED
		pk_c++;
# endif
	}
# ifdef __DEBUG_ENABLED
	fprintf(stdout, "tmp, sent %u packets, %u bytes.\n", pk_c, __io_buff.bc);
# endif
	return any_err;
}

tmp_err_t tmp_recv(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff, tmp_addr_t __from_addr) {
	tmp_err_t any_err = TMP_SUCCESS;
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	}

	struct tmp_packet_t tmp_packet;
# ifdef __DEBUG_ENABLED
	mdl_u8_t pk_c = 0;
# endif
	mdl_u8_t *begin = __io_buff.p;
	mdl_u8_t *itr = begin;
	while (itr != begin+__io_buff.bc) {
		mdl_uint_t off = itr-begin;
		mdl_uint_t left = __io_buff.bc-off;

		mdl_uint_t bc = left >= pk_dt_sect_size? pk_dt_sect_size:left;
		tmp_packet.io_buff = tmp_io_buff(itr, bc);

		mdl_u8_t try_c = 0;
		_try_again:
		if (try_c++ >= TMP_MAX_TRY_C) {
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, max try count exceed, failed to receive packet.\n");
# endif
			return TMP_FAILURE;
		}
		if ((any_err = tmp_recv_packet(__tmp_io, &tmp_packet)) != TMP_SUCCESS) {
			send_ack(__tmp_io, ACK_FAILURE);
# ifdef __DEBUG_ENABLED
			fprintf(stdout, "tmp, failed to receive packet.\n");
# endif
			if (tmp_is_flag(__tmp_io->flags, TMP_FLG_NORET)) {
# ifdef __DEBUG_ENABLED
				fprintf(stdout, "tmp, going to try again to receive packet.\n");
# endif
				goto _try_again;
			}
			return any_err;
		}

		send_ack(__tmp_io, ACK_SUCCESS);
		itr+= bc;
# ifdef __DEBUG_ENABLED
		pk_c++;
# endif
	}
# ifdef __DEBUG_ENABLED
	fprintf(stdout, "tmp, recved %u packets, %u bytes.\n", pk_c, __io_buff.bc);
# endif
	return any_err;
}
# else
tmp_err_t tmp_send(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff) {
	tmp_err_t any_err = TMP_SUCCESS;
# ifdef __TMP_KOS
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	}
# endif

	any_err = tmp_raw_send(__tmp_io, __io_buff);
	return any_err;
}

tmp_err_t tmp_recv(struct tmp_io *__tmp_io, tmp_io_buff_t __io_buff) {
	tmp_err_t any_err = TMP_SUCCESS;
# ifdef __TMP_KOS
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if ((any_err = send_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
	if ((any_err = recv_key_and_sync(__tmp_io)) != TMP_SUCCESS) return any_err;
    }
# endif

	any_err = tmp_raw_recv(__tmp_io, __io_buff);
	return any_err;
}
# endif /*__TMP_LIGHT*/

tmp_io_buff_t tmp_io_buff(mdl_u8_t *__p, mdl_uint_t __bc) {
	return (tmp_io_buff_t){.p=__p, .bc=__bc};
}

# ifndef __TMP_LIGHT
tmp_err_t tmp_send_w64(struct tmp_io *__tmp_io, mdl_u64_t __data) {
	tmp_err_t any_err = TMP_SUCCESS;
	if ((any_err = tmp_send_w32(__tmp_io, __data&0xFFFFFFFF)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_send_w32(__tmp_io, __data >> 32&0xFFFFFFFF)) != TMP_SUCCESS) return any_err;
	return any_err;
}

tmp_err_t tmp_recv_w64(struct tmp_io *__tmp_io, mdl_u64_t *__data) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u32_t _64b_part;

	_64b_part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &_64b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u64_t)_64b_part;

	_64b_part = 0;
	if ((any_err = tmp_recv_w32(__tmp_io, &_64b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u64_t)_64b_part << 32;
	return any_err;
}

tmp_err_t tmp_send_w32(struct tmp_io *__tmp_io, mdl_u32_t __data) {
	tmp_err_t any_err = TMP_SUCCESS;
	if ((any_err = tmp_send_w16(__tmp_io, __data&0xFFFF)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_send_w16(__tmp_io, __data >> 16&0xFFFF)) != TMP_SUCCESS) return any_err;
	return any_err;
}

tmp_err_t tmp_recv_w32(struct tmp_io *__tmp_io, mdl_u32_t *__data) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u16_t _32b_part;

	_32b_part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &_32b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u32_t)_32b_part;

	_32b_part = 0;
	if ((any_err = tmp_recv_w16(__tmp_io, &_32b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u32_t)_32b_part << 16;
	return any_err;
}

tmp_err_t tmp_send_w16(struct tmp_io *__tmp_io, mdl_u16_t __data) {
	tmp_err_t any_err = TMP_SUCCESS;
	if ((any_err = tmp_send_byte(__tmp_io, __data&0xFF)) != TMP_SUCCESS) return any_err;
	if ((any_err = tmp_send_byte(__tmp_io, __data >> 8&0xFF)) != TMP_SUCCESS) return any_err;
	return any_err;
}

tmp_err_t tmp_recv_w16(struct tmp_io *__tmp_io, mdl_u16_t *__data) {
	tmp_err_t any_err = TMP_SUCCESS;
	mdl_u8_t _16b_part;

	_16b_part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &_16b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u16_t)_16b_part;

	_16b_part = 0;
	if ((any_err = tmp_recv_byte(__tmp_io, &_16b_part)) != TMP_SUCCESS) return any_err;
	*__data |= (mdl_u16_t)_16b_part << 8;
	return any_err;
}
# endif

void tmp_set_opt(struct tmp_io *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_TIMEO:
			__tmp_io->snd_timeo = *(mdl_uint_t*)__data;
		break;
		case TMP_OPT_RCV_TIMEO:
			__tmp_io->rcv_timeo = *(mdl_uint_t*)__data;
		break;
	}
}

void tmp_get_opt(struct tmp_io *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_TIMEO:
			*(mdl_uint_t*)__data = __tmp_io->snd_timeo;
		break;
		case TMP_OPT_RCV_TIMEO:
			*(mdl_uint_t*)__data = __tmp_io->rcv_timeo;
		break;
	}
}

mdl_u8_t tmp_is_flag(mdl_u8_t __optflags, mdl_u8_t __optflag) {
	return (__optflags&__optflag) == __optflag;}

void tmp_tog_flag(mdl_u8_t *__optflags, mdl_u8_t __optflag) {
	if (tmp_is_flag(*__optflags, __optflag))
		(*__optflags) ^= __optflag;
	else
		(*__optflags) |= __optflag;
}
