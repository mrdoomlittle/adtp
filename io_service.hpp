# ifndef __io__service__hpp__
# define __io__service__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <boost/cstdint.hpp>
# endif

# include "itmp_config.hpp"
# include "dynamic_array.hpp"
# include "dynamic_buffer.hpp"
# include "pin_manager.hpp"
# include "bitset.hpp"

/* example: if the start state is 0x0 then the clock will start ticking when changes to 0x1
*/
namespace itmp { class io_service : public pin_manager
{
    protected :
        //pin_manager(* pin_manager_cptr ) = new pin_manager();
    private :
        int unsigned(digit_i_pin_count ) = def_digit_i_pin_count;
        int unsigned(digit_o_pin_count ) = def_digit_o_pin_count;
        int unsigned(clock_start_state ) = 0x0;
        int unsigned(ibyte_read_delay ) = 0;

        int unsigned(ibit_read_delay ) = 0;

        int unsigned(infi_bitset_length ) = 0;

        int unsigned(obyte_write_delay ) = 0;

        int unsigned(obit_write_delay ) = 0;

        int unsigned(info_bitset_length ) = 0;

        int unsigned(ibitset_buff_size ) = 0;
        int unsigned(obitset_buff_size ) = 0;

        int unsigned(shared_i_var_count ) = 0;
        int unsigned(shared_o_var_count ) = 0;

        int unsigned(shared_i_buff_size ) = 0;
        int unsigned(shared_o_buff_size ) = 0;
    protected :
        typedef void( (set_digit_pmode_ft ) (uint8_t, uint8_t) );
        set_digit_pmode_ft(* set_digit_pmode_fptr ) = nullptr;

        typedef void( (set_digit_pstate_ft) (uint8_t, uint8_t) );
        set_digit_pstate_ft(* set_digit_pstate_fptr ) = nullptr;

        typedef int( (get_digit_pstate_ft ) (uint8_t) );
        get_digit_pstate_ft(* get_digit_pstate_fptr ) = nullptr;

        typedef void( (extern_mlinit_ft ) (io_service *) );
        extern_mlinit_ft(* extern_mlinit_fptr ) = nullptr;

        typedef void( (extern_mltick_ft ) (io_service *) );
        extern_mltick_ft(* extern_mltick_fptr ) = nullptr;
    public :
        io_service
        (
            set_digit_pmode_ft(* __set_digit_pmode_fptr) = nullptr,
            set_digit_pstate_ft(* __set_digit_pstate_fptr) = nullptr,
            get_digit_pstate_ft(* __get_digit_pstate_fptr) = nullptr,
            extern_mlinit_ft(* __extern_mlinit_fptr) = nullptr,
            extern_mltick_ft(* __extern_mltick_fptr) = nullptr
        );

        ~io_service( ) { }
    private :
        int unsigned(mltick_delay) = def_mltick_delay;
        int unsigned(iltick_delay) = def_iltick_delay;

        int unsigned(real_mltick_count) = 0;
        int unsigned(real_iltick_count) = 0;
        int unsigned(temp_iltick_count) = 0;

        int unsigned(i_iltick_count) = 0;
        int unsigned(o_iltick_count) = 0;

        void
        (update_rmltick_count (int unsigned(__update_amount ) ) );
        void
        (update_rimltick_count (int unsigned(__update_amount ) ) );

        bool(ilclockp_toggled) = false;
        int unsigned(ilclockp_tcount) = 0;

        bool(ilclockn_toggled ) = false;
        int unsigned(ilclockn_tcount ) = 0;

        uint8_t
        (* digit_infi_bitset ) = new uint8_t [infi_bitset_length];

        bool
        (* i_bitset_finished ) = new bool [(infi_bitset_length / digit_i_pin_count)];

        int unsigned(i_bitset_fcount ) = 0;
    public :
        dynamic_buffer <uint8_t> (i_bitset_buffer );
        int unsigned(i_bitset_buff_pos [2]) = {0, 0};

        enum sg_type : int unsigned { __individual = 0, __total_array = 1 } ;
        enum shift_direction : int unsigned { __right = 0, __left = 1 } ;
        enum bitset_id : int unsigned { __i_bitset = 0, __o_bitset = 1 } ;

