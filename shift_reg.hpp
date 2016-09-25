# ifndef __shift__reg__hpp__
# define __shift__reg__hpp__

# define shift_reg_reset_pid 0
# define shift_reg_clock_pid 0
# define shift_reg_latch_pid 0

# define sreg_ctiming_holdup 0

# define def_max_amount_of_sreg 3

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <boost/cstdint.hpp>
# endif
 
# include "dynamic_array.hpp"

namespace tmp { class shift_reg
{
    private :
        int unsigned (max_amount_of_sreg ) = def_max_amount_of_sreg;
        
    public :
        void(set_shift_reg_pid());
        void(get_shift_ref_pid());

        void(set_shift_reg_type());
        void(get_shift_reg_type());

        void(add_shift_register())
        {
           shift_reg_pidl.add_darr_layer(); 
        }

        void(del_shift_register());

        void(set_shift_ref_pstate());
        void(get_shift_ref_pstate());

        shift_reg()
        {
            (this-> shift_reg_pidl).darr_init ((this-> max_amount_of_sreg), 0);
        }

    private :
        dynamic_array <uint8_t> shift_reg_pidl;
        dynamic_array <uint8_t> shift_reg_ipidl;

        dynamic_array <int unsigned> shift_reg_pcl;
        dynamic_array <int unsigned> shift_ref_psl;
        dynamic_array <int unsigned> shift_reg_tl;
} ; }

# endif /*__shift__reg__hpp__*/
