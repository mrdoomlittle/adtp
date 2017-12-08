# include "tmp_io.h"
mdl_u8_t tmp_gpio_high = 0x1, tmp_gpio_low = 0x0;
mdl_u8_t tmp_gpio_in = 0x0, tmp_gpio_out = 0x1;

mdl_u8_t rx_clk_trig_val;
mdl_u8_t tx_clk_trig_val;
mdl_u64_t tmp_null;

void static tmp_set_pin_mode(struct tmp_io*, mdl_u8_t, mdl_u8_t);
void static tmp_set_pin_state(struct tmp_io*, mdl_u8_t, mdl_u8_t);
mdl_u8_t static tmp_get_pin_state(struct tmp_io*, mdl_u8_t);

void static bzero(void *__p, mdl_uint_t __bc) {
	mdl_u8_t *itr = (mdl_u8_t*)__p;
	while(itr != (mdl_u8_t*)__p+__bc) {
		mdl_uint_t off = itr-(mdl_u8_t*)__p;
		if (off >= sizeof(mdl_u64_t)) {
			*((mdl_u64_t*)itr) = 0x00000000000000;
			itr+=sizeof(mdl_u64_t);
		} else *(itr++) = 0x0;
	}
}

mdl_u8_t tmp_cutoff(mdl_u8_t __divider, mdl_u16_t *__c, mdl_u32_t *__p, mdl_uint_t __cutoff) {
	if (!__cutoff) return 0;
	if (((*__c)>>__divider)&0x1) {
		(*__p)++;
		*__c = 0;
	}

	if (*__p >= __cutoff) {
		*__p = 0;
		*__c = 0;
		return 1;
	}
	(*__c)++;
	return 0;
}

tmp_err_t tmp_init(struct tmp_io *__tmp_io, void(*__set_pin_mode_fp)(mdl_u8_t, mdl_u8_t), void(*__set_pin_state_fp)(mdl_u8_t, mdl_u8_t), mdl_u8_t(*__get_pin_state_fp)(mdl_u8_t)
# ifndef __TMP_LIGHT
, tmp_method_t __tr_method, tmp_flag_t __flags, mdl_u8_t __port_c
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

	tmp_set_pin_state(__tmp_io, tmp_gpio_low, __tmp_io->tx_pid);

	__tmp_io->snd_cutoff = 0;
	__tmp_io->rcv_cutoff = 0;
	__tmp_io->divider = 1<<_d2;

	__tmp_io->snd_holdup_ic = 0;
	__tmp_io->rcv_holdup_ic = 0;
    __tmp_io->snd_holdup = 0;
	__tmp_io->rcv_holdup = 0;
	__tmp_io->snd_optflags = 0;
	__tmp_io->rcv_optflags = 0;
# ifndef __TMP_LIGHT
	__tmp_io->iface = NULL;
	__tmp_io->iface_c = 0;
	__tmp_io->flags = __flags|TMP_DEF_FLAGS;
	__tmp_io->cur_iface = 0;
	__tmp_io->port_c = __port_c;
	struct tmp_port *itr = __tmp_io->ports;
	struct tmp_port *end = __tmp_io->ports+__port_c;
	while(itr != end) {
		*(itr++) = (struct tmp_port) {
			.flags = 0x0, .id = (itr-__tmp_io->ports)-1,
			.left = 0, .by = NULL
		};
	}
# else
	__tmp_io->flags = TMP_DEF_FLAGS;
# endif
	tmp_holdup(__tmp_io, 200, 0);
	return TMP_SUCCESS;
}

void tmp_prepare(struct tmp_io *__tmp_io) {
	tmp_set_pin_state(__tmp_io, tmp_is_snd_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? rx_clk_trig_val:~rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);
	tmp_set_pin_state(__tmp_io, tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_TX_TRIG_VAL)? tx_clk_trig_val:~tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);
}

# ifndef __TMP_LIGHT
struct tmp_iface* tmp_add_iface(struct tmp_io *__tmp_io, tmp_addr_t __addr, mdl_u8_t __no, mdl_u8_t __port_id) {
	if (!__tmp_io->iface) {
		*(__tmp_io->iface = (struct tmp_iface*)malloc(sizeof(struct tmp_iface))) = (struct tmp_iface) {.addr=__addr, .no=__no};
		__tmp_io->iface_c++;
		return __tmp_io->iface;
	}

