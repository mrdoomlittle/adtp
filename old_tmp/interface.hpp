# ifndef __interface__hpp__
# define __interface__hpp__

# include "tmp_config.hpp"
# include "dynamic_array.hpp"
# include "dynamic_buffer.hpp"
# include "tmp_ip.hpp"
# include "bitset.hpp"
# include <string.h>
# include "array.hpp"
# include "pin_manager.hpp"
/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

// still have alot to do one this
namespace tmp { class interface
{
    public :
        interface()
        {
            (this-> ip_addr_list).darr_init(1, 0);
            (this-> dati_pid_list).darr_init(1, 0);
            (this-> dato_pid_list).darr_init(1, 0);
            (this-> datio_cpid_list).darr_init(2, 0);
            (this-> datio_lpid_list).darr_init(2, 0);
            (this-> iface_pmanager_state).darr_init(1, 0);

            (this-> dati_dpacket_buff).dbuff_init(2, 0, 0);
            (this-> dato_dpacket_buff).dbuff_init(2, 0, 0);
        }

        void (create_iface(char const(* __iface_ip_addr), array<uint8_t>(& __dati_pid_list), array<uint8_t>(& __dato_pid_list),
            uint8_t(__dati_clock_pid), uint8_t(__dato_clock_pid), uint8_t(__dati_latch_pid), uint8_t(__dato_latch_pid)))
        {
            (this-> ip_addr_list).add_darr_layer();
            (this-> dati_pid_list).add_darr_layer();
            (this-> dato_pid_list).add_darr_layer();

            (this-> datio_cpid_list).add_darr_layer();
            (this-> datio_lpid_list).add_darr_layer();
            (this-> iface_pmanager_state).add_darr_layer();

            int unsigned(iface_id_addr_length ) = strlen(__iface_ip_addr);

            if (iface_id_addr_length > (this-> ip_addr_list).get_darr_length((this-> ip_addr_lpos)))
                (this-> ip_addr_list).resize_darr(0, (this-> ip_addr_lpos), iface_id_addr_length);

            for (int unsigned(x ) = 0; x != iface_id_addr_length; x ++) {
                char c = __iface_ip_addr[x];
                (this-> ip_addr_list).set_darr_ilayer(&c, (this-> ip_addr_lpos), x);
            }

            if (__dati_pid_list.garr_len() > (this-> dati_pid_list).get_darr_length((this-> ip_addr_lpos)))
                (this-> dati_pid_list).resize_darr(0, (this-> ip_addr_lpos), __dati_pid_list.garr_len( ));

            if (__dati_pid_list.garr_len() > (this-> dato_pid_list).get_darr_length((this-> ip_addr_lpos)))
                (this-> dato_pid_list).resize_darr(0, (this-> ip_addr_lpos), __dati_pid_list.garr_len( ));

            for (int unsigned(x ) = 0; x != __dati_pid_list.garr_len( ); x ++) {
                (this-> dati_pid_list).set_darr_ilayer(&__dati_pid_list[x], (this-> ip_addr_lpos), x);
            }

            for (int unsigned(x ) = 0; x != __dati_pid_list.garr_len( ); x ++) {
                (this-> dato_pid_list).set_darr_ilayer(&__dato_pid_list[x], (this-> ip_addr_lpos), x);
            }

            (this-> datio_cpid_list).set_darr_ilayer(&__dati_clock_pid, (this-> ip_addr_lpos), (tmp_config::io_t::__itype));
            (this-> datio_lpid_list).set_darr_ilayer(&__dati_latch_pid, (this-> ip_addr_lpos), (tmp_config::io_t::__itype));

            (this-> datio_cpid_list).set_darr_ilayer(&__dato_clock_pid, (this-> ip_addr_lpos), (tmp_config::io_t::__otype));
            (this-> datio_lpid_list).set_darr_ilayer(&__dato_latch_pid, (this-> ip_addr_lpos), (tmp_config::io_t::__otype));

            (this-> set_iface_pmanager_state((this-> ip_addr_lpos), __doesent_exist));

            //bool tmp = false;
            //(this-> iface_pmanager_ustate).set_darr_ilayer(&tmp, (this-> ip_addr_lpos), 0);
            (this-> ip_addr_lpos) ++;
        }

