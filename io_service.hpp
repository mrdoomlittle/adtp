# ifndef __io__service__hpp__
# define __io__service__hpp__

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

# include "tmp_config.hpp"
# include "dynamic_array.hpp"
# include "dynamic_buffer.hpp"
# include "pin_manager.hpp"
# include "bitset.hpp"
# include "data_packet.hpp"
# include "shift_reg.hpp"
# include "time.hpp"
# include "interface.hpp"
# include "array.hpp"
/* example: if the start state is 0x0 then the clock will start ticking when changes to 0x1
*/
namespace tmp { class io_service
{

    private :
        int unsigned(amount_of_interfaces) = 2;// not needed ?
    protected :
        typedef time time_ct;
        time_ct
            (* time_cinst_ptr ) = nullptr;

        typedef pin_manager pmanager_ct;
        pmanager_ct
            (* pmanager_cinst_ptr) = nullptr;

        typedef shift_reg sregister_ct;
        sregister_ct
            (* sregister_cinst_ptr ) = nullptr;

        pmanager_ct
        (* get_pmanager_cinst_ptr());
        sregister_ct
        (* get_sregister_cinst_ptr());

        void
        (init_pmanager_cinst());

        bool(has_pmanager_cinst_init ) = false;

        void
        (init_sregister_cinst());

        bool(has_sregister_cinst_init ) = false;

        typedef interface interface_ct;
        interface_ct
            (* interface_cinst_ptr ) = nullptr;
        public:
        void
        (init_interface_cinst());
        interface_ct
            (* get_interface_cinst_ptr());

        bool(has_interface_cinst_init ) = false;

    private :
        int unsigned(digit_i_pin_count ) =
            (tmp_config::def_digit_dati_pcount);
        int unsigned(digit_o_pin_count ) =
            (tmp_config::def_digit_dato_pcount);

        int unsigned(clock_sstate_ignore ) = 0x0;

        dynamic_array <int unsigned> (dati_bitset_length);
        dynamic_array <int unsigned> (dato_bitset_length);

        int unsigned(ibyte_read_holdup ) = 0;
        int unsigned(obyte_write_holdup ) = 0;

        int unsigned(ibit_read_holdup ) = 0;
        int unsigned(obit_write_holdup ) = 0;

        int unsigned(ibitset_buff_size ) = 0;
        int unsigned(obitset_buff_size ) = 0;
    protected :
        typedef void( (set_digit_pmode_ft ) (uint8_t, uint8_t) );
        set_digit_pmode_ft
            (* set_digit_pmode_fptr ) = nullptr;

        typedef void( (set_digit_pstate_ft) (uint8_t, uint8_t) );
        set_digit_pstate_ft
            (* set_digit_pstate_fptr ) = nullptr;

        typedef int( (get_digit_pstate_ft ) (uint8_t) );
        get_digit_pstate_ft
            (* get_digit_pstate_fptr ) = nullptr;

        typedef int unsigned long( (get_high_rclock_ft) (int unsigned) );
        get_high_rclock_ft
            (* get_high_rclock_fptr ) = nullptr;

        // change to bool  or int unsigned
        typedef int unsigned( (extern_mlinit_ft ) (io_service *) );
        extern_mlinit_ft
            (* extern_mlinit_fptr ) = nullptr;

        typedef int unsigned( (extern_mltick_ft ) (io_service *) );
        extern_mltick_ft
            (* extern_mltick_fptr ) = nullptr;
    public :
        io_service( );
        ~io_service( );

        void
        (service_init (
            set_digit_pmode_ft
                (* __set_digit_pmode_fptr) = nullptr,
            set_digit_pstate_ft
                (* __set_digit_pstate_fptr) = nullptr,
            get_digit_pstate_ft
                (* __get_digit_pstate_fptr) = nullptr,
            get_high_rclock_ft
                (* __get_high_rclock_fptr ) = nullptr,
            extern_mlinit_ft
                (* __extern_mlinit_fptr) = nullptr,
            extern_mltick_ft
                (* __extern_mltick_fptr) = nullptr
        ) );

        void
        (set_ptr_to_sdigit_pmode_f (set_digit_pmode_ft(* __set_digit_pmode_fptr) ) );
        void
        (set_ptr_to_sdigit_pstate_f (set_digit_pstate_ft(* __set_digit_pstate_fptr) ) );
        void
        (set_ptr_to_gdigit_pstate_f (get_digit_pstate_ft(* __get_digit_pstate_fptr) ) );
        void
        (set_ptr_to_ghigh_rclock_f (get_high_rclock_ft(* __get_high_rclock_fptr) ) );
        void
        (set_ptr_to_extern_mlinit_f (extern_mlinit_ft(* __extern_mlinit_fptr) ) );
        void
        (set_ptr_to_extern_mltick_f (extern_mltick_ft(* __extern_mltick_fptr) ) );

