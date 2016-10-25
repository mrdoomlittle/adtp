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
        int unsigned(digit_dati_pcount ) =
            (tmp_config::def_digit_dati_pcount);

        int unsigned(digit_dato_pcount ) =
            (tmp_config::def_digit_dato_pcount);

        int unsigned(clock_sstate_ignore ) = 0x0;

        dynamic_array <int unsigned> (dati_bitset_length);
        dynamic_array <int unsigned> (dato_bitset_length);

        int unsigned(dati_byte_read_holdup ) = 0;
        int unsigned(dato_byte_write_holdup ) = 0;

        int unsigned(dati_bit_read_holdup ) = 0;
        int unsigned(dato_bit_write_holdup ) = 0;
    public :
        int unsigned(dati_bitset_buff_size ) = 12;
        int unsigned(dato_bitset_buff_size ) = 12;
    protected :
        typedef void( (set_digit_pmode_func_t ) (uint8_t, uint8_t) );
        set_digit_pmode_func_t
            (* set_digit_pmode_func_ptr ) = nullptr;

        typedef void( (set_digit_pstate_func_t) (uint8_t, uint8_t) );
        set_digit_pstate_func_t
            (* set_digit_pstate_func_ptr ) = nullptr;

        typedef int( (get_digit_pstate_func_t ) (uint8_t) );
        get_digit_pstate_func_t
            (* get_digit_pstate_func_ptr ) = nullptr;

        typedef int unsigned long( (get_high_rclock_func_t) (int unsigned) );
        get_high_rclock_func_t
            (* get_high_rclock_func_ptr ) = nullptr;

        // NOTE change to bool or uint8_t as int unsigned takes up 4 bytes and
        // we dont need that as we are only reading a 0 or 1
        typedef int unsigned( (extern_mlinit_func_t ) (io_service *) );
        extern_mlinit_func_t
            (* extern_mlinit_func_ptr ) = nullptr;

        typedef int unsigned( (extern_mltick_func_t ) (io_service *) );
        extern_mltick_func_t
            (* extern_mltick_func_ptr ) = nullptr;
    public :
        io_service( );
        ~io_service( );

        void
        (service_init (
            set_digit_pmode_func_t(* __set_digit_pmode_func_ptr) = nullptr,
            set_digit_pstate_func_t(* __set_digit_pstate_func_ptr) = nullptr,
            get_digit_pstate_func_t(* __get_digit_pstate_func_ptr) = nullptr,
            get_high_rclock_func_t(* __get_high_rclock_func_ptr ) = nullptr,
            extern_mlinit_func_t(* __extern_mlinit_func_ptr) = nullptr,
            extern_mltick_func_t(* __extern_mltick_func_ptr) = nullptr
        ) );

        void
        (set_ptr_to_sdigit_pmode_func (set_digit_pmode_func_t(* __set_digit_pmode_func_ptr) ) );
        void
        (set_ptr_to_sdigit_pstate_func (set_digit_pstate_func_t(* __set_digit_pstate_func_ptr) ) );
        void
        (set_ptr_to_gdigit_pstate_func (get_digit_pstate_func_t(* __get_digit_pstate_func_ptr) ) );
        void
        (set_ptr_to_ghigh_rclock_func (get_high_rclock_func_t(* __get_high_rclock_func_ptr) ) );
        void
        (set_ptr_to_extern_mlinit_func (extern_mlinit_func_t(* __extern_mlinit_func_ptr) ) );
        void
        (set_ptr_to_extern_mltick_func (extern_mltick_func_t(* __extern_mltick_func_ptr) ) );

        bool
        (is_ptr_to_sdigit_pmode_func (set_digit_pmode_func_t(* __is_type) ) );
        bool
        (is_ptr_to_sdigit_pstate_func (set_digit_pstate_func_t(* __is_type) ) );
        bool
        (is_ptr_to_gdigit_pstate_func (get_digit_pstate_func_t(* __is_type) ) );
        bool
        (is_ptr_to_ghigh_rclock_func (get_high_rclock_func_t(* __is_type) ) );
        bool
        (is_ptr_to_extern_mlinit_func (extern_mlinit_func_t(* __is_type) ) );
        bool
        (is_ptr_to_extern_mltick_func (extern_mltick_func_t(* __is_type) ) );

    private :
        int unsigned(mltrigger_holdup) =
            tmp_config::def_mltrigger_holdup;

        int unsigned(iltrigger_holdup) =
            tmp_config::def_iltrigger_holdup;

        int unsigned(real_mltrigger_count) = 0;
        int unsigned(real_iltrigger_count) = 0;
        int unsigned(tmp_iltrigger_count) = 0;

        int unsigned(dati_iltrigger_count) = 0;
        int unsigned(dato_iltrigger_count) = 0;

        void
        (update_rmltrigger_count (int unsigned(__update_amount ) ) );
        void
        (update_riltrigger_count (int unsigned(__update_amount ) ) );

        void
        (reset_riltrigger_count())
        {
            (this-> real_iltrigger_count ) = 0;
        }

        void
        (update_dat_iltrigger_count (int unsigned(__update_amount ), std::uint8_t(__type) ) )
        {
            switch(__type)
            {
                case(tmp_config::io_t::__itype):
                    (this-> dati_iltrigger_count) += __update_amount;
                break;
                case(tmp_config::io_t::__otype):
                    (this-> dato_iltrigger_count) += __update_amount;
                break;
            }
        }

        bool(ilclockp_toggled) = false;
        int unsigned(ilclockp_tcount) = 0;

        bool(ilclockn_toggled) = false;
        int unsigned(ilclockn_tcount) = 0;

    public :
    // NOTE: might change to struct or keep as enum/ and it move to tmp_config
        enum sg_type : int unsigned { __individual = 0, __total_array = 1 } ;
        enum shift_direction : int unsigned { __right = 0, __left = 1 } ;

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
        bitset_list <__bitset_type> (* digit_datio_bitset) = new bitset_list <__bitset_type> [2];

        void
        (set_dati_bitset (array <uint8_t> (* __dati_bitset)));
        void
        (set_dato_bitset (array <uint8_t> (* __dato_bitset)));

        array <uint8_t>
        (* get_dati_bitset ());
        array <uint8_t>
        (* get_dato_bitset ());

    public :
        array <uint8_t>
        (* digit_dati_bitset ) = new array <uint8_t> (8, {}, false);
        array <uint8_t>
        (* digit_dato_bitset ) = new array <uint8_t> (8, {}, false);
    private:
        array <bool>
        (* dati_bitset_finished ) = new array <bool> ((8 / digit_dati_pcount), {}, false);
        array <bool>
        (* dato_bitset_finished ) = new array <bool> ((8 / digit_dato_pcount), {}, false);

        int unsigned(dati_bitset_fcount ) = 0;
        int unsigned(dato_bitset_fcount ) = 0;
    public :
        dynamic_buffer <uint8_t> (dati_bitset_buff);
        dynamic_buffer <uint8_t> (dato_bitset_buff);

        int unsigned(dati_bitset_buff_pos[2] ) = {0, 0};
        int unsigned(dato_bitset_buff_pos[2] ) = {0, 0};
    private :
        int unsigned(digit_dati_buff_pos ) = 0;
        int unsigned(digit_dato_buff_pos ) = 0;

        int unsigned(ibp_pcount_multiplier ) = 0;
        int unsigned(obp_pcount_multiplier ) = 0;

        int unsigned(dati_bitsetf_truec ) = 0;
        int unsigned(dato_bitsetf_truec ) = 0;

        int unsigned(dati_clock_ltcount ) = 0;
        bool(is_dati_clock_ppos) = false;

    public :
        int unsigned(dati_bytestream_bsize) = 17;
        int unsigned(dato_bytestream_bsize) = 17;

        void
        (add_to_dati_bytestream(uint8_t(__iface_id), bitset <uint8_t> (* __bitset_to_add)))
        {
            if ((this-> dati_bytestream_buff).is_block_smarker(true, __iface_id, dati_bytestream_bpos[0]))
            {
                if ((this-> dati_bstream_buff_offunc_ptr) != nullptr)
                    (this-> dati_bstream_buff_overflow(__iface_id, __bitset_to_add));
                return;
            }

            for (int unsigned(x ) = 0; x != (__bitset_to_add-> get_bitset_length()); x ++)
                (this-> dati_bytestream_buff).add_to_dbuff((__bitset_to_add-> get_bitset(0, x)), 2, __iface_id, (this-> dati_bytestream_bpos[0]), x, false, false, false);

            if ((this-> dati_bytestream_bpos[0]) == (this-> dati_bytestream_bsize - 1))
                (this-> dati_bytestream_bpos[0]) = 0;
            else
                (this-> dati_bytestream_bpos[0])++;
        }

        bitset <uint8_t>
        (get_from_dati_bytestream(uint8_t(__iface_id)))
        {
            bitset <uint8_t> __bitset;

            __bitset.bitset_init(8);

            uint8_t o = 0;
            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset(&o, 0, x);

            if ((this-> dati_bytestream_buff).is_block_smarker(false, __iface_id, (this-> dati_bytestream_bpos[1]))) return __bitset;

            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset((this-> dati_bytestream_buff).get_from_dbuff(2, __iface_id, (this-> dati_bytestream_bpos[1]), x, false, false, false, true), 0, x);

            (this-> dati_bytestream_buff).del_from_dbuffer(1, 0, (this-> dati_bytestream_bpos[1]), 0);

            if ((this-> dati_bytestream_bpos[1]) == (this-> dati_bytestream_bsize - 1))
                (this-> dati_bytestream_bpos[1]) = 0;
            else
                (this-> dati_bytestream_bpos[1]) ++;

            return (__bitset);
        }

        void
        (add_to_dato_bytestream(uint8_t(__iface_id), bitset <uint8_t> (* __bitset_to_add)))
        {
            if ((this-> dato_bytestream_buff).is_block_smarker(true, __iface_id, dato_bytestream_bpos[0]))
            {
                if ((this-> dato_bstream_buff_offunc_ptr) != nullptr)
                    (this-> dato_bstream_buff_overflow(__iface_id, __bitset_to_add));
                return;
            }

            for (int unsigned(x ) = 0; x != (__bitset_to_add-> get_bitset_length()); x ++)
                (this-> dato_bytestream_buff).add_to_dbuff((__bitset_to_add-> get_bitset(0, x)), 2, __iface_id, (this-> dato_bytestream_bpos[0]), x, false, false, false);

            if ((this-> dato_bytestream_bpos[0]) == (this-> dato_bytestream_bsize - 1))
                (this-> dato_bytestream_bpos[0]) = 0;
            else
                (this-> dato_bytestream_bpos[0])++;
        }

        bitset <uint8_t>
        (get_from_dato_bytestream(uint8_t(__iface_id)))
        {
            bitset <uint8_t> __bitset;

            __bitset.bitset_init(8);

            uint8_t o = 0;
            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset(&o, 0, x);

            if ((this-> dato_bytestream_buff).is_block_smarker(false, __iface_id, (this-> dato_bytestream_bpos[1]))) return __bitset;

            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset((this-> dato_bytestream_buff).get_from_dbuff(2, __iface_id, (this-> dato_bytestream_bpos[1]), x, false, false, false, true), 0, x);

            (this-> dato_bytestream_buff).del_from_dbuffer(1, 0, (this-> dato_bytestream_bpos[1]), 0);

            if ((this-> dato_bytestream_bpos[1]) == (this-> dato_bytestream_bsize - 1))
                (this-> dato_bytestream_bpos[1]) = 0;
            else
                (this-> dato_bytestream_bpos[1]) ++;

            return (__bitset);
        }

        void
        (add_to_dati_bitset_buff(uint8_t(__iface_id), bitset <uint8_t> (* __bitset)))
        {
            if ((this-> dati_bitset_buff).is_block_smarker(true, __iface_id, dati_bitset_buff_pos[0])) return;

            for (int unsigned(x ) = 0; x != __bitset-> get_bitset_length(); x ++)
                (this-> dati_bitset_buff).add_to_dbuff((__bitset-> get_bitset(0, x)), 2, __iface_id, (this-> dati_bitset_buff_pos[0]), x, false, false, false);

            if ((this-> dati_bitset_buff_pos[0]) == (this-> dati_bitset_buff_size - 1))
                (this-> dati_bitset_buff_pos[0]) = 0;
            else
                (this-> dati_bitset_buff_pos[0])++;
        }

        bitset <uint8_t>
        (get_from_dati_bitset_buff(uint8_t(__iface_id)))
        {
            static bitset <std::uint8_t> __bitset;

            __bitset.bitset_init(8);

            uint8_t o = 0;
            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset(&o, 0, x);

            if ((this-> dati_bitset_buff).is_block_smarker(false, __iface_id, (this-> dati_bitset_buff_pos[1] ))) return __bitset;

            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset((this-> dati_bitset_buff).get_from_dbuff(2, __iface_id, (this-> dati_bitset_buff_pos[1]), x, false, false, false, true), 0, x);

            (this-> dati_bitset_buff).del_from_dbuffer(1, 0, (this-> dati_bitset_buff_pos[1]), 0);

            if ( (this-> dati_bitset_buff_pos[1] ) == (this-> dati_bitset_buff_size - 1))
                (this-> dati_bitset_buff_pos[1] ) = 0;
            else
                (this-> dati_bitset_buff_pos[1] ) ++;

            return __bitset;
        }

        void
        (add_to_dato_bitset_buff(uint8_t(__iface_id), bitset <uint8_t> (* __bitset)))
        {
            if ((this-> dato_bitset_buff).is_block_smarker(true, __iface_id, dato_bitset_buff_pos[0])) return;

            for (int unsigned(x ) = 0; x != __bitset-> get_bitset_length(); x ++)
                (this-> dato_bitset_buff).add_to_dbuff((__bitset-> get_bitset(0, x)), 2, __iface_id, (this-> dato_bitset_buff_pos[0]), x, false, false, false);

            if ((this-> dato_bitset_buff_pos[0]) == (this-> dato_bitset_buff_size - 1))
                (this-> dato_bitset_buff_pos[0]) = 0;
            else
                (this-> dato_bitset_buff_pos[0])++;
        }

        bitset <uint8_t>
        (get_from_dato_bitset_buff(uint8_t(__iface_id)))
        {
            static bitset <std::uint8_t> __bitset;

            __bitset.bitset_init(8);

            uint8_t o = 0;
            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset(&o, 0, x);

            if ((this-> dato_bitset_buff).is_block_smarker(false, __iface_id, (this-> dato_bitset_buff_pos[1] ))) return __bitset;

            for (int unsigned x = 0; x != __bitset.get_bitset_length(); x ++)
                __bitset.set_bitset((this-> dato_bitset_buff).get_from_dbuff(2, __iface_id, (this-> dato_bitset_buff_pos[1]), x, false, false, false, true), 0, x);

            (this-> dato_bitset_buff).del_from_dbuffer(1, 0, (this-> dato_bitset_buff_pos[1]), 0);

            if ( (this-> dato_bitset_buff_pos[1] ) == (this-> dato_bitset_buff_size - 1))
                (this-> dato_bitset_buff_pos[1] ) = 0;
            else
                (this-> dato_bitset_buff_pos[1] ) ++;

            return __bitset;
        }

        /*
        if ((this-> dato_bitset_buff).is_block_smarker(true, __iface_id, (this-> dato_bitset_buff_pos[0] ))) return;

        for (int unsigned x = 0; x != 8; x ++)
            ((*(this-> digit_dato_bitset)) [x]) = *(this-> dato_bitset_buff).get_from_dbuff(2, __iface_id, (this-> dato_bitset_buff_pos[0] ), x, false, false, false, true);

        if ( (this-> dato_bitset_buff_pos[0] ) == (this-> dato_bitset_buff_size ) - 1)
            (this-> dato_bitset_buff_pos[0] ) = 0;
        else
            (this-> dato_bitset_buff_pos[0] ) ++;
        */

        void
        (set_dati_bstream_buff_offunc_ptr(void(* __overflow)(int unsigned iface, bitset <uint8_t> (* __bitset))))
        {
            (this-> dati_bstream_buff_offunc_ptr) = __overflow;
        }

        void
        (set_dato_bstream_buff_offunc_ptr(void(* __overflow)(int unsigned iface, bitset <uint8_t> (* __bitset))))
        {
            (this-> dato_bstream_buff_offunc_ptr) = __overflow;
        }

        void
        (dati_bstream_buff_overflow(int unsigned(iface_id), tmp::bitset <uint8_t> (* __bitset)))
        {
            (this-> dati_bstream_buff_offunc_ptr(iface_id, __bitset));
        }

        void
        (dato_bstream_buff_overflow(int unsigned(iface_id), tmp::bitset <uint8_t> (* __bitset)))
        {
            (this-> dato_bstream_buff_offunc_ptr(iface_id, __bitset));
        }

        void(* dati_bstream_buff_offunc_ptr)(int unsigned, bitset <uint8_t> *) = nullptr;

        void(* dato_bstream_buff_offunc_ptr)(int unsigned, bitset <uint8_t> *) = nullptr;

        // NOTE add under flow
        bool
        (is_dati_bstream_buff_full())
        {
            return(this-> dati_bytestream_buff.get_sector_free_c(0) == 0? true : false);
        }

        bool
        (is_dato_bstream_buff_full())
        {
            return(this-> dato_bytestream_buff.get_sector_free_c(0) == 0? true : false);
        }

        array <int unsigned> dati_bytestream_bpos =
            array <int unsigned>(2, {0, 0}, true);
        array <int unsigned> dato_bytestream_bpos =
            array <int unsigned>(2, {0, 0}, true);

        array <int unsigned> dati_bitset_buffpos =
            array <int unsigned>(2, {0, 0}, true);
        array <int unsigned> dato_bitset_buffpos =
            array <int unsigned>(2, {0, 0}, true);


        dynamic_buffer <uint8_t> (dati_bytestream_buff);
        dynamic_buffer <uint8_t> (dato_bytestream_buff);

        array <uint8_t>
        (* digit_dati_bitbuff ) = new array <uint8_t> (digit_dati_pcount, {}, false);
        array <uint8_t>
        (* digit_dato_bitbuff ) = new array <uint8_t> (digit_dato_pcount, {}, false);
    private :
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

        // rename to extern
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
        (toggle_mloop_serv_state(std::uint8_t(__if_type), bool(__logic)));
        void
        (toggle_iloop_serv_state(std::uint8_t(__if_type), bool(__logic)));

        void
        (update_clock_reading( ) ); //

        void
        (update_mltrigger_count (int unsigned(__update_amount ) ) );
        void
        (update_iltrigger_count (int unsigned(__update_amount ) ) );

        void
        (set_mltrigger_count (int unsigned(__mltick_count ) ) );
        void
        (set_iltrigger_count (int unsigned(__iltick_count ) ) );

        int unsigned
        (get_mltrigger_count( ) );
        int unsigned
        (get_iltrigger_count( ) );

        void
        (reset_mltrigger_count( ) );
        void
        (reset_iltrigger_count( ) );

        bool
        (is_mloop_serv_running (std::uint8_t(__is_type ) ) );
        bool
        (is_iloop_serv_running (std::uint8_t(__is_type ) ) );

        int unsigned(serv_mltrigger_count ) = 0;
        int unsigned(serv_iltrigger_count ) = 0;

        std::uint8_t(serv_mloop_running ) = (tmp_config::lstate::__not_running);
        std::uint8_t(serv_iloop_running ) = (tmp_config::lstate::__not_running);
} ; }

# endif /*__io__service__hpp__*/
