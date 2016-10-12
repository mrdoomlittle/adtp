# ifndef __interface__hpp__
# define __interface__hpp__

# include "tmp_config.hpp"
# include "dynamic_array.hpp"
# include "dynamic_buffer.hpp"
# include "tmp_ip.hpp"
# include "bitset.hpp"
# include <string.h>
# include "array.hpp"

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
            (this-> iface_ip_addr_list).darr_init(15, 0);
            (this-> iface_dati_plist).darr_init(1, 0);
            (this-> iface_dati_eplist).darr_init(2, 0);

            (this-> iface_dato_plist).darr_init(1, 0);
            (this-> iface_dato_eplist).darr_init(2, 0);
        }
        void (create_iface(char const(* __iface_ip_addr), array<uint8_t>(& __dati_pid_list), array<uint8_t>(& __dato_pid_list),
            uint8_t(__dati_clock_pid), uint8_t(__dato_clock_pid), uint8_t(__dati_latch_pid), uint8_t(__dato_latch_pid)))
        {
            (this-> iface_ip_addr_list).add_darr_layer( );

            (this-> iface_dati_plist).add_darr_layer( );
            (this-> iface_dati_eplist).add_darr_layer( );

            (this-> iface_dato_plist).add_darr_layer( );
            (this-> iface_dato_eplist).add_darr_layer( );

            std::cout << "Arr Size's: " << __dati_pid_list.size() << " / " << __dato_pid_list.size() << std::endl;

            for (int unsigned x = 0; x != strlen(__iface_ip_addr); x ++)
            {
                char tmp = __iface_ip_addr[x];

                (this-> iface_ip_addr_list).set_darr_ilayer(&tmp, (this-> iface_ip_addr_lpos), x);
            }

            (this-> iface_ip_addr_lpos) ++;
        }

        void (setup_iface())
        {

        }


    private :
        int unsigned(iface_ip_addr_lpos ) = 0;
        dynamic_array <char> iface_ip_addr_list;

        dynamic_array <uint8_t> iface_dati_plist;
        dynamic_array <uint8_t> iface_dati_eplist;

        dynamic_array <uint8_t> iface_dato_plist;
        dynamic_array <uint8_t> iface_dato_eplist;

        struct iface_info
        {

        };

} ; }

# endif /*__interface__hpp__*/
