# ifndef __adtp__config__hpp__
# define __adtp__config__hpp__

# define def_clock_start_state 0x1

# define def_digit_clock_pin_id 6

# define def_digit_i_pin_count 2
constexpr int def_digit_i_pin_id [2] = {2, 3};

# define def_digit_o_pin_count 2
constexpr int def_digit_o_pin_id [2] = {4, 5};

# define def_i_bitset_size 8
# define def_o_bitset_size 8

# define def_ibyte_read_delay 1
# define def_obyte_write_delay 1

# define def_ibit_read_delay 1
# define def_obit_write_delay 1

# ifdef ARDUINO
    // the 101 has a slower clock cycle
    # define def_mltick_delay 300000
    # define def_iltick_delay 300000
# else
    # define def_mltick_delay 3000000
    # define def_iltick_delay 3000000
# endif

# define def_ibitset_buff_size 8
# define def_obitset_buff_size 8

# define def_shared_i_var_count 1
# define def_shared_o_var_count 1

# define def_shared_i_buff_size 5
# define def_shared_o_buff_size 5

# endif /*__adtp__config__hpp__*/
