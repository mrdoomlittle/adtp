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
    // change int unsigned to uint8_t as we are not using a large num
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

    enum io_t : std::uint8_t { __itype, __otype };

    enum lstate : std::uint8_t { __not_running, __running };

    //enum sig_comp_t std::uint8_t
    //{
        // will add other options
        ///__all_of_them
    //};

    // this will create a default interface using the data below / some
    extern uint8_t const
        (create_default_interface);


    // this will compress the clock and latch to gether into one wire
    // and the all i pins and all o pins
    // 0 i clock and latch
    // 1 o clock and latch
    // 3 i data stream << all of the pins
    // 4 o data stream << all of the pins
    extern uint8_t const
        (use_signal_compressing);

    extern uint8_t const
        (signal_compressing_type);
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
        (def_dati_bit_read_holdup);
    extern int unsigned const
        (def_dato_bit_write_holdup);

    extern int unsigned const
        (def_dati_byte_read_holdup);
    extern int unsigned const
        (def_dato_byte_write_holdup);

    extern int unsigned const
        (def_dati_bitset_buff_size);
    extern int unsigned const
        (def_dato_bitset_buff_size);

    // REMINDER: change name for this
    extern int unsigned const
        (def_mltrigger_holdup);
    extern int unsigned const
        (def_iltrigger_holdup);

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

    extern int unsigned const
        (def_dati_clock_ppslength);
    extern int unsigned const
        (def_dato_clock_ppslength);

    extern int unsigned const
        (def_dati_clock_pnslength);
    extern int unsigned const
        (def_dato_clock_pnslength);

    extern int unsigned const
        (def_dati_latch_ppslength);
    extern int unsigned const
        (def_dato_latch_ppslength);

    extern int unsigned const
        (def_dati_latch_pnslength);
    extern int unsigned const
        (def_dato_latch_pnslength);
}

# endif /*__tmp__config__hpp__*/