	__tmp_io->iface = (struct tmp_iface*)realloc(__tmp_io->iface, (++__tmp_io->iface_c)*sizeof(struct tmp_iface));
	struct tmp_iface *iface;
	*(iface = (__tmp_io->iface+(__tmp_io->iface_c-1))) = (struct tmp_iface) {.addr=__addr, .no=__no, .port=tmp_get_port(__tmp_io, __port_id)};
	return iface;
}


void tmp_rm_iface(struct tmp_io *__tmp_io, struct tmp_iface* __p) {
	if (!__tmp_io->iface || !__p) return;
	if (!(__tmp_io->iface_c-1)) {
		free(__tmp_io->iface);
		__tmp_io->iface = NULL;
		return;
	}

	mdl_u8_t no = __p-__tmp_io->iface;
	if (no != __tmp_io->iface_c-1) {
		*__p = *(__tmp_io->iface+(__tmp_io->iface_c-1));
		__p->no = no;
	}

	__tmp_io->iface = (struct tmp_iface*)realloc(__tmp_io->iface, (--__tmp_io->iface_c)*sizeof(struct tmp_iface));
}

mdl_u32_t tmp_cal_sv(mdl_u8_t *__p, mdl_uint_t __bc) {
	mdl_u32_t ret_val = 0;
	mdl_u8_t *itr = __p;
	while(itr != __p+__bc) {
//		ret_val += *(itr++);
		ret_val ^= ((ret_val<<2)|(*itr))<<((itr-__p)&0x3);
		itr++;
	}
	return ret_val;
}