        bool
        (is_ptr_to_sdigit_pmode_f (set_digit_pmode_ft(* __is_type) ) );
        bool
        (is_ptr_to_sdigit_pstate_f (set_digit_pstate_ft(* __is_type) ) );
        bool
        (is_ptr_to_gdigit_pstate_f (get_digit_pstate_ft(* __is_type) ) );
        bool
        (is_ptr_to_ghigh_rclock_f (get_high_rclock_ft(* __is_type) ) );
        bool
        (is_ptr_to_extern_mlinit_f (extern_mlinit_ft(* __is_type) ) );
        bool
        (is_ptr_to_extern_mltick_f (extern_mltick_ft(* __is_type) ) );
    private :
        int unsigned(mltick_holdup) = tmp_config::def_mltick_holdup;
        int unsigned(iltick_holdup) = tmp_config::def_iltick_holdup;

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

        bool(ilclockn_toggled) = false;
        int unsigned(ilclockn_tcount) = 0;

    public :
    // NOTE: might change to struct or keep as enum/ and it move to tmp_config
        enum sg_type : int unsigned { __individual = 0, __total_array = 1 } ;
        enum shift_direction : int unsigned { __right = 0, __left = 1 } ;
        enum bitset_id : int unsigned { __i_bitset = 0, __o_bitset = 1 } ;

        typedef uint8_t __bitset_type;

        void
        (set_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), __bitset_type(* __io_bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)));

        __bitset_type
        (* get_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), int unsigned(__get_type), int unsigned(__ibitset_arr_pos)));

        void
        (shift_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), int unsigned(__shift_direction), int unsigned(__shift_amount)));

        void
        (flip_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id)));

    private :
        void
        (set_i_bitset (uint8_t(* __i_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)));
        void
        (set_o_bitset (uint8_t(* __o_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)));

        uint8_t
        (* get_i_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)));
        uint8_t
        (* get_o_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)));

        //bitset <__bitset_type> (* digit_io_bitset ) = new bitset <__bitset_type> [2];
        bitset_list <__bitset_type> (* digit_datio_bitset) = new bitset_list <__bitset_type> [2];

        uint8_t
        (* digit_dati_bitset ) = new uint8_t [/*dati_bitset_length*/8];
        uint8_t
        (* digit_dato_bitset ) = new uint8_t [/*dati_bitset_length*/8];

        bool
        (* i_bitset_finished ) = new bool [(/*dati_bitset_length*/8 / digit_i_pin_count)];
        bool
        (* o_bitset_finished ) = new bool [(/*dati_bitset_length*/8 / digit_o_pin_count)];

        int unsigned(i_bitset_fcount ) = 0;
        int unsigned(o_bitset_fcount ) = 0;

    public :
    /* NOTE: need to fix the dynamic buffer as its doing the same things that the dynamic array was doing
        if block size is higher then 21 it will cause a core dump
    */
        int unsigned buffsize = 21;
        void (add_to_obs_stream(bitset<int unsigned>(& __obs), int unsigned(__iface)))
        {
            for (int unsigned(x ) = 0; x != 8; x ++)
                (this-> dato_obs_stream_buff).add_to_dbuff(__obs.get_bitset(0, x), 2, __iface, 0, 0, false, true, true);
        }

        dynamic_buffer <int unsigned> (dato_obs_stream_buff);

        //dynamic_buffer <uint8_t> (* datio_bitset_buff) = new dynamic_buffer <uint8_t> [2];

        dynamic_buffer <uint8_t> (dati_bitset_buff); // this is the newly named one
        dynamic_buffer <uint8_t> (dato_bitset_buff); // this is the newly named one

        int unsigned(i_bitset_buff_pos [2]) = {0, 0};
        int unsigned(o_bitset_buff_pos [2]) = {0, 0};
    private :
        int unsigned(digit_i_buffer_pos ) = 0;
        int unsigned(digit_o_buffer_pos ) = 0;

        int unsigned(ibp_pcount_multiplier ) = 0;
        int unsigned(obp_pcount_multiplier ) = 0;

        int unsigned(i_bitsetf_truec ) = 0;
        int unsigned(o_bitsetf_truec ) = 0;

        int unsigned(dati_clock_ltcount ) = 0;
        bool(is_dati_clock_ppos) = false;

        uint8_t
        (* digit_i_buffer ) = new uint8_t [digit_i_pin_count];
        uint8_t
        (* digit_o_buffer ) = new uint8_t [digit_o_pin_count];

        bool(i_buffer_finished ) = false;
        bool(o_buffer_finished ) = false;

        //enum clock_ttmethod: int unsigned
        //{
        //    __only_when_true = 0,
        //    __only_when_false = 1,
        //    __change_in_clock = 2
        //}

        enum clock_tick_method : int unsigned
        {

        } ;

        int unsigned(clock_ttrigger_method) = (tmp_config::def_clock_ttrigger_method);

        void
        (set_digit_pmode (uint8_t(__digit_pid ), uint8_t(__digit_pmode ) ) );
        void
        (set_digit_pstate (uint8_t(__digit_pid ), uint8_t(__digit_pstate ), int unsigned(__interface_id ) = 0 ) );
        bool
        (get_digit_pstate (uint8_t(__digit_pid ) ));

        int unsigned
        (call_extern_mlinit (io_service(* __class_ptr ) ) );
        int unsigned
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
        (is_external_clock (bool(__is_type ), int unsigned(__interface_id) = 0 ) );

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
