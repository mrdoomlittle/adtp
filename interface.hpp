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

namespace tmp { class interface
{
    public :
        interface()
        {

            (this-> iface_ip_addr_list).darr_init(1, 0);
            (this-> iface_dati_pid_list).darr_init(1, 0);
            (this-> iface_dato_pid_list).darr_init(1, 0);
            (this-> iface_datio_cpid_list).darr_init(2, 0);
            (this-> iface_datio_lpid_list).darr_init(2, 0);
        }
        void (create_iface(char const(* __iface_ip_addr), array<uint8_t>(& __dati_pid_list), array<uint8_t>(& __dato_pid_list),
            uint8_t(__dati_clock_pid), uint8_t(__dato_clock_pid), uint8_t(__dati_latch_pid), uint8_t(__dato_latch_pid)))
        {
            (this-> iface_ip_addr_list).add_darr_layer();
            (this-> iface_dati_pid_list).add_darr_layer();
            (this-> iface_dato_pid_list).add_darr_layer();

            (this-> iface_datio_cpid_list).add_darr_layer();
            (this-> iface_datio_lpid_list).add_darr_layer();

            int unsigned(iface_id_addr_length ) = strlen(__iface_ip_addr);

            if (iface_id_addr_length > (this-> iface_ip_addr_list).get_darr_length((this-> iface_ip_addr_lpos)))
                (this-> iface_ip_addr_list).resize_darr(0, (this-> iface_ip_addr_lpos), iface_id_addr_length);

            for (int unsigned(x ) = 0; x != iface_id_addr_length; x ++) {
                char c = __iface_ip_addr[x];
                (this-> iface_ip_addr_list).set_darr_ilayer(&c, (this-> iface_ip_addr_lpos), x);
            }

            if (__dati_pid_list.glen() > (this-> iface_dati_pid_list).get_darr_length((this-> iface_ip_addr_lpos)))
                (this-> iface_dati_pid_list).resize_darr(0, (this-> iface_ip_addr_lpos), __dati_pid_list.glen( ));

            if (__dati_pid_list.glen() > (this-> iface_dato_pid_list).get_darr_length((this-> iface_ip_addr_lpos)))
                (this-> iface_dato_pid_list).resize_darr(0, (this-> iface_ip_addr_lpos), __dati_pid_list.glen( ));

            for (int unsigned(x ) = 0; x != __dati_pid_list.glen( ); x ++) {
                (this-> iface_dati_pid_list).set_darr_ilayer(&__dati_pid_list[x], (this-> iface_ip_addr_lpos), x);
            }

            for (int unsigned(x ) = 0; x != __dati_pid_list.glen( ); x ++) {
                (this-> iface_dato_pid_list).set_darr_ilayer(&__dato_pid_list[x], (this-> iface_ip_addr_lpos), x);
            }

            (this-> iface_datio_cpid_list).set_darr_ilayer(&__dati_clock_pid, (this-> iface_ip_addr_lpos), (tmp_config::io_t::__i));
            (this-> iface_datio_lpid_list).set_darr_ilayer(&__dati_latch_pid, (this-> iface_ip_addr_lpos), (tmp_config::io_t::__i));

            (this-> iface_datio_cpid_list).set_darr_ilayer(&__dato_clock_pid, (this-> iface_ip_addr_lpos), (tmp_config::io_t::__o));
            (this-> iface_datio_lpid_list).set_darr_ilayer(&__dato_latch_pid, (this-> iface_ip_addr_lpos), (tmp_config::io_t::__o));

            (this-> iface_ip_addr_lpos) ++;

            std::cout << (this-> iface_ip_addr_list).get_darr_layer(0) << "#" << std::endl;

            // glen = get length
            for (int unsigned(x ) = 0; x != __dati_pid_list.glen( ); x ++) {
                std::cout << unsigned(*(this-> iface_dato_pid_list).get_darr_ilayer(1, x)) << ",";
            }

            std::cout << std::endl;

        }

        bool
        (update_pmanager(pin_manager(* __pmanager_cinst_ptr), int unsigned(__iface_id)))
        {
            // make sure its not being used
            for (int unsigned(iface ) = 0; iface != (this-> iface_ip_addr_lpos ); iface ++)
            {
                if (__pmanager_cinst_ptr-> get_dati_clock_pid(iface) == *(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i))) return false;
                if (__pmanager_cinst_ptr-> get_dato_clock_pid(iface) == *(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o))) return false;