mdl_u32_t tmp_addr_from_str(char const *__addr, tmp_err_t *__any_err) {
	mdl_u32_t addr = 0x000000, addr_off = 0;
	mdl_u8_t addr_bit = 0, no_unit = 1, nu_cald = 0;
	mdl_u8_t i = 0;
	for (;;i++) {
		if (__addr[i] == '\0') break;
		if (!nu_cald) {
			for (mdl_u8_t off = 0;; off++){if (__addr[i+off+1] == '.' || __addr[i+off+1] == '\0') {nu_cald = 1; break;} no_unit = no_unit*10;}
		}

		if (__addr[i] != '.') {
			switch(__addr[i]) {
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
			addr |= (mdl_u32_t)addr_bit<<addr_off;
			addr_off += 8;
			addr_bit = 0x0;
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
mdl_u8_t tmp_is_rx_clk_trig_val(mdl_u8_t __trig_val) {return (rx_clk_trig_val == __trig_val);}

void tmp_flip_tx_clk_trig_val() {tx_clk_trig_val = ~tx_clk_trig_val&0x1;}
mdl_u8_t tmp_is_tx_clk_trig_val(mdl_u8_t __trig_val) {return (tx_clk_trig_val == __trig_val);}

tmp_err_t tmp_rcv_nib(struct tmp_io *__tmp_io, mdl_u8_t *__nib) {
	tmp_err_t any_err;
	mdl_u8_t bit_off = 0;
	for (;bit_off != 4; bit_off++) {
		mdl_u8_t bit_val;
		if (_err(any_err = tmp_rcv_bit(__tmp_io, &bit_val))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to receive nib, off: %u bits.\n", bit_off);
# endif
			return any_err;
		}
		if (__nib != NULL)
			*__nib |= bit_val<<bit_off;
	}
# if defined(__TMP_DEBUG) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully recved nibble, {%x}\n", *__nib);
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_nib(struct tmp_io *__tmp_io, mdl_u8_t __nib) {
	tmp_err_t any_err;
	mdl_u8_t bit_off = 0;
	for (;bit_off != 4; bit_off++) {
		if (_err(any_err = tmp_snd_bit(__tmp_io, (__nib>>bit_off)&0x1))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to send nibble, off: %u bits.\n", bit_off);
# endif
			return any_err;
		}
	}
# if defined(__TMP_DEBUG) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully sent nib, {%x}\n", __nib);
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_byte(struct tmp_io *__tmp_io, mdl_u8_t *__byte) {
	mdl_u8_t any_err, nib_val;
	nib_val = 0;
	if (_err(any_err = tmp_rcv_nib(__tmp_io, &nib_val))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, recv_byte: failed to receive the first 4 bits.\n");
# endif
		return any_err;
	}
	*__byte |= nib_val;

	nib_val = 0;
	if (_err(any_err = tmp_rcv_nib(__tmp_io, &nib_val))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, recv_byte: failed to receive the last 4 bits.\n");
# endif
		return any_err;
	}
	*__byte |= nib_val<<4;
# if defined(__TMP_DEBUG) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully recved byte, {%x}\n", *__byte);
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_byte(struct tmp_io *__tmp_io, mdl_u8_t __byte) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_nib(__tmp_io, __byte))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, send_byte: failed to send the first 4 bits.\n");
# endif
		return any_err;
	}

	if (_err(any_err = tmp_snd_nib(__tmp_io, __byte>>4))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, send_byte: failed to send the last 4 bits.\n");
# endif
		return any_err;
	}
# if defined(__TMP_DEBUG) && !defined(TMP_DB_ONLY_ERR)
	fprintf(stdout, "tmp, successfully sent byte, {%x}\n", __byte);
# endif
	return TMP_SUCCESS;
}

mdl_u8_t tmp_par_asnd_sig(struct tmp_io *__tmp_io) {
	return (tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) == (tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val));}
mdl_u8_t tmp_par_arcv_sig(struct tmp_io *__tmp_io) {return ~tmp_par_asnd_sig(__tmp_io)&0x1;}

tmp_err_t tmp_rcv_bit(struct tmp_io *__tmp_io, mdl_u8_t *__bit) {
# ifdef __AVR
	mdl_u8_t re_enable_gi = 0;
	if ((SREG>>7)&1) {re_enable_gi = 1;cli();}
# endif
	mdl_u8_t _tx_clk_trig_val = tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_TX_TRIG_VAL)? ~tx_clk_trig_val&0x1:tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = tmp_is_rcv_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val;
	mdl_u16_t c = 0;
	mdl_u32_t p = 0;

	tmp_set_pin_state(__tmp_io, _tx_clk_trig_val, __tmp_io->tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	while (tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) != _rx_clk_trig_val) {
		if (tmp_get_pin_state(__tmp_io, __tmp_io->tx_ci_pid) == (~_tx_clk_trig_val&0x1)) {
			tmp_set_pin_state(__tmp_io, ~_tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp can't recv.\n");
# endif
			return TMP_FAILURE;
        }

		if (tmp_rcv_cutoff(__tmp_io, &c, &p)){
			tmp_set_pin_state(__tmp_io, ~_tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, cutoff reched, took too long.\n");
# endif
			return TMP_CUTOFF;
		}
	}

	tmp_rcv_holdup(__tmp_io);

	mdl_u8_t recved_bit = tmp_get_pin_state(__tmp_io, __tmp_io->rx_pid);
	if (tmp_is_rcv_optflag(__tmp_io, TMP_OPT_FLIP_BIT))
		*__bit = ~recved_bit&0x1;
	else
		*__bit = recved_bit&0x1;
	tmp_rcv_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, ~_tx_clk_trig_val&0x1, __tmp_io->tx_co_pid);
	tmp_rcv_holdup(__tmp_io);

	c = 0;
	p = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->rx_ci_pid) != (~_rx_clk_trig_val&0x1)) {
		if (tmp_rcv_cutoff(__tmp_io, &c, &p)) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, cutoff reched, took too long.\n");
# endif
			return TMP_CUTOFF;
		}
	}
	tmp_rcv_holdup(__tmp_io);
# ifdef __AVR
	if (re_enable_gi) sei();
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_bit(struct tmp_io *__tmp_io, mdl_u8_t __bit) {
# ifdef __AVR
	mdl_u8_t re_enable_gi = 0;
	if ((SREG>>7)&1) {re_enable_gi = 1;cli();}
# endif
	mdl_u8_t _tx_clk_trig_val = tmp_is_snd_optflag(__tmp_io, TMP_OPT_INV_TX_TRIG_VAL)? ~tx_clk_trig_val&0x1:tx_clk_trig_val;
	mdl_u8_t _rx_clk_trig_val = tmp_is_snd_optflag(__tmp_io, TMP_OPT_INV_RX_TRIG_VAL)? ~rx_clk_trig_val&0x1:rx_clk_trig_val;
	if (tmp_is_snd_optflag(__tmp_io, TMP_OPT_FLIP_BIT)) __bit = ~__bit&0x1;
	mdl_u16_t c = 0;
	mdl_u32_t p = 0;

	while(tmp_get_pin_state(__tmp_io, __tmp_io->tx_ci_pid) != _tx_clk_trig_val) {
		if (tmp_snd_cutoff(__tmp_io, &c, &p)) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, cutoff reched, took too long.\n");
# endif
			return TMP_CUTOFF;
		}
	}
	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, __bit, __tmp_io->tx_pid);
	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, _rx_clk_trig_val, __tmp_io->rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	c = 0;
	p = 0;
	while(tmp_get_pin_state(__tmp_io, __tmp_io->tx_ci_pid) != (~_tx_clk_trig_val&0x1)) {
		if (tmp_snd_cutoff(__tmp_io, &c, &p)) {
			tmp_set_pin_state(__tmp_io, ~_rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, cutoff reched, took too long.\n");
# endif
			return TMP_CUTOFF;
		}
	}

	tmp_snd_holdup(__tmp_io);

	tmp_set_pin_state(__tmp_io, ~_rx_clk_trig_val&0x1, __tmp_io->rx_co_pid);
	tmp_snd_holdup(__tmp_io);

	if (__bit) tmp_set_pin_state(__tmp_io, tmp_gpio_low, __tmp_io->tx_pid);
# ifdef __AVR
	if (re_enable_gi) sei();
# endif
	return TMP_SUCCESS;
}

