# ifndef __io__service__hpp__
# define __io__service__hpp__
# include <boost/cstdint.hpp>

# include "dynamic_buffer.hpp"

/* created by mrdoomlittle / daniel robson 
* github: https://github.com/mrdoomlittle
* email: doctordoomlittle@gmail.com
*/

/* example: if the start state is 0x0 then the clock will start ticking when changes to 0x1
*/
# define def_clock_start_state 0x1

# define def_digit_clock_pin_id 6

# define def_digit_i_pin_count 2

# define def_digit_i_pin_id_0 2
# define def_digit_i_pin_id_1 3

# define def_digit_o_pin_count 2
# define def_digit_o_pin_id_0 4
# define def_digit_o_pin_id_1 5

# define def_i_bitset_size 8
# define def_o_bitset_size 8

# define def_ibyte_read_delay 1
# define def_obyte_write_delay 1

# define def_ibit_read_delay 1
# define def_obit_write_delay 1

# define def_mltick_delay 3000000
# define def_iltick_delay 3000000

# define def_ibitset_buff_size 8
# define def_obitset_buff_size 8
# define def_shared_i_var_count 1
# define def_shared_o_var_count 1
# define def_shared_i_buff_size 5
# define def_shared_o_buff_size 5

namespace adtp { class io_service
{
    private :
        int unsigned(clock_start_state ) = def_clock_start_state;

        int unsigned(shared_i_var_count ) = def_shared_i_var_count;

        int unsigned(shared_o_var_count ) = def_shared_o_var_count;

        int unsigned(shared_i_buff_size ) = def_shared_i_buff_size;

        int unsigned(shared_o_buff_size ) = def_shared_o_buff_size;

        int unsigned(digit_i_pin_count ) = def_digit_i_pin_count;
        uint8_t(* digit_i_pin_ids ) = new uint8_t [digit_i_pin_count];

        int unsigned(digit_o_pin_count ) = def_digit_o_pin_count;
        uint8_t(* digit_o_pin_ids ) = new uint8_t [digit_o_pin_count];
        
        uint8_t(digit_clock_pin_id ) = def_digit_clock_pin_id;

        int unsigned(ibyte_read_delay ) = def_ibyte_read_delay;
        int unsigned(obyte_write_delay ) = def_obyte_write_delay;

        int unsigned(ibit_read_delay ) = def_ibit_read_delay;
        int unsigned(obit_write_delay ) = def_obit_write_delay;

        int unsigned(i_bitset_size ) = def_i_bitset_size;
        int unsigned(o_bitset_size ) = def_o_bitset_size;

        int unsigned(ibitset_buff_size ) = def_ibitset_buff_size;
        int unsigned(obitset_buff_size ) = def_obitset_buff_size;
    protected :
        typedef void( (set_digit_pin_mode_ft ) (uint8_t, uint8_t) );
        set_digit_pin_mode_ft(* set_digit_pin_mode_fptr ) = nullptr;

        typedef void( (set_digit_pin_state_ft) (uint8_t, uint8_t) );
        set_digit_pin_state_ft(* set_digit_pin_state_fptr ) = nullptr;

        typedef int( (get_digit_pin_state_ft ) (uint8_t) );
        get_digit_pin_state_ft(* get_digit_pin_state_fptr ) = nullptr;

        typedef void( (external_mlinit_ft ) (io_service *) );
        external_mlinit_ft(* external_mlinit_fptr ) = nullptr;

        typedef void( (external_mltick_ft ) (io_service *) );
        external_mltick_ft(* external_mltick_fptr ) = nullptr;
    public :
        io_service (
            set_digit_pin_mode_ft(* __set_digit_pin_mode_fptr) = nullptr,
            set_digit_pin_state_ft(* __set_digit_pin_state_fptr) = nullptr,
            get_digit_pin_state_ft(* __get_digit_pin_state_fptr) = nullptr,
            external_mlinit_ft(* __external_mlinit_fptr) = nullptr,
            external_mltick_ft(* __external_mltick_fptr) = nullptr
        );
    private :
        int unsigned(mltick_delay ) = def_mltick_delay;
        int unsigned(iltick_delay ) = def_iltick_delay;
        int unsigned(real_mltick_count ) = 0;
        int unsigned(real_iltick_count ) = 0;
        int unsigned(temp_iltick_count ) = 0;
        int unsigned(i_iltick_count ) = 0;
        int unsigned(o_iltick_count ) = 0;

