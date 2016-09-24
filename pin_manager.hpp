# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

# include "itmp_config.hpp"
# include "dynamic_array.hpp"

# ifndef ARDUINO
    # include <boost/cstdint.hpp>
# else
    # include <stdint.h>
# endif

namespace itmp { class pin_manager
{
    private :
        uint8_t(digit_mio_clock_pid ) = def_digit_mio_clock_pid;
        uint8_t(digit_infi_clock_pid ) = def_digit_infi_clock_pid;
        uint8_t(digit_info_clock_pid ) = def_digit_info_clock_pid;
        uint8_t(digit_infi_latch_pid ) = def_digit_infi_latch_pid;
        uint8_t(digit_info_latch_pid ) = def_digit_info_latch_pid;

        bool(mio_clock_pid_sstate ) = false;
        bool(infi_clock_pid_sstate ) = false;
        bool(info_clock_pid_sstate ) = false;
        bool(infi_latch_pid_sstate ) = false;
        bool(info_latch_pid_sstate ) = false;

        int unsigned(mio_clock_ppos_count ) = 0;
        int unsigned(infi_clock_ppos_count ) = 0;
        int unsigned(info_clock_ppos_count ) = 0;

        int unsigned(mio_clock_pneg_count ) = 0;
        int unsigned(infi_clock_pneg_count ) = 0;
        int unsigned(info_clock_pneg_count ) = 0;

        int(mio_clock_pstate ) = digit_pin_low_state;
        int(infi_clock_pstate ) = digit_pin_low_state;
        int(info_clock_pstate ) = digit_pin_low_state;
        int(infi_latch_pstate ) = digit_pin_low_state;
        int(info_latch_pstate ) = digit_pin_low_state;

        int(mio_clock_pmode ) = digit_pin_input_mode;
        int(infi_clock_pmode ) = digit_pin_input_mode;
        int(info_clock_pmode ) = digit_pin_output_mode;
        int(infi_latch_pmode ) = digit_pin_input_mode;
        int(info_latch_pmode ) = digit_pin_output_mode;

        int unsigned(digit_infi_pcount ) = def_digit_i_pin_count;
        int unsigned(digit_info_pcount ) = def_digit_o_pin_count;

        dynamic_array <bool> infi_pid_sstate_list;
        dynamic_array <bool> info_pid_sstate_list;

        dynamic_array <int> infi_pstate_list;
        dynamic_array <int> info_pstate_list;

        dynamic_array <int> infi_pmode_list;
        dynamic_array <int> info_pmode_list;

        dynamic_array <uint8_t> digit_infi_pid_list;
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
        void
        (set_mio_clock_ppos_count(int unsigned(__clock_ppos_count)));
        void
        (set_infi_clock_ppos_count(int unsigned(__clock_ppos_count)));
        void
        (set_info_clock_ppos_count(int unsigned(__clock_ppos_count)));

        int unsigned
        (get_mio_clock_ppos_count());
        int unsigned
        (get_infi_clock_ppos_count());
        int unsigned
        (get_info_clock_ppos_count());

        void
        (set_mio_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_infi_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_info_clock_pneg_count(int unsigned(__clock_pneg_count)));

        int unsigned
        (get_mio_clock_pneg_count());
        int unsigned
        (get_infi_clock_pneg_count());
        int unsigned
        (get_info_clock_pneg_count());

        void
        (set_mio_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_infi_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_info_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_infi_latch_pid (uint8_t(__digit_pid ) ) );
        void
        (set_info_latch_pid (uint8_t(__digit_pid ) ) );

        uint8_t
        (get_mio_clock_pid( ) );
        uint8_t
        (get_infi_clock_pid( ) );
        uint8_t
        (get_info_clock_pid( ) );
        uint8_t
        (get_infi_latch_pid( ) );
        uint8_t
        (get_info_latch_pid( ) );

        void
        (uset_mio_clock_pid( ) );
        void
        (uset_infi_clock_pid( ) );
        void
        (uset_info_clock_pid( ) );
        void
        (uset_infi_latch_pid( ) );
        void
        (uset_info_latch_pid( ) );

        void
        (set_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_infi_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_info_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_infi_latch_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_info_latch_pid_sstate (bool(__pid_sstate ) ) );

        bool
        (get_mio_clock_pid_sstate( ) );
        bool
        (get_infi_clock_pid_sstate( ) );
        bool
        (get_info_clock_pid_sstate( ) );
        bool
        (get_infi_latch_pid_sstate( ) );
        bool
        (get_info_latch_pid_sstate( ) );

        bool
        (is_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_infi_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_info_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_infi_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_info_latch_pid_sstate (bool(__pid_sstate ) ) );

        void
        (update_mio_clock_pstate (int(__mio_clock_pstate ) ) );
        void
        (update_infi_clock_pstate (int(__infi_clock_pstate ) ) );
        void
        (update_info_clock_pstate (int(__info_clock_pstate ) ) );
        void
        (update_infi_latch_pstate (int(__infi_latch_pstate ) ) );
        void
        (update_info_latch_pstate (int(__info_latch_pstate ) ) );

        int
        (get_mio_clock_pstate( ) );
        int
        (get_infi_clock_pstate( ) );
        int
        (get_info_clock_pstate( ) );
        int
        (get_infi_latch_pstate( ) );
        int
        (get_info_latch_pstate( ) );

        int
        (get_mio_clock_pmode( ) );
        int
        (get_infi_clock_pmode( ) );
        int
        (get_info_clock_pmode( ) );
        int
        (get_infi_latch_pmode( ) );
        int
        (get_info_latch_pmode( ) );

        void
        (set_infi_pid(uint8_t(__digit_pid), int unsigned(__infi_pid_pos)));
        void
        (set_info_pid(uint8_t(__digit_pid), int unsigned(__info_pid_pos)));

        uint8_t
        (get_infi_pid(int unsigned(__infi_pid_pos)));
        uint8_t
        (get_info_pid(int unsigned(__info_pid_pos)));

        void
        (uset_infi_pid(int unsigned(__infi_pid_pos)));
        void
        (uset_info_pid(int unsigned(__info_pid_pos)));

        void
        (set_infi_pid_sstate(bool(__pid_sstate ), int unsigned(__infi_pid_pos)));
        void
        (set_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)));

        bool
        (get_infi_pid_sstate(int unsigned(__infi_pid_pos)));
        bool
        (get_info_pid_sstate(int unsigned(__info_pid_pos)));

        bool
        (is_infi_pid_sstate(bool(__pid_sstate ) ,int unsigned(__infi_pid_pos)));
        bool
        (is_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)));

        int unsigned
        (get_infi_pcount( ) )
        {
            return(this-> digit_infi_pcount);
        }
        int unsigned
        (get_info_pcount( ) )
        {
            return(this-> digit_info_pcount);
        }
} ; }

# endif /*__pin__manager__hpp__*/