void static tmp_set_pin_mode(struct tmp_io *__tmp_io, mdl_u8_t __mode, mdl_u8_t __id) {
	__tmp_io->set_pin_mode_fp(__mode, __id);
}

void static tmp_set_pin_state(struct tmp_io *__tmp_io, mdl_u8_t __state, mdl_u8_t __id) {
	__tmp_io->set_pin_state_fp(__state, __id);
}

mdl_u8_t static tmp_get_pin_state(struct tmp_io *__tmp_io, mdl_u8_t __id) {
	return __tmp_io->get_pin_state_fp(__id);
}
# if !defined(__TMP_LIGHT) || defined(__TMP_KOS)
tmp_err_t tmp_snd_ack(struct tmp_io *__tmp_io, mdl_u8_t __ack_val) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_bit(__tmp_io, __ack_val&0x1)))
		return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_ack(struct tmp_io *__tmp_io, mdl_u8_t *__ackv_p) {
	tmp_err_t any_err;
	*__ackv_p = 0x0;
	if (_err(any_err = tmp_rcv_bit(__tmp_io, __ackv_p)))
		return any_err;
	return TMP_SUCCESS;
}

# define KEY 0xc000000000000005
# ifdef __TMP_LIGHT
mdl_u64_t const key = KEY;
# endif
tmp_err_t send_key_and_sync(struct tmp_io *__tmp_io) {
	tmp_err_t any_err;
	mdl_u8_t recved_ack;

	_again:
# ifndef __TMP_LIGHT
	if (_err(any_err = tmp_snd_64l(__tmp_io, KEY))) return any_err;
# else
	if (_err(any_err = tmp_raw_snd(__tmp_io, tmp_io_buff((mdl_u8_t*)&key, sizeof(mdl_u64_t)))))
		return any_err;
# endif
	if (_err(any_err = tmp_rcv_ack(__tmp_io, &recved_ack))) return any_err;
	if (recved_ack != ACK_SUCCESS) goto _again;
	return TMP_SUCCESS;
}

