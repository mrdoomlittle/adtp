# ifndef __itmp__config__hpp__
# define __itmp__config__hpp__

# define digit_pin_mode_output 0x0
# define digit_pin_mode_input 0x1

# define digit_pin_state_high 0x1
# define digit_pin_state_low 0x0

# define def_clock_start_state 0x1

# define def_digit_clock_pin_id 6
// need to implement somthing to allow me to select 
// the clock tick state example: true or false or the change from x to x 

// both are for later
constexpr int def_clock_pstate[2] = {0x1, 0x0};
# define def_clock_trigger_method 0

# define def_digit_i_pin_count 2
constexpr int def_digit_i_pin_id [2] = {2, 3};
// this will be used for later
constexpr int def_i_pin_pstate [2] = {0x1, 0x0};


# define def_digit_o_pin_count 2
constexpr int def_digit_o_pin_id [2] = {4, 5};
// this will be used for later
constexpr int def_o_pin_pstate [2] = {0x1, 0x0};

# define def_digit_latch_pin_id 7
// this will be used for later
constexpr int def_latch_pstate [2] {0x1, 0x0};

// the size of the bitset (00000000) 256 diffrent combinations
# define def_i_bitset_size 8
# define def_o_bitset_size 8

// the amount of time in clock ticks for eatch byte aka bitset
# define def_ibyte_read_delay 1
# define def_obyte_write_delay 1

// the amount of time in clock ticks eatch bit takes to read/write
# define def_ibit_read_delay 1
# define def_obit_write_delay 1

// this is just to slow things to make debugging easier
# ifdef ARDUINO
    // the 101 has a slower clock cycle
    # define def_mltick_delay 300000
    # define def_iltick_delay 300000
# else
    # define def_mltick_delay 3000000
    # define def_iltick_delay 3000000
# endif

// the size of the buffer storing the bitsets
# define def_ibitset_buff_size 8
# define def_obitset_buff_size 8

// this is for later when alll is working
// it will be used for storing int char etc
// example :
/*
for this we will use bitwise
to turn are BITSET into a int, uint, char etc or array
VAR 0 = BITSET 0 
*/
# define def_shared_i_var_count 1
# define def_shared_o_var_count 1

# define def_shared_i_buff_size 5
# define def_shared_o_buff_size 5

# endif /*__itmp__config__hpp__*/
