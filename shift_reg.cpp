# include "shift_reg.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/


// NOTE: this is still being worked on
namespace tmp
{
void (shift_reg::set_pmanager_cinst_ptr(pmanager_ct(* __pmanager_cinst_ptr)))
{
    if ((is_pmanager_cinst_ptr_set) == true)return;

    (this-> pmanager_cinst_ptr) = __pmanager_cinst_ptr;

    (is_pmanager_cinst_ptr_set) = true;
}

shift_reg::pmanager_ct (* shift_reg::get_pmanager_cinst_ptr())
{
    return ((this-> pmanager_cinst_ptr));
}

void(shift_reg::update_shift_reg_ipstates(int unsigned(__shift_reg_arr_pos)))
{
    for (int unsigned(x) = 0; x != *shift_reg_ipcount_l.get_darr_ilayer(__shift_reg_arr_pos, 0); x ++)
    {
        (this-> set_shift_reg_cpstate(__shift_reg_arr_pos, tmp_config::digit_pin_high_state));

        for (int unsigned(y ) = 0; y != shift_reg_ctohigh_holdup; y ++){}

        (this-> set_shift_reg_opstate(__shift_reg_arr_pos, *(this-> shift_ref_ipstate_l).get_darr_ilayer(__shift_reg_arr_pos, x)));

        for (int unsigned(y ) = 0; y != shift_reg_ctolow_holdup; y ++){}

        (this-> set_shift_reg_cpstate(__shift_reg_arr_pos, tmp_config::digit_pin_low_state));
        (this-> set_shift_reg_opstate(__shift_reg_arr_pos, tmp_config::digit_pin_low_state));
    }

    (this-> set_shift_reg_lpstate(__shift_reg_arr_pos, tmp_config::digit_pin_high_state));

    for (int unsigned(y ) = 0; y != shift_reg_ctolow_holdup; y ++){}

    (this-> set_shift_reg_lpstate(__shift_reg_arr_pos, tmp_config::digit_pin_low_state));
}

void (shift_reg::set_shift_reg_obitset(int unsigned(* __obitset), int unsigned(__shift_reg_arr_pos)))
{
    (this-> shift_reg_obitset).set_bitset(__obitset, 1, 0, __shift_reg_arr_pos);
}

int unsigned(* shift_reg::get_shift_reg_obitset(int unsigned(__shift_reg_arr_pos)))
{
    return((this-> shift_reg_obitset).get_bitset(1, 0, __shift_reg_arr_pos));
}

void(shift_reg::add_shift_register(int unsigned(__shift_reg_arr_pos), uint8_t(__shift_reg_opid), uint8_t(__shift_reg_lpid),
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

shift_reg::shift_reg()
{
    (this-> shift_reg_pid_list).darr_init ((this-> max_amount_of_sreg), 0);
    (this-> shift_reg_ipcount_l).darr_init(1, 0);
    (this-> shift_ref_ipstate_l).darr_init (8, 0);
    shift_reg_obitset.bitset_init(8, 0);
}

shift_reg::~shift_reg()
{

} }
