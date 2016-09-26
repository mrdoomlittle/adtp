# ifndef __shift__reg__hpp__
# define __shift__reg__hpp__

# define shift_reg_reset_pid 0
# define shift_reg_clock_pid 0
# define shift_reg_latch_pid 0

# define sreg_ctiming_holdup 0

# define def_max_amount_of_sreg 4

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <boost/cstdint.hpp>
# endif
 
# include "dynamic_array.hpp"
# include "pin_manager.hpp"

namespace tmp { class shift_reg
{
    protected :
        typedef pin_manager pmanager_ct;
        pmanager_ct
            (* pmanager_cinst_ptr) = nullptr;

        void (set_pmanager_cinst_ptr(pmanager_ct(* __pmanager_cinst_ptr)))
        {
            (this-> pmanager_cinst_ptr) = __pmanager_cinst_ptr;
        }

        pmanager_ct (* get_pmanager_cinst_ptr())
        {
            return ((this-> pmanager_cinst_ptr));
        }

    private :
        

        int unsigned (max_amount_of_sreg ) = def_max_amount_of_sreg;
        
    public :
        void(set_shift_reg_pid());
        void(get_shift_ref_pid());

        void(set_shift_reg_type());
        void(get_shift_reg_type());

        void(add_shift_register(int unsigned(__shift_ref_arr_pos_id), uint8_t(__shift_reg_opid), uint8_t(__shift_reg_lpid), 
            uint8_t(__shift_reg_cpid), uint8_t(__shift_reg_rpid), int unsigned(__shift_reg_pcount)))
        {
            shift_reg_pid_list.add_darr_layer();
          
            shift_reg_pcount_l.add_darr_layer();

            uint8_t(shift_reg_pid_list_tmp [4]) = {__shift_reg_opid, __shift_reg_lpid, __shift_reg_cpid, __shift_reg_rpid};

            shift_reg_pid_list.set_darr_layer(shift_reg_pid_list_tmp, __shift_ref_arr_pos_id);

            shift_reg_pcount_l.set_darr_ilayer(&__shift_reg_pcount, __shift_ref_arr_pos_id, 0);
 
        }

        void(del_shift_register());

        void(set_shift_reg_opstate());// input
        void(set_shift_reg_lpstate());// latch
        void(set_shift_reg_cpstate());// clock
        void(set_shift_reg_rpstate());// reset

        void(get_shift_ref_opstate());

        shift_reg()
        {
            (this-> shift_reg_pid_list).darr_init ((this-> max_amount_of_sreg), 0);
            (this-> shift_reg_pcount_l).darr_init(1, 0);
        }

    private :
     

        dynamic_array <uint8_t> shift_reg_pid_list;

        //dynamic_array <uint8_t> shift_reg_ipidl;

        dynamic_array <int unsigned> shift_reg_pcount_l;
        dynamic_array <int unsigned> shift_ref_pstate_l;
        //dynamic_array <int unsigned> shift_reg_tl;
} ; }

# endif /*__shift__reg__hpp__*/