        typedef uint8_t __bitset_type;

        void
        (set_io_bitset (int unsigned(__bitset_id), __bitset_type(* __io_bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)));

        __bitset_type
        (* get_io_bitset (int unsigned(__bitset_id), int unsigned(__get_type), int unsigned(__ibitset_arr_pos)));

        void
        (shift_io_bitset (int unsigned(__bitset_id), int unsigned(__shift_direction), int unsigned(__shift_amount)));

        void
        (flip_io_bitset (int unsigned(__bitset_id)));

    private :
        void
        (set_i_bitset (uint8_t(* __i_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)));

        uint8_t
        (* get_i_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)));

        void
        (set_o_bitset (uint8_t(* __o_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)));

        uint8_t
        (* get_o_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)));

        bitset <__bitset_type> (* digit_io_bitset ) = new bitset <__bitset_type> [2];

        uint8_t
        (* digit_info_bitset ) = new uint8_t [info_bitset_length];

        bool
        (* o_bitset_finished ) = new bool [(info_bitset_length / digit_o_pin_count)];

        int unsigned(o_bitset_fcount ) = 0;

    public :
        dynamic_buffer <uint8_t> (o_bitset_buffer);
        int unsigned(o_bitset_buff_pos [2]) = {0, 0};
    private :
        int unsigned(digit_i_buffer_pos ) = 0;
        int unsigned(digit_o_buffer_pos ) = 0;

        int unsigned(ibp_pcount_multiplier ) = 0;
        int unsigned(obp_pcount_multiplier ) = 0;
        int unsigned(i_bitsetf_truec ) = 0;
        int unsigned(o_bitsetf_truec ) = 0;

        uint8_t
        (* digit_i_buffer ) = new uint8_t [digit_i_pin_count];
        uint8_t
        (* digit_o_buffer ) = new uint8_t [digit_o_pin_count];

        bool(i_buffer_finished ) = false;
        bool(o_buffer_finished ) = false;

        uint8_t
        (* shared_i_variable ) = new uint8_t [shared_i_var_count];
        uint8_t
        (* shared_o_variable ) = new uint8_t [shared_o_var_count];

        void
        (set_digit_pmode (uint8_t(__pin_id ), uint8_t(__pin_mode ) ) );
        void
        (set_digit_pstate (uint8_t(__pin_id ), uint8_t(__pin_state ) ) );
        bool
        (get_digit_pstate (uint8_t(__pin_id ) ));

        void
        (call_extern_mlinit (io_service(* __class_ptr ) ) );
        void
        (call_extern_mltick (io_service(* __class_ptr ) ) );

        int unsigned(external_clock_ptcount ) = 0;
        int unsigned(external_clock_ntcount ) = 0;

        bool(external_clock_reading ) = false;

        void
        (update_clock_ptcount (int unsigned(__update_amount ) ) );
        void
        (update_clock_ntcount (int unsigned(__update_amount ) ) );
        void
        (set_clock_ptcount (int unsigned(__clock_ptcount ) ) );
        void
        (set_clock_ntcount (int unsigned(__clock_ntcount ) ) );

        bool
        (is_clock_reading (bool(__is_type ) ) );
        bool
        (is_external_clock (bool(__is_type ) ) );

        void
        (toggle_mloop_state( ) );
        void
        (toggle_iloop_state( ) );
        void
        (update_clock_reading( ) );

        void
        (update_mltick_count (int unsigned(__update_amount ) ) );
        void
        (update_iltick_count (int unsigned(__update_amount ) ) );
        void
        (set_mltick_count (int unsigned(__mltick_count ) ) );
        void
        (set_iltick_count (int unsigned(__iltick_count ) ) );

        int unsigned
        (get_mltick_count( ) );
        int unsigned
        (get_iltick_count( ) );

        void
        (reset_mltick_count( ) );
        void
        (reset_iltick_count( ) );

        bool
        (is_mloop_running (bool(__is_type ) ) );
        bool
        (is_iloop_running (bool(__is_type ) ) );

        int unsigned(service_mltick_count ) = 0;
        int unsigned(service_iltick_count ) = 0;

        bool(service_mloop_running ) = false;
        bool(service_iloop_running ) = false;
} ; }

# endif /*__io__service__hpp__*/
