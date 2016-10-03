# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

# include "tmp_config.hpp"
# include "dynamic_array.hpp"

# ifndef ARDUINO
    # include <boost/cstdint.hpp>
# else
    # include <stdint.h>
# endif

namespace tmp { class pin_manager
{
    private :
        uint8_t(digit_mio_clock_pid ) = tmp_config::def_digit_mio_clock_pid;
        uint8_t(digit_dati_clock_pid ) = tmp_config::def_digit_dati_clock_pid;
        uint8_t(digit_dato_clock_pid ) = tmp_config::def_digit_dato_clock_pid;
        uint8_t(digit_dati_latch_pid ) = tmp_config::def_digit_dati_latch_pid;
        uint8_t(digit_dato_latch_pid ) = tmp_config::def_digit_dato_latch_pid;

        bool(mio_clock_pid_sstate ) = false;
        bool(dati_clock_pid_sstate ) = false;
        bool(dato_clock_pid_sstate ) = false;
        bool(dati_latch_pid_sstate ) = false;
        bool(dato_latch_pid_sstate ) = false;

        int unsigned(mio_clock_ppos_count ) = 0;
        int unsigned(dati_clock_ppos_count ) = 0;
        int unsigned(dato_clock_ppos_count ) = 0;

        int unsigned(mio_clock_pneg_count ) = 0;
        int unsigned(dati_clock_pneg_count ) = 0;
        int unsigned(dato_clock_pneg_count ) = 0;

        int(mio_clock_pstate ) = tmp_config::digit_pin_low_state;
        int(dati_clock_pstate ) = tmp_config::digit_pin_low_state;
        int(dato_clock_pstate ) = tmp_config::digit_pin_low_state;
        int(dati_latch_pstate ) = tmp_config::digit_pin_low_state;
        int(dato_latch_pstate ) = tmp_config::digit_pin_low_state;

        int(mio_clock_pmode ) = tmp_config::digit_pin_input_mode;
        int(dati_clock_pmode ) = tmp_config::digit_pin_input_mode;
        int(dato_clock_pmode ) = tmp_config::digit_pin_output_mode;
        int(dati_latch_pmode ) = tmp_config::digit_pin_input_mode;
        int(dato_latch_pmode ) = tmp_config::digit_pin_output_mode;

        int unsigned(digit_dati_pcount ) = tmp_config::def_digit_i_pin_count;
        int unsigned(digit_dato_pcount ) = tmp_config::def_digit_o_pin_count;

        dynamic_array <bool> dati_pid_sstate_list;
        dynamic_array <bool> dato_pid_sstate_list;

        dynamic_array <int> dati_pstate_list;
        dynamic_array <int> dato_pstate_list;

        dynamic_array <int> dati_pmode_list;
        dynamic_array <int> dato_pmode_list;

        dynamic_array <uint8_t> digit_dati_pid_list;
        dynamic_array <uint8_t> digit_dato_pid_list;
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
        (set_dati_clock_ppos_count(int unsigned(__clock_ppos_count)));
        void
        (set_dato_clock_ppos_count(int unsigned(__clock_ppos_count)));

        int unsigned
        (get_mio_clock_ppos_count());
        int unsigned
        (get_dati_clock_ppos_count());
        int unsigned
        (get_dato_clock_ppos_count());

        void
        (set_mio_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_dati_clock_pneg_count(int unsigned(__clock_pneg_count)));
        void
        (set_dato_clock_pneg_count(int unsigned(__clock_pneg_count)));

        int unsigned
        (get_mio_clock_pneg_count());
        int unsigned
        (get_dati_clock_pneg_count());
        int unsigned
        (get_dato_clock_pneg_count());

        void
        (set_mio_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dati_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dato_clock_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dati_latch_pid (uint8_t(__digit_pid ) ) );
        void
        (set_dato_latch_pid (uint8_t(__digit_pid ) ) );

        uint8_t
        (get_mio_clock_pid( ) );
        uint8_t
        (get_dati_clock_pid( ) );
        uint8_t
        (get_dato_clock_pid( ) );
        uint8_t
        (get_dati_latch_pid( ) );
        uint8_t
        (get_dato_latch_pid( ) );

        void
        (uset_mio_clock_pid( ) );
        void
        (uset_dati_clock_pid( ) );
        void
        (uset_dato_clock_pid( ) );
        void
        (uset_dati_latch_pid( ) );
        void
        (uset_dato_latch_pid( ) );

        void
        (set_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dati_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dato_clock_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dati_latch_pid_sstate (bool(__pid_sstate ) ) );
        void
        (set_dato_latch_pid_sstate (bool(__pid_sstate ) ) );

        bool
        (get_mio_clock_pid_sstate( ) );
        bool
        (get_dati_clock_pid_sstate( ) );
        bool
        (get_dato_clock_pid_sstate( ) );
        bool
        (get_dati_latch_pid_sstate( ) );
        bool
        (get_dato_latch_pid_sstate( ) );

        bool
        (is_mio_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dati_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dato_clock_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dati_latch_pid_sstate (bool(__pid_sstate ) ) );
        bool
        (is_dato_latch_pid_sstate (bool(__pid_sstate ) ) );

        void
        (update_mio_clock_pstate (int(__mio_clock_pstate ) ) );
        void
        (update_dati_clock_pstate (int(__dati_clock_pstate ) ) );
        void
        (update_dato_clock_pstate (int(__dato_clock_pstate ) ) );
        void
        (update_dati_latch_pstate (int(__dati_latch_pstate ) ) );
        void
        (update_dato_latch_pstate (int(__dato_latch_pstate ) ) );

        int
        (get_mio_clock_pstate( ) );
        int
        (get_dati_clock_pstate( ) );
        int
        (get_dato_clock_pstate( ) );
        int
        (get_dati_latch_pstate( ) );
        int
        (get_dato_latch_pstate( ) );

        int
        (get_mio_clock_pmode( ) );
        int
        (get_dati_clock_pmode( ) );
        int
        (get_dato_clock_pmode( ) );
        int
        (get_dati_latch_pmode( ) );
        int
        (get_dato_latch_pmode( ) );

        void
        (set_dati_pid(uint8_t(__digit_pid), int unsigned(__dati_pid_pos)));
        void
        (set_dato_pid(uint8_t(__digit_pid), int unsigned(__dato_pid_pos)));

        uint8_t
        (get_dati_pid(int unsigned(__dati_pid_pos)));
        uint8_t
        (get_dato_pid(int unsigned(__dato_pid_pos)));

        void
        (uset_dati_pid(int unsigned(__dati_pid_pos)));
        void
        (uset_dato_pid(int unsigned(__dato_pid_pos)));

        void
        (set_dati_pid_sstate(bool(__pid_sstate ), int unsigned(__dati_pid_pos)));
        void
        (set_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos)));

        bool
        (get_dati_pid_sstate(int unsigned(__dati_pid_pos)));
        bool
        (get_dato_pid_sstate(int unsigned(__dato_pid_pos)));

        bool
        (is_dati_pid_sstate(bool(__pid_sstate ) ,int unsigned(__dati_pid_pos)));
        bool
        (is_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos)));

        int unsigned
        (get_dati_pcount( ) )
        {
            return(this-> digit_dati_pcount);
        }
        int unsigned
        (get_dato_pcount( ) )
        {
            return(this-> digit_dato_pcount);
        }
} ; }

# endif /*__pin__manager__hpp__*/
