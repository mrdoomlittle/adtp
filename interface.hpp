# ifndef __interface__hpp__
# define __interface__hpp__

# include "tmp_config.hpp"
# include "dynamic_array.hpp"
# include "dynamic_buffer.hpp"
# include "tmp_ip.hpp"
# include "bitset.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

namespace tmp { class interface
{
    public :
        void (create_interface())
        {

        }

    private :
        struct iface_info
        {
            char(* ip_address_asc) = nullptr;
            uint8_t(ip_address_asi[4]);
        };

        iface_info * iface_ilist;


} ; }

# endif /*__interface__hpp__*/
