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
    if ((is_pmanager_cinst_ptr_set) == true) return;

    (this-> pmanager_cinst_ptr) = __pmanager_cinst_ptr;

    (is_pmanager_cinst_ptr_set) = true;
}

shift_reg::pmanager_ct (* shift_reg::get_pmanager_cinst_ptr())
{
    return ((this-> pmanager_cinst_ptr));
}

void(shift_reg::update_shift_reg_ipstates(int unsigned(__shift_reg_arr_pos)))
{
    // this need working on and needs to be tested
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

void
(shift_reg::add_shift_register(int unsigned(__register_io_t), uint8_t(__shift_reg_pid), uint8_t(__shift_reg_lpid),
    uint8_t(__shift_reg_cpid), uint8_t(__shift_reg_rpid), int unsigned(__shift_reg_ipcount)))
{
    if ((this-> is_pid_being_used(__shift_reg_pid)) == true) return;
    if ((this-> is_pid_being_used(__shift_reg_lpid)) == true) return;
    if ((this-> is_pid_being_used(__shift_reg_cpid)) == true) return;
    if ((this-> is_pid_being_used(__shift_reg_rpid)) == true) return;

    (this-> shift_reg_pid_list).add_darr_layer();
    (this-> shift_reg_io_type).add_darr_layer();
    (this-> shift_reg_ipcount_l).add_darr_layer();

    uint8_t __shift_reg_pid_list[4] = {__shift_reg_pid, __shift_reg_lpid, __shift_reg_cpid, __shift_reg_rpid};

    (this-> shift_reg_pid_list).set_darr_layer(shift_reg_pid_list, (this-> shift_reg_arr_pos));
    (this-> shift_reg_io_type).set_darr_ilayer(&__register_io_t, (this-> shift_reg_arr_pos), 0);
   // (this-> shift_reg_ipcount_l).set_darr_ilayer(&__shift_reg_ipcount, (this-> shift_reg_arr_pos), 0)

    (this-> shift_reg_arr_pos) ++;
}

bool
(shift_reg::is_pid_being_used(uint8_t(__digit_pid)))
{
    if ((this-> shift_reg_arr_pos) == 0) return(false);

    for (int unsigned(y ) = 0; y != (this-> shift_reg_arr_pos); y ++)
    {
        for (int unsigned(x ) = 0; x != 4; x ++)
        {
            if (*(this-> shift_reg_pid_list).get_darr_ilayer(y, x) == __digit_pid) return(true);    
        }
    }    

    return(false);
}

shift_reg::shift_reg()
{

    (this-> shift_reg_pid_list).darr_init (4, 0);

    (this-> shift_reg_ibitset).bitset_init(8, 0);
    (this-> shift_reg_obitset).bitset_init(8, 0);

    (this-> shift_reg_io_type).darr_init(1, 0);

    (this-> shift_reg_ipcount_l).darr_init(1, 0);
    (this-> shift_ref_ipstate_l).darr_init (8, 0);
}

shift_reg::~shift_reg()
{

} }
