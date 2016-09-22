# ifndef __itmp__config__hpp__
# define __itmp__config__hpp__

# define digit_pin_input_mode 0x1
# define digit_pin_output_mode 0x0

# define digit_pin_high_state 0x1
# define digit_pin_low_state 0x0

# define def_digit_clock_pin_id 6
# define def_clock_start_state 0x1
const int(def_clock_power_state [2]) = { 0x1, 0x0 } ;
# define def_clock_trigger_method 0

# define def_digit_latch_pin_id 7

# define def_digit_i_pin_count 2
const int unsigned def_digit_i_pin_ids [def_digit_i_pin_count] = { 2, 3 } ;
const int(def_i_pin_power_state [def_digit_i_pin_count] [2]) = { {0x1, 0x0}, {0x1, 0x0} };

# define def_i_bitset_size 8
# define def_ibit_read_delay 1
# define def_ibyte_read_delay 1
# define def_ibitset_buff_size 8

# define def_digit_o_pin_count 2
const int unsigned def_digit_o_pin_ids [def_digit_o_pin_count] = { 2, 3 } ;
const int(def_o_pin_power_state [def_digit_o_pin_count] [2]) = { {0x1, 0x0}, {0x1, 0x0} };

# define def_o_bitset_size 8
# define def_obit_write_delay 1
# define def_obyte_write_delay 1
# define def_obitset_buff_size 8

# ifdef ARDUINO
    # define def_mltick_delay 300000
    # define def_iltick_delay 300000
# else
    # define def_mltick_delay 3000000
    # define def_iltick_delay 3000000
# endif

# define def_shared_i_var_count 1
# define def_shared_o_var_count 1

# define def_shared_i_buff_size 5
# define def_shared_o_buff_size 5

# endif /*__itmp__config__hpp__*/
