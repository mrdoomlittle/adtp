# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__
# include "itmp_config.hpp"
# include "dynamic_array.hpp"
# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <boost/cstdint.hpp>
# endif

namespace itmp { class pin_manager
{
    private :
        uint8_t(digit_infi_clock_pid ) = def_digit_infi_clock_pid;
        uint8_t(digit_info_clock_pid ) = def_digit_info_clock_pid;

        bool(infi_clock_pid_sstate ) = false;
        bool(info_clock_pid_sstate ) = false;

        int(infi_clock_pstate ) = digit_pin_low_state;
        int(info_clock_pstate ) = digit_pin_low_state;

        int(infi_clock_pmode ) = digit_pin_input_mode;
        int(info_clock_pmode ) = digit_pin_output_mode;

        uint8_t(digit_infi_latch_pid ) = def_digit_infi_latch_pid;
        uint8_t(digit_info_latch_pid ) = def_digit_info_latch_pid;

        bool(infi_latch_pid_sstate ) = false;
        bool(info_latch_pid_sstate ) = false;

        int(infi_latch_pstate ) = digit_pin_low_state;
        int(info_latch_pstate ) = digit_pin_low_state;

        int(infi_latch_pmode ) = digit_pin_input_mode;
        int(info_latch_pmode ) = digit_pin_output_mode;

        int unsigned(digit_infi_pcount ) = def_digit_i_pin_count;

        dynamic_array <bool> infi_pid_sstate_list;

        dynamic_array <int> infi_pstate_list;

        dynamic_array <int> infi_pmode_list;

        dynamic_array <uint8_t> digit_infi_pid_list;

        int unsigned(digit_info_pcount ) = def_digit_o_pin_count;

        dynamic_array <bool> info_pid_sstate_list;

        dynamic_array <int> info_pstate_list;

        dynamic_array <int> info_pmode_list;

        dynamic_array <uint8_t> digit_info_pid_list;
    public :
        pin_manager ( );
        ~pin_manager( ) { }

    private :
        bool
        (is_pid_irange (uint8_t(__digit_pid ) ) );
        bool
        (is_pstate_icheck (uint8_t(__digit_pstate ) ) );
        bool
        (is_pmode_icheck (uint8_t(__digit_pmode ) ) );

    public :
        /* i am using the same method as a shift register
            there is only 4 types of pins eg the clock latch (data input) or (data output)
        */

        void
        (set_infi_clock_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_infi_clock_pid( ) );
        void
        (uset_infi_clock_pid( ) );
        void
        (set_infi_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_infi_clock_pid_sstate( ) );
        bool
        (is_infi_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (update_infi_clock_pstate (int(__infi_clock_pstate ) ) );
        int
        (get_infi_clock_pstate( ) );
        int
        (get_infi_clock_pmode( ) );

        void
        (set_info_clock_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_info_clock_pid( ) );
        void
        (uset_info_clock_pid( ) );
        void
        (set_info_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_info_clock_pid_sstate( ) );
        bool
        (is_info_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (update_info_clock_pstate (int(__info_clock_pstate ) ) );
        int
        (get_info_clock_pstate( ) );
        int
        (get_info_clock_pmode( ) );

        void
        (set_infi_latch_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_infi_latch_pid( ) );
        void
        (uset_infi_latch_pid( ) );
        void
        (set_infi_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_infi_latch_pid_sstate( ) );
        bool
        (is_infi_latch_pid_sstate (bool(__pid_sstate ) ) );
        void
        (update_infi_latch_pstate (int(__infi_latch_pstate ) ) );
        int
        (get_infi_latch_pstate( ) );
        int
        (get_infi_latch_pmode( ) );

        void
        (set_info_latch_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_info_latch_pid( ) );
        void
        (uset_info_latch_pid( ) );
        void
        (set_info_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_info_latch_pid_sstate( ) );
        bool
        (is_info_latch_pid_sstate (bool(__pid_sstate ) ) );
        void
        (update_info_latch_pstate (int(__info_latch_pstate ) ) );
        int
        (get_info_latch_pstate( ) );
        int
        (get_info_latch_pmode( ) );

        void
        (set_infi_pid(uint8_t(__digit_pid), int unsigned(__infi_pid_pos)));
        uint8_t
        (get_infi_pid(int unsigned(__infi_pid_pos)));
        void
        (uset_infi_pid(int unsigned(__infi_pid_pos)));
        void
        (set_infi_pid_sstate(bool(__pid_sstate ), int unsigned(__infi_pid_pos)));
        bool
        (get_infi_pid_sstate(int unsigned(__infi_pid_pos)));
        bool
        (is_infi_pid_sstate(bool(__pid_sstate ) ,int unsigned(__infi_pid_pos)));
        int unsigned
        (get_infi_pcount( ) )
        {
            return(this-> digit_infi_pcount);
        }

        void
        (set_info_pid(uint8_t(__digit_pid), int unsigned(__info_pid_pos)));
        uint8_t
        (get_info_pid(int unsigned(__info_pid_pos)));
        void
        (uset_info_pid(int unsigned(__info_pid_pos)));
        void
        (set_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)));
        bool
        (get_info_pid_sstate(int unsigned(__info_pid_pos)));
        bool
        (is_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)));
        int unsigned
        (get_info_pcount( ) )
        {
            return(this-> digit_info_pcount);
        }
} ; }

# endif /*__pin__manager__hpp__*/
