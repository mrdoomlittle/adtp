# ifndef __tmp__config__hpp__
# define __tmp__config__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <iostream>
    # include <boost/cstdint.hpp>
# endif

namespace tmp
{
    enum __time_t : int unsigned 
    {
        __nano_seconds = 0
    };
}

# define digit_pin_input_mode 0x1
# define digit_pin_output_mode 0x0

# define digit_pin_high_state 0x1
# define digit_pin_low_state 0x0

# define def_digit_clock_pin_id 6
# define def_digit_mio_clock_pid 6
# define def_digit_dati_clock_pid 7
# define def_digit_dato_clock_pid 8

# define def_clock_sstate_ignore 0x1
const int(def_clock_power_state [2]) = { 0x1, 0x0 } ;
# define def_clock_trigger_method 0

# define def_digit_dati_latch_pid 9
# define def_digit_dato_latch_pid 10

# define def_digit_i_pin_count 2
const int unsigned def_digit_dati_pids [def_digit_i_pin_count] = { 2, 3 } ;
const int(def_i_pin_power_state [def_digit_i_pin_count] [2]) = { {0x1, 0x0}, {0x1, 0x0} };

# define def_dati_bitset_length 8
# define def_ibit_read_holdup 1
# define def_ibyte_read_holdup 1
# define def_ibitset_buff_size 8

# define def_digit_o_pin_count 2
const int unsigned def_digit_dato_pids [def_digit_o_pin_count] = { 4, 5 } ;
const int(def_o_pin_power_state [def_digit_o_pin_count] [2]) = { {0x1, 0x0}, {0x1, 0x0} };

# define def_dato_bitset_length 8
# define def_obit_write_holdup 1
# define def_obyte_write_holdup 1
# define def_obitset_buff_size 8

# ifdef ARDUINO
    # define def_mltick_holdup 300000
    # define def_iltick_holdup 300000
# else
    # define def_mltick_holdup 3000000
    # define def_iltick_holdup 3000000
# endif

# define def_shared_i_var_count 1
# define def_shared_o_var_count 1

# define def_shared_i_buff_size 5
# define def_shared_o_buff_size 5

# endif /*__tmp__config__hpp__*/
