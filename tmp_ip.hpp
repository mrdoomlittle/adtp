# ifndef __tmp__ip__hpp__
# define __tmp__ip__hpp__

# include "carg_filter.hpp"
# include "cint_convert.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

# define ip_addr_length 4
# include "tmp_config.hpp"
namespace tmp { class tmp_ip
{
    public :
        void (set_system_ip_addr(const char * __ip_address))
        {
            carg_filter _carg_filter;

            const char ** ip_addr = _carg_filter.filter_list_in(__ip_address, ".", (ip_addr_length*3)+(ip_addr_length-1));

            (this-> sys_ip_addr_char) = const_cast<char *>(__ip_address);

            for (int unsigned(x ) = 0; x != ip_addr_length; x ++)
            {
                (this-> sys_ip_addr_int[x]) = convert_to_int<uint8_t>(ip_addr[x], 3);
            }


            for (int unsigned x = 0; x != 4; x ++)
                std::cout << unsigned(sys_ip_addr_int[x]) << std::endl;
        }

        char * (get_system_ip_addr())
        {
            return nullptr;
        }
    private :
        char * sys_ip_addr_char = nullptr;
        uint8_t sys_ip_addr_int[4];

} ; }

# endif /*__tmp__ip__hpp__*/
