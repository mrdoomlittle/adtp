# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

# include "dtmp_config.hpp"
# include "dynamic_array.hpp"

# ifndef ARDUINO
    # include <boost/cstdint.hpp>
# else
    # include <stdint.h>
# endif

namespace dtmp { class pin_manager
{
    private :
        uint8_t(digit_mio_clock_pid ) = def_digit_mio_clock_pid;
        uint8_t(digit_dtai_clock_pid ) = def_digit_dtai_clock_pid;
        uint8_t(digit_dtao_clock_pid ) = def_digit_dtao_clock_pid;
        uint8_t(digit_dtai_latch_pid ) = def_digit_dtai_latch_pid;
        uint8_t(digit_dtao_latch_pid ) = def_digit_dtao_latch_pid;

        bool(mio_clock_pid_sstate ) = false;
        bool(dtai_clock_pid_sstate ) = false;
        bool(dtao_clock_pid_sstate ) = false;
        bool(dtai_latch_pid_sstate ) = false;
        bool(dtao_latch_pid_sstate ) = false;

        int unsigned(mio_clock_ppos_count ) = 0;
        int unsigned(dtai_clock_ppos_count ) = 0;
        int unsigned(dtao_clock_ppos_count ) = 0;

        int unsigned(mio_clock_pneg_count ) = 0;
        int unsigned(dtai_clock_pneg_count ) = 0;
        int unsigned(dtao_clock_pneg_count ) = 0;

        int(mio_clock_pstate ) = digit_pin_low_state;
        int(dtai_clock_pstate ) = digit_pin_low_state;
        int(dtao_clock_pstate ) = digit_pin_low_state;
        int(dtai_latch_pstate ) = digit_pin_low_state;
        int(dtao_latch_pstate ) = digit_pin_low_state;

        int(mio_clock_pmode ) = digit_pin_input_mode;
        int(dtai_clock_pmode ) = digit_pin_input_mode;
        int(dtao_clock_pmode ) = digit_pin_output_mode;
        int(dtai_latch_pmode ) = digit_pin_input_mode;
        int(dtao_latch_pmode ) = digit_pin_output_mode;

        int unsigned(digit_dtai_pcount ) = def_digit_i_pin_count;
        int unsigned(digit_dtao_pcount ) = def_digit_o_pin_count;

        dynamic_array <bool> dtai_pid_sstate_list;
        dynamic_array <bool> dtao_pid_sstate_list;

        dynamic_array <int> dtai_pstate_list;
        dynamic_array <int> dtao_pstate_list;

        dynamic_array <int> dtai_pmode_list;
        dynamic_array <int> dtao_pmode_list;

        dynamic_array <uint8_t> digit_dtai_pid_list;
        dynamic_array <uint8_t> digit_dtao_pid_list;
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
        (set_dtai_clock_ppos_count(int unsigned(__clock_ppos_count)));
        void
        (set_dtao_clock_ppos_count(int unsigned(__clock_ppos_count)));

        int unsigned
        (get_mio_clock_ppos_count());
        int unsigned
        (get_dtai_clock_ppos_count());
        int unsigned
        (get_dtao_clock_ppos_count());

        void
        (set_mio_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_dtai_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_dtao_clock_pneg_count(int unsigned(__clock_pneg_count)));

        int unsigned
        (get_mio_clock_pneg_count());
        int unsigned
        (get_dtai_clock_pneg_count());
        int unsigned
        (get_dtao_clock_pneg_count());

        void
        (set_mio_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dtai_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dtao_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dtai_latch_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dtao_latch_pid (uint8_t(__digit_pid ) ) );

        uint8_t
        (get_mio_clock_pid( ) );
        uint8_t
        (get_dtai_clock_pid( ) );
        uint8_t
        (get_dtao_clock_pid( ) );
        uint8_t
        (get_dtai_latch_pid( ) );
        uint8_t
        (get_dtao_latch_pid( ) );

        void
        (uset_mio_clock_pid( ) );
        void
        (uset_dtai_clock_pid( ) );
        void
        (uset_dtao_clock_pid( ) );
        void
        (uset_dtai_latch_pid( ) );
        void
        (uset_dtao_latch_pid( ) );

        void
        (set_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dtai_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dtao_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dtai_latch_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dtao_latch_pid_sstate (bool(__pid_sstate ) ) );

        bool
        (get_mio_clock_pid_sstate( ) );
        bool
        (get_dtai_clock_pid_sstate( ) );
        bool
        (get_dtao_clock_pid_sstate( ) );
        bool
        (get_dtai_latch_pid_sstate( ) );
        bool
        (get_dtao_latch_pid_sstate( ) );

        bool
        (is_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dtai_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dtao_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dtai_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dtao_latch_pid_sstate (bool(__pid_sstate ) ) );

        void
        (update_mio_clock_pstate (int(__mio_clock_pstate ) ) );
        void
        (update_dtai_clock_pstate (int(__dtai_clock_pstate ) ) );
        void
        (update_dtao_clock_pstate (int(__dtao_clock_pstate ) ) );
        void
        (update_dtai_latch_pstate (int(__dtai_latch_pstate ) ) );
        void
        (update_dtao_latch_pstate (int(__dtao_latch_pstate ) ) );

        int
        (get_mio_clock_pstate( ) );
        int
        (get_dtai_clock_pstate( ) );
        int
        (get_dtao_clock_pstate( ) );
        int
        (get_dtai_latch_pstate( ) );
        int
        (get_dtao_latch_pstate( ) );

        int
        (get_mio_clock_pmode( ) );
        int
        (get_dtai_clock_pmode( ) );
        int
        (get_dtao_clock_pmode( ) );
        int
        (get_dtai_latch_pmode( ) );
        int
        (get_dtao_latch_pmode( ) );

        void
        (set_dtai_pid(uint8_t(__digit_pid), int unsigned(__dtai_pid_pos)));
        void
        (set_dtao_pid(uint8_t(__digit_pid), int unsigned(__dtao_pid_pos)));

        uint8_t
        (get_dtai_pid(int unsigned(__dtai_pid_pos)));
        uint8_t
        (get_dtao_pid(int unsigned(__dtao_pid_pos)));

        void
        (uset_dtai_pid(int unsigned(__dtai_pid_pos)));
        void
        (uset_dtao_pid(int unsigned(__dtao_pid_pos)));

        void
        (set_dtai_pid_sstate(bool(__pid_sstate ), int unsigned(__dtai_pid_pos)));
        void
        (set_dtao_pid_sstate(bool(__pid_sstate ), int unsigned(__dtao_pid_pos)));

        bool
        (get_dtai_pid_sstate(int unsigned(__dtai_pid_pos)));
        bool
        (get_dtao_pid_sstate(int unsigned(__dtao_pid_pos)));

        bool
        (is_dtai_pid_sstate(bool(__pid_sstate ) ,int unsigned(__dtai_pid_pos)));
        bool
        (is_dtao_pid_sstate(bool(__pid_sstate ), int unsigned(__dtao_pid_pos)));

        int unsigned
        (get_dtai_pcount( ) )
        {
            return(this-> digit_dtai_pcount);
        }
        int unsigned
        (get_dtao_pcount( ) )
        {
            return(this-> digit_dtao_pcount);
        }
} ; }

# endif /*__pin__manager__hpp__*/
