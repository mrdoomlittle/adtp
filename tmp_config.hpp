# ifndef __tmp__config__hpp__
# define __tmp__config__hpp__

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
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
    enum time_format : int unsigned {
        __nano_seconds,
        __mloop_tick_count
    } ;

    enum port_state : int unsigned {
        __active,
        __inactive,
        __enabled,
        __disabled,
        __reserved,
        __taken,
        __nottaken
    } ;

    enum io_t : int unsigned { __i = 0, __o = 1 } ;

    // this will create a default interface using the data below / some
    extern bool const
        (create_default_interface);

    // this will be the size of the header for eatch packet of data
    // it will be fixed because it need to include the packet size without the header size
    extern int unsigned const
        (dpacket_header_size);

    extern int unsigned const
        (max_dpacket_size);
    extern int unsigned const
        (min_dpacket_size);

    extern uint8_t const
        (maximum_digit_pid);
    extern uint8_t const
        (minimum_digit_pid);

    extern int const
        (digit_pin_input_mode);
    extern int const
        (digit_pin_output_mode);

    extern int const
        (digit_pin_high_state);
    extern int const
        (digit_pin_low_state);

    extern uint8_t const
        (def_digit_dati_clock_pid);
    extern uint8_t const
        (def_digit_dato_clock_pid);

    extern int unsigned const
        (def_dati_bitset_length);
    extern int unsigned const
        (def_dato_bitset_length);

    extern int unsigned const
        (def_read_uphold_tformat);
    extern int unsigned const
        (def_write_uphold_tformat);

    extern int unsigned const
        (def_ibit_read_holdup);
    extern int unsigned const
        (def_obit_write_holdup);

    extern int unsigned const
        (def_ibyte_read_holdup);
    extern int unsigned const
        (def_obyte_write_holdup);

    extern int unsigned const
        (def_ibitset_buff_size);
    extern int unsigned const
        (def_obitset_buff_size);

    // REMINDER: change name for this
    extern int unsigned const
        (def_mltick_holdup);
    extern int unsigned const
        (def_iltick_holdup);

    extern int unsigned const
        (def_digit_dati_pcount);
    extern int unsigned const
        (def_digit_dato_pcount);

    extern uint8_t const
        (def_digit_dati_pids[]);
    extern uint8_t const
        (def_digit_dato_pids[]);

    extern int unsigned const
        (def_digit_dati_latch_pid);
    extern int unsigned const
        (def_digit_dato_latch_pid);

    extern int unsigned const
        (def_digit_mio_clock_pid);

    extern int unsigned const
        (def_clock_sstate_ignore);
    extern int unsigned const
        (def_clock_ttrigger_method);
}

# endif /*__tmp__config__hpp__*/