                if (__pmanager_cinst_ptr-> get_dati_latch_pid(iface) == *(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i))) return false;
                if (__pmanager_cinst_ptr-> get_dato_latch_pid(iface) == *(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o))) return false;

                for (int unsigned(x ) = 0; x != (this-> iface_dati_pid_list).get_darr_length(iface); x ++) {
                    if (__pmanager_cinst_ptr-> does_dati_pid_exist(*(this-> iface_dati_pid_list).get_darr_ilayer(__iface_id, x), iface) == true) return false;
                }

                for (int unsigned(x ) = 0; x != (this-> iface_dato_pid_list).get_darr_length(iface); x ++) {
                    if (__pmanager_cinst_ptr-> does_dato_pid_exist(*(this-> iface_dato_pid_list).get_darr_ilayer(__iface_id, x), iface) == true) return false;
                }
            }

            int unsigned total_pcount = (this-> iface_dati_pid_list).get_darr_length(__iface_id) +
                (this-> iface_dato_pid_list).get_darr_length(__iface_id) + 4;

            array<uint8_t> ch(total_pcount, {}, false);
            int unsigned cc = 0;

            for (int unsigned(x ) = 0; x != (this-> iface_dati_pid_list).get_darr_length(__iface_id); x ++) {
                ch[x] = *(this-> iface_dati_pid_list).get_darr_ilayer(__iface_id, x);
                cc ++;
            }

            for (int unsigned(x ) = 0; x != (this-> iface_dato_pid_list).get_darr_length(__iface_id); x ++) {
                ch[x + cc] = *(this-> iface_dato_pid_list).get_darr_ilayer(__iface_id, x);
            }
            cc += (this-> iface_dato_pid_list).get_darr_length(__iface_id);

            ch[cc] = *(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i));
            ch[cc+1] = *(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o));

            ch[cc+2] = *(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i));
            ch[cc+3] = *(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o));

            for (int unsigned x = 0 ; x != total_pcount; x ++)
                for (int unsigned y = 0 ; y != total_pcount; y ++)
                    if (ch[x] == ch[y] && y != x) return false;


            for (int unsigned x = 0 ; x != total_pcount; x ++)
                std::cout << unsigned(ch[x]);
            std::cout << std::endl;
            //cc += x;
            //ch

            for (int unsigned(x ) = 0; x != (this-> iface_dati_pid_list).get_darr_length(__iface_id); x ++) {
                (__pmanager_cinst_ptr-> add_dati_pid_space(__iface_id));
                (__pmanager_cinst_ptr-> set_dati_pid(*(this-> iface_dati_pid_list).get_darr_ilayer(__iface_id, x), x , __iface_id));
            }

            for (int unsigned(x ) = 0; x != (this-> iface_dato_pid_list).get_darr_length(__iface_id); x ++) {
                (__pmanager_cinst_ptr-> add_dato_pid_space(__iface_id));
                (__pmanager_cinst_ptr-> set_dato_pid(*(this-> iface_dato_pid_list).get_darr_ilayer(__iface_id, x), x, __iface_id));
            }

            (__pmanager_cinst_ptr-> set_dati_clock_pid(*(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i)), __iface_id));
            (__pmanager_cinst_ptr-> set_dato_clock_pid(*(this-> iface_datio_cpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o)), __iface_id));

            (__pmanager_cinst_ptr-> set_dati_latch_pid(*(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__i)), __iface_id));
            (__pmanager_cinst_ptr-> set_dato_latch_pid(*(this-> iface_datio_lpid_list).get_darr_ilayer(__iface_id, (tmp_config::io_t::__o)), __iface_id));

            std::cout << "Updating Pin Manager with New Infomation" << std::endl;

            return true;

        }

        int unsigned
        (get_iface_count())
        {
            return ((this-> iface_ip_addr_lpos));
        }

        void (setup_iface())
        {

        }


    private :
        int unsigned(iface_ip_addr_lpos ) = 0;
        dynamic_array <char> iface_ip_addr_list;

        dynamic_array <uint8_t> iface_dati_pid_list;
        dynamic_array <uint8_t> iface_dato_pid_list;

        dynamic_array <uint8_t> iface_datio_cpid_list;
        dynamic_array <uint8_t> iface_datio_lpid_list;


} ; }

# endif /*__interface__hpp__*/
