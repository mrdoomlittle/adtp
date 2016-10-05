# ifndef __socket__manager__hpp__
# define __socket__manager__hpp__
// might change the name to 'socket.hpp/cpp'
# include "tmp_config.hpp"
# include "carg_filter.hpp"
# include "port_manager.hpp"


namespace tmp { class socket_manager
{
    public :
        void create_socket(const char * __ip, int unsigned __port)
        {
            carg_filter ip;

            const char ** k = ip.filter_list_in(__ip, ".", 15);

            int unsigned o[4];

            for (int unsigned x = 0; x != ip.get_sub_counter(); x ++)
            {
                //o[x] = static_cast<int unsigned>(k[x]);
            }

        }


} ; }

# endif /*__socket__manager__hpp__*/