tmp_err_t recv_key_and_sync(struct tmp_io *__tmp_io) {
	tmp_err_t any_err;
	mdl_u64_t recved_key;

	_again:
	recved_key = 0x0000000000000000;
# ifndef __TMP_LIGHT
	if (_err(any_err = tmp_rcv_64l(__tmp_io, &recved_key))) return any_err;
# else
	if (_err(any_err = tmp_raw_rcv(__tmp_io, tmp_io_buff((mdl_u8_t*)&recved_key, sizeof(mdl_u64_t)))))
		return any_err;
# endif
	if (recved_key != KEY) {
		tmp_rcv_ack(__tmp_io, (mdl_u8_t*)&tmp_null);
		tmp_snd_ack(__tmp_io, ACK_FAILURE);
		goto _again;
	} else
		tmp_snd_ack(__tmp_io, ACK_SUCCESS);
	return TMP_SUCCESS;
}
# endif
tmp_err_t tmp_raw_snd(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff) {
	tmp_err_t any_err;
	mdl_u8_t *itr = __io_buff.p;
	while (itr != __io_buff.p+__io_buff.bc)
		if (_err(any_err = tmp_snd_byte(__tmp_io, *(itr++)))) return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_raw_rcv(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff) {
	tmp_err_t any_err;
	mdl_u8_t *itr = __io_buff.p;
	while (itr != __io_buff.p+__io_buff.bc)
		if (_err(any_err = tmp_rcv_byte(__tmp_io, itr++))) return any_err;
	return TMP_SUCCESS;
}
# ifndef __TMP_LIGHT
tmp_err_t tmp_snd_pkt(struct tmp_io *__tmp_io, struct tmp_packet *__packet) {
	if (__packet->io_buff.bc > TMP_PKT_MSS) return TMP_FAILURE;

	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_32l(__tmp_io, __packet->dst_addr))) return any_err;
	if (_err(any_err = tmp_snd_32l(__tmp_io, __packet->src_addr))) return any_err;

	__packet->dt_sect_sv = tmp_cal_sv(__packet->io_buff.p, __packet->io_buff.bc);
	if (_err(any_err = tmp_snd_32l(__tmp_io, __packet->dt_sect_sv))) return any_err;
	if (_err(any_err = tmp_raw_snd(__tmp_io, __packet->io_buff))) return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_pkt(struct tmp_io *__tmp_io, struct tmp_packet *__packet) {
	if (__packet->io_buff.bc > TMP_PKT_MSS) return TMP_FAILURE;

	tmp_err_t any_err;
	if (_err(any_err = tmp_rcv_32l(__tmp_io, &__packet->dst_addr))) return any_err;
	if (_err(any_err = tmp_rcv_32l(__tmp_io, &__packet->src_addr))) return any_err;

	__packet->dt_sect_sv = 0x00000000;
	if (_err(any_err = tmp_rcv_32l(__tmp_io, &__packet->dt_sect_sv))) return any_err;
	if (_err(any_err = tmp_raw_rcv(__tmp_io, __packet->io_buff))) return any_err;

	if (tmp_cal_sv(__packet->io_buff.p, __packet->io_buff.bc) != __packet->dt_sect_sv) {
# ifdef __TMP_DEBUG
		printf("mismatch.\n");
# endif
	//	return TMP_FAILURE;
	}
# ifdef __TMP_DEBUG
	printf("src addr: %u.%u.%u.%u\n", __packet->src_addr&0xFF,__packet->src_addr>>8&0xFF, __packet->src_addr>>16&0xFF, __packet->src_addr>>24&0xFF);
# endif
	return TMP_SUCCESS;
}

void tmp_build_pk(struct tmp_packet *__pk, tmp_io_buf_t __io_buff) {
	__pk->io_buff = __io_buff;
	// ...
}
# endif /*__TMP_LIGHT*/

# ifndef __TMP_LIGHT
tmp_err_t tmp_snd_prepare(struct tmp_io *__tmp_io, mdl_u8_t *__rcv_optflags, mdl_u8_t __snd_optflags) {
	tmp_err_t any_err;
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
		if (_err(any_err = recv_key_and_sync(__tmp_io))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to recv key and sync.\n");
# endif
			return any_err;
		}

		if (_err(any_err = send_key_and_sync(__tmp_io))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to send key and sync.\n");
# endif
			return any_err;
		}
	}

	if (_err(any_err = tmp_rcv_nib(__tmp_io, __rcv_optflags))) {
		return any_err;
	}

	if (_err(any_err = tmp_snd_nib(__tmp_io, __snd_optflags))) {
		return any_err;
	}
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_prepare(struct tmp_io *__tmp_io, mdl_u8_t __rcv_optflags, mdl_u8_t *__snd_optflags) {
	tmp_err_t any_err;
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
		if (_err(any_err = send_key_and_sync(__tmp_io))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to send key and sync.\n");
# endif
			return any_err;
		}
		if (_err(any_err = recv_key_and_sync(__tmp_io))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to recv key and sync.\n");
# endif
			return any_err;
		}
	}

	if (_err(any_err = tmp_snd_nib(__tmp_io, __rcv_optflags))) {
		return any_err;
    }

	if (_err(any_err = tmp_rcv_nib(__tmp_io, __snd_optflags))) {
		return any_err;
	}
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_sig(struct tmp_io *__tmp_io, mdl_u8_t __sigv) {
	return tmp_snd_bit(__tmp_io, __sigv);
}

tmp_err_t tmp_rcv_sig(struct tmp_io *__tmp_io, mdl_u8_t *__sigv_p) {
	return tmp_rcv_bit(__tmp_io, __sigv_p);
}

void tmp_sigwait(struct tmp_io *__tmp_io) {
	mdl_u8_t sigval = 0x0;
	mdl_uint_t trys = 0;
	_wait:
	if (trys > MAX_SIG_TRYS) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "waited for signal but exceded max amount of trys.\n");
# endif
		return;
	}
	if (_ok(tmp_rcv_sig(__tmp_io, &sigval))) {
		if (sigval == SIG_EXIT) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "exit signal recved.\n");
