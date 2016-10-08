# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
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
        dynamic_array <uint8_t> (digit_mio_clock_pid );
        dynamic_array <uint8_t> (digit_dati_clock_pid );
        dynamic_array <uint8_t> (digit_dato_clock_pid );
        dynamic_array <uint8_t> (digit_dati_latch_pid );
        dynamic_array <uint8_t> (digit_dato_latch_pid );

        dynamic_array <bool> (mio_clock_pid_sstate );
        dynamic_array <bool> (dati_clock_pid_sstate );
        dynamic_array <bool> (dato_clock_pid_sstate );
        dynamic_array <bool> (dati_latch_pid_sstate );
        dynamic_array <bool> (dato_latch_pid_sstate );


        dynamic_array <int unsigned> mio_clock_ppos_count;
        dynamic_array <int unsigned> dati_clock_ppos_count;
        dynamic_array <int unsigned> dato_clock_ppos_count;

        dynamic_array <int unsigned> mio_clock_pneg_count;
        dynamic_array <int unsigned> dati_clock_pneg_count;
        dynamic_array <int unsigned> dato_clock_pneg_count;


        dynamic_array <int> (mio_clock_pstate );
        dynamic_array <int> (dati_clock_pstate );
        dynamic_array <int> (dato_clock_pstate );
        dynamic_array <int> (dati_latch_pstate );
        dynamic_array <int> (dato_latch_pstate );

        dynamic_array <int> (mio_clock_pmode );
        dynamic_array <int> (dati_clock_pmode );
        dynamic_array <int> (dato_clock_pmode );
        dynamic_array <int> (dati_latch_pmode );
        dynamic_array <int> (dato_latch_pmode );

        dynamic_array <int unsigned> (digit_dati_pcount );// = tmp_config::def_digit_dati_pcount;
        dynamic_array <int unsigned> (digit_dato_pcount );// = tmp_config::def_digit_dato_pcount;

        dynamic_array <bool> dati_pid_sstate_list;
        dynamic_array <bool> dato_pid_sstate_list;

        dynamic_array <int> dati_pstate_list;
        dynamic_array <int> dato_pstate_list;

        dynamic_array <int> dati_pmode_list;
        dynamic_array <int> dato_pmode_list;

        dynamic_array <uint8_t> digit_dati_pid_list;
        dynamic_array <uint8_t> digit_dato_pid_list;
    public :
        pin_manager (int unsigned(__interface_count));
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
        (set_mio_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id )));
        void
        (set_dati_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id )));
        void
        (set_dato_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id )));

        int unsigned
        (get_mio_clock_ppos_count(int unsigned(__interface_id )));
        int unsigned
        (get_dati_clock_ppos_count(int unsigned(__interface_id )));
        int unsigned
        (get_dato_clock_ppos_count(int unsigned(__interface_id )));

        void
        (set_mio_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id )));
        void
        (set_dati_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id )));
        void
        (set_dato_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id )));

        int unsigned
        (get_mio_clock_pneg_count(int unsigned(__interface_id )));
        int unsigned
        (get_dati_clock_pneg_count(int unsigned(__interface_id )));
        int unsigned
        (get_dato_clock_pneg_count(int unsigned(__interface_id )));

        void
        (set_mio_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id ) ) );
        void
        (set_dati_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id ) ) );
        void
        (set_dato_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id ) ) );
        void
        (set_dati_latch_pid (uint8_t(__digit_pid ), int unsigned(__interface_id ) ) );
        void
        (set_dato_latch_pid (uint8_t(__digit_pid ), int unsigned(__interface_id ) ) );

        uint8_t
        (get_mio_clock_pid(int unsigned(__interface_id ) ) );
        uint8_t
        (get_dati_clock_pid(int unsigned(__interface_id ) ) );
        uint8_t
        (get_dato_clock_pid(int unsigned(__interface_id ) ) );
        uint8_t
        (get_dati_latch_pid(int unsigned(__interface_id ) ) );
        uint8_t
        (get_dato_latch_pid(int unsigned(__interface_id ) ) );

        void
        (uset_mio_clock_pid(int unsigned(__interface_id ) ) );
        void
        (uset_dati_clock_pid(int unsigned(__interface_id ) ) );
        void
        (uset_dato_clock_pid(int unsigned(__interface_id ) ) );
        void
        (uset_dati_latch_pid(int unsigned(__interface_id ) ) );
        void
        (uset_dato_latch_pid(int unsigned(__interface_id ) ) );

        void
        (set_mio_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        void
        (set_dati_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        void
        (set_dato_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        void
        (set_dati_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        void
        (set_dato_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );

        bool
        (get_mio_clock_pid_sstate(int unsigned(__interface_id ) ) );
        bool
        (get_dati_clock_pid_sstate(int unsigned(__interface_id ) ) );
        bool
        (get_dato_clock_pid_sstate(int unsigned(__interface_id ) ) );
        bool
        (get_dati_latch_pid_sstate(int unsigned(__interface_id ) ) );
        bool
        (get_dato_latch_pid_sstate(int unsigned(__interface_id ) ) );

        bool
        (is_mio_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        bool
        (is_dati_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        bool
        (is_dato_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        bool
        (is_dati_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );
        bool
        (is_dato_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) );

        void
        (update_mio_clock_pstate (int(__mio_clock_pstate ), int unsigned(__interface_id ) ) );
        void
        (update_dati_clock_pstate (int(__dati_clock_pstate ), int unsigned(__interface_id ) ) );
        void
        (update_dato_clock_pstate (int(__dato_clock_pstate ), int unsigned(__interface_id ) ) );
        void
        (update_dati_latch_pstate (int(__dati_latch_pstate ), int unsigned(__interface_id ) ) );
        void
        (update_dato_latch_pstate (int(__dato_latch_pstate ), int unsigned(__interface_id ) ) );

        int
        (get_mio_clock_pstate(int unsigned(__interface_id ) ) );
        int
        (get_dati_clock_pstate(int unsigned(__interface_id ) ) );
        int
        (get_dato_clock_pstate(int unsigned(__interface_id ) ) );
        int
        (get_dati_latch_pstate(int unsigned(__interface_id ) ) );
        int
        (get_dato_latch_pstate(int unsigned(__interface_id ) ) );

        int
        (get_mio_clock_pmode(int unsigned(__interface_id ) ) );
        int
        (get_dati_clock_pmode(int unsigned(__interface_id ) ) );
        int
        (get_dato_clock_pmode(int unsigned(__interface_id ) ) );
        int
        (get_dati_latch_pmode(int unsigned(__interface_id ) ) );
        int
        (get_dato_latch_pmode(int unsigned(__interface_id ) ) );

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
        (get_dati_pcount (int unsigned(__interface_id) ) )
        {
            return(* (this-> digit_dati_pcount).get_darr_ilayer(__interface_id, 0));
        }
        int unsigned
        (get_dato_pcount (int unsigned(__interface_id) ) )
        {
            return(* (this-> digit_dato_pcount).get_darr_ilayer(__interface_id, 0));
        }
} ; }

# endif /*__pin__manager__hpp__*/
