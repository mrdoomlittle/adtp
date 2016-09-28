# ifndef __port__manager__hpp__
# define __port__manager__hpp__
# include "dynamic_array.hpp"
# include "bitset_array.hpp"
namespace tmp { class port_manager
{

    private :
        dynamic_array <int unsigned> port_num_list;
        bitset_array <int unsigned> port_ibitset;
        bitset_array <int unsigned> port_obitset; 
} ; }

# endif /*__port__manager__hpp__*/