# endif
			return;
		}
		tmp_snd_sig(__tmp_io, sigval);
	}
	trys++;
	goto _wait;
}

tmp_err_t tmp_signal(struct tmp_io *__tmp_io) {
	if (_err(tmp_snd_sig(__tmp_io, SIG_OK)))
		return TMP_FAILURE;

	mdl_u8_t sigval = 0x0;
	if (_err(tmp_rcv_sig(__tmp_io, &sigval)))
		return TMP_FAILURE;
	if (sigval == SIG_OK) {
		if (_err(tmp_snd_sig(__tmp_io, SIG_EXIT)))
			return TMP_FAILURE;
# ifdef __TMP_DEBUG
		fprintf(stdout, "sent signal.\n");
# endif
		return TMP_SUCCESS;
	}
	return TMP_FAILURE;
}

tmp_err_t tmp_snd(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
tmp_err_t tmp_send(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff, tmp_addr_t __to_addr) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd(__tmp_io, &__io_buff, __to_addr, 0x0, NULL))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, failed to send.\n");
# endif
		return any_err;
	}
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd(struct tmp_io *__tmp_io, tmp_io_buf_t *__io_buff, tmp_addr_t __to_addr, mdl_u8_t __flags, struct tmp_packet *__pkbuf) {
	tmp_sigwait(__tmp_io);
	if (_err(tmp_signal(__tmp_io)))
		return TMP_FAILURE;

	tmp_err_t any_err;
	mdl_u8_t s_flags = __flags, r_flags = 0x0;
	if (_err(any_err = tmp_snd_prepare(__tmp_io, &r_flags, s_flags))) {
		return any_err;
	}

	if (tmp_is_flag(r_flags, TMP_FLG_RBS)) {
		if (_err(any_err = tmp_snd_16l(__tmp_io, __io_buff->bc))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "failed to send buffer size.\n");
# endif
			return any_err;
		}
	}

	struct tmp_packet pk;
	if (!__pkbuf) {
	pk = (struct tmp_packet){
		.dst_addr = __to_addr,
		.src_addr = tmp_get_iface(__tmp_io, tmp_get_iface_no(__tmp_io))->addr
	};}
# ifdef __TMP_DEBUG
	fprintf(stdout, "src: %u.%u.%u.%u\n", pk.src_addr&0xFF, pk.src_addr>>8&0xFF, pk.src_addr>>16&0xFF, pk.src_addr>>24&0xFF);
	mdl_u8_t pk_c = 0;
# endif
	mdl_u8_t *begin = __io_buff->p;
	mdl_u8_t *itr = begin;
	mdl_u8_t ack;
	while(itr != begin+__io_buff->bc) {
		mdl_uint_t off = itr-begin;
		mdl_uint_t left = __io_buff->bc-off;

		mdl_uint_t bc = left >= TMP_PKT_MSS?TMP_PKT_MSS:left;
		if (__pkbuf != NULL) {
			pk = *(__pkbuf++);
		} else {
			tmp_build_pk(&pk, tmp_io_buff(itr, bc));
		}

		mdl_u8_t try_c = 0;
		_try_again:
		if (try_c++ >= TMP_MAX_TRY_C) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, max try count exceed, failed to send packet.\n");
# endif
			return TMP_FAILURE;
		}

		if (_err(any_err = tmp_snd_pkt(__tmp_io, &pk))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to send packet.\n");
# endif
			return any_err;
		}

		if (_err(any_err = tmp_rcv_ack(__tmp_io, &ack))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to recv ack.\n");
# endif
			return any_err;
		}

		if (ack == ACK_FAILURE) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, ack reported the packet failed to send.\n");
# endif
			if (tmp_is_flag(__tmp_io->flags, TMP_FLG_NORET)) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "tmp, going to try again to send packet.\n");
# endif
				goto _try_again;
			}
		}

		itr+= bc;
# ifdef __TMP_DEBUG
		pk_c++;
# endif
	}
# ifdef __TMP_DEBUG
	fprintf(stdout, "tmp, sent %u packets, %u bytes.\n", pk_c, __io_buff->bc);