    // change to submit_to_pmanager()
    // need renaming and cleaning
        bool
        (update_pmanager(pin_manager(* __pmanager_cinst_ptr), int unsigned(__iface_id)))
        {

            // make sure its not being used
            for (int unsigned(iface ) = 0; iface != (this-> ip_addr_lpos ); iface ++)
            {
                if (__pmanager_cinst_ptr-> get_dati_clock_pid(iface) == *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype))) return false;
                if (__pmanager_cinst_ptr-> get_dato_clock_pid(iface) == *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype))) return false;

                if (__pmanager_cinst_ptr-> get_dati_latch_pid(iface) == *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype))) return false;
                if (__pmanager_cinst_ptr-> get_dato_latch_pid(iface) == *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype))) return false;

                array<uint8_t> ll(4, {}, false);

                ll[0] = *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype));
                ll[1] = *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype));

                ll[2] = *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype));
                ll[3] = *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype));

                for (int unsigned(x ) = 0; x != (this-> dati_pid_list).get_darr_length(iface); x ++) {

                    if (__pmanager_cinst_ptr-> does_dati_pid_exist(*(this-> dati_pid_list).get_darr_ilayer(__iface_id, x), iface) == true) return false;
                    for (int unsigned y = 0; y != 4; y ++)
                        if (__pmanager_cinst_ptr-> does_dati_pid_exist(ll[y], iface) == true) return false;
                }

                for (int unsigned(x ) = 0; x != (this-> dato_pid_list).get_darr_length(iface); x ++) {
                    if (__pmanager_cinst_ptr-> does_dato_pid_exist(*(this-> dato_pid_list).get_darr_ilayer(__iface_id, x), iface) == true) return false;
                    for (int unsigned y = 0; y != 4; y ++)
                        if (__pmanager_cinst_ptr-> does_dati_pid_exist(ll[y], iface) == true) return false;
                }

            }

            int unsigned total_pcount = (this-> dati_pid_list).get_darr_length(__iface_id) +
                (this-> dato_pid_list).get_darr_length(__iface_id) + 4;

            array<uint8_t> ch(total_pcount, {}, false);
            int unsigned cc = 0;

            for (int unsigned(x ) = 0; x != (this-> dati_pid_list).get_darr_length(__iface_id); x ++) {
                ch[x] = *(this-> dati_pid_list).get_darr_ilayer(__iface_id, x);
                cc ++;
            }

            for (int unsigned(x ) = 0; x != (this-> dato_pid_list).get_darr_length(__iface_id); x ++) {
                ch[x + cc] = *(this-> dato_pid_list).get_darr_ilayer(__iface_id, x);
            }
            cc += (this-> dato_pid_list).get_darr_length(__iface_id);

            ch[cc] = *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype));
            ch[cc+1] = *(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype));

            ch[cc+2] = *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype));
            ch[cc+3] = *(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype));

            for (int unsigned x = 0 ; x != total_pcount; x ++)
                for (int unsigned y = 0 ; y != total_pcount; y ++)
                    if (ch[x] == ch[y] && y != x) return false;

            for (int unsigned(x ) = 0; x != (this-> dati_pid_list).get_darr_length(__iface_id); x ++) {
                (__pmanager_cinst_ptr-> add_dati_pid_space(__iface_id));
                (__pmanager_cinst_ptr-> set_dati_pid(*(this-> dati_pid_list).get_darr_ilayer(__iface_id, x), x , __iface_id));
            }

            for (int unsigned(x ) = 0; x != (this-> dato_pid_list).get_darr_length(__iface_id); x ++) {
                (__pmanager_cinst_ptr-> add_dato_pid_space(__iface_id));
                (__pmanager_cinst_ptr-> set_dato_pid(*(this-> dato_pid_list).get_darr_ilayer(__iface_id, x), x, __iface_id));
            }

            (__pmanager_cinst_ptr-> set_dati_clock_pid(*(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype)), __iface_id));
            (__pmanager_cinst_ptr-> set_dato_clock_pid(*(this-> datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype)), __iface_id));

            (__pmanager_cinst_ptr-> set_dati_latch_pid(*(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__itype)), __iface_id));
            (__pmanager_cinst_ptr-> set_dato_latch_pid(*(this-> datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__otype)), __iface_id));

            std::cout << "Updating Pin Manager with New Infomation" << std::endl;
            (this-> iface_count ) ++;

            (this-> set_iface_pmanager_state(__iface_id, __does_exist));

            //bool tmp = true;
            //(this-> iface_pmanager_ustate).set_darr_ilayer(&tmp, __iface_id, 0);

            return true;

        }

        bool
        (is_iface_pmanager_state(int unsigned(__is_type), int unsigned(__iface_id)))
        {
            return((*(this-> iface_pmanager_state).get_darr_ilayer(__iface_id, 0)) == __is_type? true : false);
        }

        int unsigned
        (get_iface_pmanager_state(int unsigned(__iface_id)))
        {
            return(*(this-> iface_pmanager_state).get_darr_ilayer(__iface_id, 0));
        }

        void
        (set_iface_pmanager_state(int unsigned(__iface_id), int unsigned(__pmanager_state)))
        {
            if (__pmanager_state == __does_exist || __pmanager_state == __doesent_exist) {} else return;

            (this-> iface_pmanager_state).set_darr_ilayer(& __pmanager_state, __iface_id, 0);
        }

        int unsigned
        (get_iface_count())
        {
            return ((this-> ip_addr_lpos));
        }

        enum : int unsigned {
            __does_exist,
            __doesent_exist
        };
    private :
        int unsigned(iface_count ) = 0;

        int unsigned(ip_addr_lpos ) = 0;
        dynamic_array <char> ip_addr_list;

        dynamic_array <uint8_t> dati_pid_list;
        dynamic_array <uint8_t> dato_pid_list;

        dynamic_array <uint8_t> datio_cpid_list;
        dynamic_array <uint8_t> datio_lpid_list;

        // this is where we will store the incomming packets from the interface I/O

        dynamic_buffer <uint8_t> dati_dpacket_buff;
        dynamic_buffer <uint8_t> dato_dpacket_buff;

        // might need to change name. this just states if the iface has been uploaded to the pin manager allready
        // NOTE: change to uint8_t using int unsigned is a wast of memory as we are only storing a true false value
        dynamic_array <int unsigned> iface_pmanager_state;
} ; }

# endif /*__interface__hpp__*/
