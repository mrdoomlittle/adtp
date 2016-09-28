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
# include <iostream>
# include "dynamic_array.hpp"
# include "pin_manager.hpp"
# include "tmp_config.hpp"
# include "bitset_array.hpp"
namespace tmp { class shift_reg
{
    protected :
        typedef pin_manager pmanager_ct;
        pmanager_ct
            (* pmanager_cinst_ptr) = nullptr;
    public :
        void (set_pmanager_cinst_ptr(pmanager_ct(* __pmanager_cinst_ptr)))
        {
            if ((is_pmanager_cinst_ptr_set) == true)return;

            (this-> pmanager_cinst_ptr) = __pmanager_cinst_ptr;

            (is_pmanager_cinst_ptr_set) = true;
        }
    protected :
        pmanager_ct (* get_pmanager_cinst_ptr())
        {
            return ((this-> pmanager_cinst_ptr));
        }

    private :
        bool (is_pmanager_cinst_ptr_set) = false;

        int unsigned(shift_reg_ctohigh_holdup) = 100;
        int unsigned(shift_reg_ctolow_holdup) = 100;

        int unsigned(shift_reg_ltolow_holdup) = 100;

        int unsigned (max_amount_of_sreg ) = def_max_amount_of_sreg;


        void(set_shift_reg_opstate(int unsigned(__shift_reg_arr_pos), int unsigned(__shift_reg_opstate)))
        {

        }

        void(set_shift_reg_lpstate(int unsigned(__shift_reg_arr_pos), int unsigned(__shift_reg_lpstate)))
        {

        }

        void(set_shift_reg_cpstate(int unsigned(__shift_reg_arr_pos), int unsigned(__shift_reg_cpstate)))
        {

        }

        void(set_shift_reg_rpstate(int unsigned(__shift_reg_arr_pos), int unsigned(__shift_reg_rpstate)))
        {

        }
    public :
        void(set_shift_reg_oipstate(int unsigned(__shift_reg_arr_pos), int unsigned(__shift_reg_arr_ipos_id), int unsigned(__shift_reg_oipstate)))
        {

        }

        void(update_shift_reg_ipstates(int unsigned(__shift_reg_arr_pos)))
        {
            for (int unsigned(x) = 0; x != *shift_reg_ipcount_l.get_darr_ilayer(__shift_reg_arr_pos, 0); x ++)
            {
                (this-> set_shift_reg_cpstate(__shift_reg_arr_pos, digit_pin_high_state));

                for (int unsigned(y ) = 0; y != shift_reg_ctohigh_holdup; y ++){}

                (this-> set_shift_reg_opstate(__shift_reg_arr_pos, *(this-> shift_ref_ipstate_l).get_darr_ilayer(__shift_reg_arr_pos, x)));

                for (int unsigned(y ) = 0; y != shift_reg_ctolow_holdup; y ++){}

                (this-> set_shift_reg_cpstate(__shift_reg_arr_pos, digit_pin_low_state));
                (this-> set_shift_reg_opstate(__shift_reg_arr_pos, digit_pin_low_state));
            }

            (this-> set_shift_reg_lpstate(__shift_reg_arr_pos, digit_pin_high_state));

            for (int unsigned(y ) = 0; y != shift_reg_ctolow_holdup; y ++){}

            (this-> set_shift_reg_lpstate(__shift_reg_arr_pos, digit_pin_low_state));
        }

        void(set_shift_reg_pid())
        {

        }

        void(get_shift_ref_pid())
        {
            
        }

        void (set_shift_reg_obitset(int unsigned(* __obitset), int unsigned(__shift_reg_arr_pos)))
        {
         
            (this-> shift_reg_obitset).set_bitset(__obitset, 1, 0, __shift_reg_arr_pos);
        }

        int unsigned(* get_shift_reg_obitset(int unsigned(__shift_reg_arr_pos)))
        {
            return((this-> shift_reg_obitset).get_bitset(1, 0, __shift_reg_arr_pos));
        }

        // hear we will mark if its a shift out or shift in register
        void(set_shift_reg_type());
        void(get_shift_reg_type());

        void(add_shift_register(int unsigned(__shift_reg_arr_pos), uint8_t(__shift_reg_opid), uint8_t(__shift_reg_lpid),
            uint8_t(__shift_reg_cpid), uint8_t(__shift_reg_rpid), int unsigned(__shift_reg_ipcount)))
        {
            // shift reg pin id list
            shift_reg_pid_list.add_darr_layer();

            // shift reg pin count list
            shift_reg_ipcount_l.add_darr_layer();

            shift_ref_ipstate_l.add_darr_layer();

            //shift_reg_obitset.bitset_init(8);

            uint8_t(shift_reg_pid_list_tmp [4]) = {__shift_reg_opid, __shift_reg_lpid, __shift_reg_cpid, __shift_reg_rpid};

            /* eatch array layers = one pin and its data
            */

            shift_reg_pid_list.set_darr_layer(shift_reg_pid_list_tmp, __shift_reg_arr_pos);

            shift_reg_ipcount_l.set_darr_ilayer(&__shift_reg_ipcount, __shift_reg_arr_pos, 0);

            (this-> shift_reg_obitset).add_bitset();
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
            (this-> shift_reg_ipcount_l).darr_init(1, 0);
            (this-> shift_ref_ipstate_l).darr_init (8, 0);
            shift_reg_obitset.bitset_init(8, 0);
        }

    private :


        dynamic_array <uint8_t> shift_reg_pid_list;

        // turn into array
        bitset_array <int unsigned> shift_reg_obitset;

        dynamic_array <int unsigned> shift_reg_ipcount_l;
        dynamic_array <int unsigned> shift_ref_ipstate_l;
} ; }

# endif /*__shift__reg__hpp__*/