# endif
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv(struct tmp_io*, tmp_io_buf_t*, tmp_addr_t, mdl_u8_t, struct tmp_packet*);
tmp_err_t tmp_recv(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff, tmp_addr_t __from_addr) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_rcv(__tmp_io, &__io_buff, __from_addr, 0x0, NULL))) {
# ifdef __TMP_DEBUG
		fprintf(stdout, "tmp, failed to recv.\n");
# endif
	}
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv(struct tmp_io *__tmp_io, tmp_io_buf_t *__io_buff, tmp_addr_t __from_addr, mdl_u8_t __flags, struct tmp_packet *__pkbuf) {
	if (_err(tmp_signal(__tmp_io)))
		return TMP_FAILURE;
	tmp_sigwait(__tmp_io);

	tmp_err_t any_err;
	mdl_u8_t s_flags, r_flags = __flags;
	struct tmp_packet pk;
	struct tmp_msg msg;
	bzero((void*)&msg, sizeof(struct tmp_msg));
	bzero((void*)&pk, sizeof(struct tmp_packet));
	tmp_io_buf_t *io_buff = __io_buff, _io_buff;

	_btt:
	{
	s_flags = 0x0;
	if (_err(any_err = tmp_rcv_prepare(__tmp_io, r_flags, &s_flags))) {
		return any_err;
	}

	if (tmp_is_flag(r_flags, TMP_FLG_RBS))
		tmp_rcv_16l(__tmp_io, (mdl_u16_t*)&io_buff->bc);
	if (tmp_is_flag(s_flags, TMP_FLG_MSG)) {
		printf("recved control message.\n");
		io_buff = &_io_buff;
		_io_buff = tmp_io_buff(&msg, sizeof(struct tmp_msg));
	}
# ifdef __TMP_DEBUG
	mdl_u8_t pk_c = 0;
# endif
	mdl_u8_t *begin = io_buff->p;
	mdl_u8_t *itr = begin;
	while (itr != begin+io_buff->bc) {
		mdl_uint_t off = itr-begin;
		mdl_uint_t left = io_buff->bc-off;

		mdl_uint_t bc = left >= TMP_PKT_MSS? TMP_PKT_MSS:left;
		pk.io_buff = tmp_io_buff(itr, bc);

		mdl_u8_t try_c = 0;
		_try_again:
		if (try_c++ >= TMP_MAX_TRY_C) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, max try count exceed, failed to receive packet.\n");
# endif
			return TMP_FAILURE;
		}
		if (_err(any_err = tmp_rcv_pkt(__tmp_io, &pk))) {
			if (_err(any_err = tmp_snd_ack(__tmp_io, ACK_FAILURE))) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "tmp, failed to send ack.\n");
# endif
				return any_err;
			}
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to receive packet.\n");
# endif
			if (tmp_is_flag(__tmp_io->flags, TMP_FLG_NORET)) {
# ifdef __TMP_DEBUG
				fprintf(stdout, "tmp, going to try again to receive packet.\n");
# endif
				goto _try_again;
			}
			return any_err;
		}

		if (_err(any_err = tmp_snd_ack(__tmp_io, ACK_SUCCESS))) {
# ifdef __TMP_DEBUG
			fprintf(stdout, "tmp, failed to send ack.\n");
# endif
			return any_err;
		}

		if (__pkbuf != NULL)
			*(__pkbuf++) = pk;
		itr+= bc;
# ifdef __TMP_DEBUG
		pk_c++;
# endif
	}
# ifdef __TMP_DEBUG
	fprintf(stdout, "tmp, recved %u packets, %u bytes.\n", pk_c, io_buff->bc);
# endif
	}

	if (tmp_is_flag(s_flags, TMP_FLG_MSG)) {
		mdl_u8_t route[24];
		struct tmp_iface *iface = __tmp_io->iface+tmp_get_iface_no(__tmp_io);
		printf("------------------------ %u - %u\n", msg.lu_addr, iface->addr);
		if (msg.lu_addr == iface->addr) {
			route[0] = 200;//iface->no;
			tmp_snd_bit(__tmp_io, 1);
			*io_buff = tmp_io_buff(route, sizeof(mdl_u8_t));
			tmp_snd(__tmp_io, io_buff, 0x0, 0x0, NULL);
			printf("found.\n");
		} else
			tmp_snd_bit(__tmp_io, 0);
		io_buff = __io_buff;
		goto _btt;
	}
	return TMP_SUCCESS;
}
# else
tmp_err_t tmp_send(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff) {
	tmp_err_t any_err;
# ifdef __TMP_KOS
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if (_err(any_err = recv_key_and_sync(__tmp_io))) return any_err;
	if (_err(any_err = send_key_and_sync(__tmp_io))) return any_err;
	}
# endif
	if (_err(any_err = tmp_raw_snd(__tmp_io, __io_buff))) {
		return any_err;
	}
	return TMP_SUCCESS;
}

