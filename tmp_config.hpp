# ifndef __tmp__config__hpp__
# define __tmp__config__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

// i am going to leave this as it is for now
// 50% might change it back to the way it was

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <iostream>
    # include <boost/cstdint.hpp>
# endif

namespace tmp_config
{
    enum time_format : int unsigned
    {
        __nano_seconds = 0,
        __mloop_tick_count = 1
    };

    extern int const(digit_pin_input_mode);
    extern int const(digit_pin_output_mode);

    extern int const(digit_pin_high_state);
    extern int const(digit_pin_low_state);

    extern uint8_t const(def_digit_dati_clock_pid);
    extern uint8_t const(def_digit_dato_clock_pid);

    extern int unsigned(def_dati_bitset_length);
    extern int unsigned(def_dato_bitset_length);

    extern int unsigned(def_read_uphold_tformat);
    extern int unsigned(def_write_uphold_tformat);

    extern int unsigned(def_ibit_read_holdup);
    extern int unsigned(def_obit_write_holdup);

    extern int unsigned(def_ibyte_read_holdup);
    extern int unsigned(def_obyte_write_holdup);

    extern int unsigned(def_ibitset_buff_size);
    extern int unsigned(def_obitset_buff_size);

    extern int unsigned(def_mltick_holdup);
    extern int unsigned(def_iltick_holdup);

    extern int const unsigned(def_digit_i_pin_count);
    extern int const unsigned(def_digit_o_pin_count);

    extern int unsigned const def_digit_dati_pids[];
    extern int unsigned const def_digit_dato_pids[];

    extern int unsigned def_digit_dati_latch_pid;
    extern int unsigned def_digit_dato_latch_pid;

    extern int unsigned def_digit_mio_clock_pid;
    extern int unsigned def_clock_sstate_ignore;
    extern int unsigned def_clock_trigger_method;
}
# endif /*__tmp__config__hpp__*/