        void (update_rmltick_count (int unsigned(__update_amount ) ) )
        {
            (this-> real_mltick_count ) += __update_amount;
        }

        void (update_rimltick_count (int unsigned(__update_amount ) ) )
        {
            (this-> real_iltick_count ) += __update_amount;
        }

        bool(ilclockp_toggled ) = false; 
        int unsigned(ilclockp_tcount ) = 0;

        bool(ilclockn_toggled ) = false;
        int unsigned(ilclockn_tcount ) = 0;

        uint8_t(* digit_i_bitset ) = new uint8_t [i_bitset_size];
        bool(* i_bitset_finished ) = new bool [(i_bitset_size / digit_i_pin_count)];
        int unsigned(i_bitset_fcount ) = 0; 
        dynamic_buffer <uint8_t *> (i_bitset_buffer);
        int unsigned(i_bitset_buff_pos ) = 0;
       
        uint8_t(* digit_o_bitset ) = new uint8_t [o_bitset_size];
        bool(* o_bitset_finished ) = new bool [(o_bitset_size / digit_o_pin_count)];
        int unsigned(o_bitset_fcount ) = 0;
        dynamic_buffer <uint8_t *> (o_bitset_buffer);
        int unsigned(o_bitset_buff_pos ) = 0;

        int unsigned(digit_i_buffer_pos ) = 0;
        int unsigned(digit_o_buffer_pos ) = 0;

        int unsigned(ibp_pcount_multiplier ) = 0;
        int unsigned(obp_pcount_multiplier ) = 0;
        int unsigned(i_bitsetf_truec ) = 0;
        int unsigned(o_bitsetf_truec ) = 0;

        uint8_t(* digit_i_buffer ) = new uint8_t [digit_i_pin_count];
        uint8_t(* digit_o_buffer ) = new uint8_t [digit_o_pin_count];
        bool(i_buffer_finished ) = false;
        bool(o_buffer_finished ) = false;

        uint8_t(* shared_i_variable ) = new uint8_t [shared_i_var_count];
        uint8_t(* shared_o_variable ) = new uint8_t [shared_o_var_count];

        void (set_digit_pin_mode (uint8_t(__pin_id ), uint8_t(__pin_mode ) ) );
        void (set_digit_pin_state (uint8_t(__pin_id ), uint8_t(__pin_state ) ) );
        bool (get_digit_pin_state (uint8_t(__pin_id ) ));

        void (call_external_mlinit (io_service(* __class_ptr ) ) );
        void (call_external_mltick (io_service(* __class_ptr ) ) );

        int unsigned(external_clock_ptcount ) = 0;
        int unsigned(external_clock_ntcount ) = 0;
        bool(external_clock_reading ) = false;

        void (update_clock_ptcount (int unsigned(__update_amount ) ) );
        void (update_clock_ntcount (int unsigned(__update_amount ) ) );
        void (set_clock_ptcount (int unsigned(__clock_ptcount ) ) );
        void (set_clock_ntcount (int unsigned(__clock_ntcount ) ) );
   
        bool (is_clock_reading (bool(__is_type ) ) );  
        bool (is_external_clock (bool(__is_type ) ) );

        void (toggle_mloop_state( ) );
        void (toggle_iloop_state( ) );
        void (update_clock_reading( ) );

        void (update_mltick_count (int unsigned(__update_amount ) ) );
        void (update_iltick_count (int unsigned(__update_amount ) ) );
        void (set_mltick_count (int unsigned(__mltick_count ) ) );
        void (set_iltick_count (int unsigned(__iltick_count ) ) );

        int unsigned (get_mltick_count( ) );
        int unsigned (get_iltick_count( ) );

        void (reset_mltick_count( ) )
        {
            (this-> service_mltick_count) = 0;
        }

        void (reset_iltick_count( ) )
        {
            (this-> service_iltick_count) = 0;
        }

        bool (is_mloop_running (bool(__is_type ) ) );
        bool (is_iloop_running (bool(__is_type ) ) );
        int unsigned(service_mltick_count ) = 0;
        int unsigned(service_iltick_count ) = 0;
        bool(service_mloop_running ) = false;
        bool(service_iloop_running ) = false;
} ; }

# endif /*__io__service__hpp__*/