tmp_err_t tmp_recv(struct tmp_io *__tmp_io, tmp_io_buf_t __io_buff) {
	tmp_err_t any_err;
# ifdef __TMP_KOS
	if (tmp_is_flag(__tmp_io->flags, TMP_FLG_KAS)) {
	if (_err(any_err = send_key_and_sync(__tmp_io))) return any_err;
	if (_err(any_err = recv_key_and_sync(__tmp_io))) return any_err;
    }
# endif
	if (_err(any_err = tmp_raw_rcv(__tmp_io, __io_buff))) {
		return any_err;
	}
	return TMP_SUCCESS;
}
# endif /*__TMP_LIGHT*/
tmp_io_buf_t tmp_io_buff(void *__p, mdl_uint_t __bc) {
	return (tmp_io_buf_t){.p=(mdl_u8_t*)__p,.bc=__bc};
}
# ifndef __TMP_LIGHT
tmp_err_t tmp_snd_64l(struct tmp_io *__tmp_io, mdl_u64_t __data) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_32l(__tmp_io, __data&0xFFFFFFFF))) return any_err;
	if (_err(any_err = tmp_snd_32l(__tmp_io, __data>>32&0xFFFFFFFF))) return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_64l(struct tmp_io *__tmp_io, mdl_u64_t *__data) {
	tmp_err_t any_err;
	mdl_u32_t _64b_part;

	_64b_part = 0;
	if (_err(any_err = tmp_rcv_32l(__tmp_io, &_64b_part))) return any_err;
	*__data |= (mdl_u64_t)_64b_part;

	_64b_part = 0;
	if (_err(any_err = tmp_rcv_32l(__tmp_io, &_64b_part))) return any_err;
	*__data |= (mdl_u64_t)_64b_part<<32;
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_32l(struct tmp_io *__tmp_io, mdl_u32_t __data) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_16l(__tmp_io, __data&0xFFFF))) return any_err;
	if (_err(any_err = tmp_snd_16l(__tmp_io, __data>>16&0xFFFF))) return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_32l(struct tmp_io *__tmp_io, mdl_u32_t *__data) {
	tmp_err_t any_err;
	mdl_u16_t _32b_part;

	_32b_part = 0;
	if (_err(any_err = tmp_rcv_16l(__tmp_io, &_32b_part))) return any_err;
	*__data |= (mdl_u32_t)_32b_part;

	_32b_part = 0;
	if (_err(any_err = tmp_rcv_16l(__tmp_io, &_32b_part))) return any_err;
	*__data |= (mdl_u32_t)_32b_part<<16;
	return TMP_SUCCESS;
}

tmp_err_t tmp_snd_16l(struct tmp_io *__tmp_io, mdl_u16_t __data) {
	tmp_err_t any_err;
	if (_err(any_err = tmp_snd_byte(__tmp_io, __data&0xFF))) return any_err;
	if (_err(any_err = tmp_snd_byte(__tmp_io, __data>>8&0xFF))) return any_err;
	return TMP_SUCCESS;
}

tmp_err_t tmp_rcv_16l(struct tmp_io *__tmp_io, mdl_u16_t *__data) {
	tmp_err_t any_err;
	mdl_u8_t _16b_part;

	_16b_part = 0;
	if (_err(any_err = tmp_rcv_byte(__tmp_io, &_16b_part))) return any_err;
	*__data |= (mdl_u16_t)_16b_part;

	_16b_part = 0;
	if (_err(any_err = tmp_rcv_byte(__tmp_io, &_16b_part))) return any_err;
	*__data |= (mdl_u16_t)_16b_part<<8;
	return TMP_SUCCESS;
}
# endif

void tmp_set_opt(struct tmp_io *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_CUTOFF:
			__tmp_io->snd_cutoff = *(mdl_uint_t*)__data;
		break;
		case TMP_OPT_RCV_CUTOFF:
			__tmp_io->rcv_cutoff = *(mdl_uint_t*)__data;
		break;
	}
}

void tmp_get_opt(struct tmp_io *__tmp_io, tmp_opt_t __tmp_opt, void *__data) {
	switch(__tmp_opt) {
		case TMP_OPT_SND_CUTOFF:
			*(mdl_uint_t*)__data = __tmp_io->snd_cutoff;
		break;
		case TMP_OPT_RCV_CUTOFF:
			*(mdl_uint_t*)__data = __tmp_io->rcv_cutoff;
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
