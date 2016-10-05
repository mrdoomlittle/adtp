# include "tmp_config.hpp"
// reminder keep as it is for now but might change it by removing tmp_config:: and adding a namespace tmp_config {}
int unsigned(tmp_config::dpacket_header_size) = 8;

int unsigned(tmp_config::max_dpacket_size) = 64; // this is in bytes
int unsigned(tmp_config::min_dpacket_size) = 64;

int const tmp_config::digit_pin_input_mode = 0x1;
int const tmp_config::digit_pin_output_mode = 0x0;

int const tmp_config::digit_pin_high_state = 0x1;
int const tmp_config::digit_pin_low_state = 0x0;

uint8_t const tmp_config::def_digit_dati_clock_pid = 7;
uint8_t const tmp_config::def_digit_dato_clock_pid = 8;

int unsigned tmp_config::def_dati_bitset_length = 8;
int unsigned tmp_config::def_dato_bitset_length = 8;

// this will be implemented later. this will allow you to select what the time format for calulating how long it should delay for
int unsigned tmp_config::def_read_uphold_tformat =
    (time_format::__mloop_tick_count);
int unsigned tmp_config::def_write_uphold_tformat =
    (time_format::__mloop_tick_count);

int unsigned tmp_config::def_ibit_read_holdup = 1;
int unsigned tmp_config::def_obit_write_holdup = 1;

int unsigned tmp_config::def_ibyte_read_holdup = 1;
int unsigned tmp_config::def_obyte_write_holdup = 1;

int unsigned tmp_config::def_ibitset_buff_size = 8;
int unsigned tmp_config::def_obitset_buff_size = 8;

int unsigned const tmp_config::def_digit_i_pin_count = 2;
int unsigned const tmp_config::def_digit_o_pin_count = 2;

int unsigned const tmp_config::def_digit_dati_pids
    [(tmp_config::def_digit_i_pin_count)] = {2, 3};

int unsigned const tmp_config::def_digit_dato_pids
    [(tmp_config::def_digit_o_pin_count)] = {4, 5};

int unsigned tmp_config::def_digit_dati_latch_pid = 9;
int unsigned tmp_config::def_digit_dato_latch_pid = 10;

int unsigned tmp_config::def_digit_mio_clock_pid = 6;
int unsigned tmp_config::def_clock_sstate_ignore = 0x1;
int unsigned tmp_config::def_clock_ttrigger_method = 0;

// NOTE: dont know if this work or not but will be testing this when done
# ifdef ARDUINO
    int unsigned tmp_config::def_mltick_holdup = 300000;
    int unsigned tmp_config::def_iltick_holdup = 300000;
# else
    int unsigned tmp_config::def_mltick_holdup = 3000000;
    int unsigned tmp_config::def_iltick_holdup = 3000000;
# endif
