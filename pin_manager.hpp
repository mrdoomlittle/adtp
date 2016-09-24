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
        uint8_t(digit_clock_pid ) = def_digit_clock_pin_id;

        bool
        (clock_pid_sstate ); // allowing multi clocks will be added later
        int unsigned
        (* clock_pin_pstate ) = new int unsigned [2];

        uint8_t(digit_latch_pid ) = def_digit_latch_pin_id;
        bool
        (latch_pid_sstate );
        int unsigned
        (* latch_pin_pstate ) = new int unsigned [2];

        int unsigned(digit_infi_pcount ) = def_digit_i_pin_count;

        dynamic_array <bool> infi_pid_sstate_list;

        dynamic_array <uint8_t> digit_infi_pid_list;

        int unsigned
        (* * i_pin_pstate ) = new int unsigned * [(digit_infi_pcount)];

        int unsigned(digit_info_pcount ) = def_digit_o_pin_count;

        dynamic_array <bool> info_pid_sstate_list;

        dynamic_array <uint8_t> digit_info_pid_list;

        int unsigned
        (* * o_pin_pstate ) = new int unsigned * [(digit_info_pcount)];
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
        (set_clock_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_clock_pid( ) );
        void
        (uset_clock_pid( ) );
        void
        (set_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_clock_pid_sstate( ) );
        bool
        (is_clock_pid_sstate (bool(__pid_sstate ) ) );

        void
        (set_latch_pid (uint8_t(__digit_pid ) ) );
        uint8_t
        (get_latch_pid( ) );
        void
        (uset_latch_pid( ) );
        void
        (set_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (get_latch_pid_sstate( ) );
        bool
        (is_latch_pid_sstate (bool(__pid_sstate ) ) );

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
} ; }

# endif /*__pin__manager__hpp__*/
