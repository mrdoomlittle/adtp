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
    // the reasion for this is because we cant have the pins that are meant to control the shift reg as a shift reg pin
    __shift_reg_lpid += (__shift_reg_ipcount - 1);
    __shift_reg_cpid += (__shift_reg_ipcount - 1);
    __shift_reg_rpid += (__shift_reg_ipcount - 1);

    if ( (this-> is_pid_being_used(__shift_reg_pid, true, 0) ) ) return;
    if ( (this-> is_pid_being_used(__shift_reg_lpid, true, 1) ) ) return;
    if ( (this-> is_pid_being_used(__shift_reg_cpid, true, 2) ) ) return;
    if ( (this-> is_pid_being_used(__shift_reg_rpid, true, 3) ) ) return;

    (this-> shift_reg_pid_list).add_darr_layer( );
    (this-> shift_reg_io_type).add_darr_layer( );
    (this-> shift_reg_bind_state).add_darr_layer( );
    (this-> shift_reg_ipcount_l).add_darr_layer( );

    bool temp = false;
    (this-> shift_reg_bind_state).set_darr_ilayer(&temp, (this-> shift_reg_arr_pos), 0);

    uint8_t __shift_reg_pid_list[4] = {__shift_reg_pid, __shift_reg_lpid, __shift_reg_cpid, __shift_reg_rpid};

    (this-> shift_reg_pid_list).set_darr_layer(__shift_reg_pid_list, (this-> shift_reg_arr_pos));

    (this-> shift_reg_io_type).set_darr_ilayer(&__register_io_t, (this-> shift_reg_arr_pos), 0);



    //(this-> shift_reg_ipcount_l).set_darr_ilayer(&__shift_reg_ipcount, (this-> shift_reg_arr_pos), 0);


    (this-> shift_reg_arr_pos) ++;
}
// this will activate the shift reg and forward all pin data to the shift reg
void
(shift_reg::bind_shift_register(uint8_t(__digit_pid)))
{
    // if the shift reg was not setup with the right pins then it will not enable it
    if (__digit_pid > (this-> get_pmanager_cinst_ptr())-> get_max_digit_pid_range()) return;
    if (__digit_pid < (this-> get_pmanager_cinst_ptr())-> get_min_digit_pid_range()) return;

    if ((this-> is_pid_incheck(__digit_pid, 0/*interface num*/)) == false) return;

    if((this-> is_pid_being_used(__digit_pid, true, 0) == false)) return;

    int unsigned * pid_arr_pos = (this-> find_pid_arr_pos(__digit_pid, true, 0));
 
    (this-> get_pmanager_cinst_ptr())-> set_min_digit_pid_range(
        (this-> get_pmanager_cinst_ptr())-> get_min_digit_pid_range() +
        *(this-> shift_reg_ipcount_l).get_darr_ilayer(pid_arr_pos[0], 0));

    if (*(this-> shift_reg_bind_state).get_darr_ilayer(pid_arr_pos[0], 0) == false)
    {
        bool temp = true;
        (this-> shift_reg_bind_state).set_darr_ilayer(&temp, pid_arr_pos[0], 0);
    }

    std::free(pid_arr_pos);
}

bool
(shift_reg::is_shift_reg_binded(bool(__is_type), uint8_t(__digit_pid)))
{
    int unsigned * pid_arr_pos = (this-> find_pid_arr_pos(__digit_pid, true, 0));


    bool output = *(this-> shift_reg_bind_state).get_darr_ilayer(pid_arr_pos[0], 0);

    return(output == __is_type? true : false);

    std::free(pid_arr_pos);
}

bool
(shift_reg::is_pid_being_used(uint8_t(__digit_pid), bool(__specific_pid_t), int unsigned(__pid_type_id)))
{
    if ((this-> shift_reg_arr_pos) == 0) return(false);

    for (int unsigned(y ) = 0; y != (this-> shift_reg_arr_pos); y ++)
    {
        if (__specific_pid_t == false)
        {
            for (int unsigned(x ) = 0; x != 4; x ++) if (*(this-> shift_reg_pid_list).get_darr_ilayer(y, x) == __digit_pid) return(true);
        }
        if (__specific_pid_t == true)
        {
            if (*(this-> shift_reg_pid_list).get_darr_ilayer(y, __pid_type_id) == __digit_pid) return(true);

        }
    }

    return(false);
}

int unsigned
(* shift_reg::find_pid_arr_pos (uint8_t(__digit_pid ), bool(__specific_pid_t ), int unsigned(__pid_type_id ) ) )
{
    for (int unsigned(y ) = 0; y != (this-> shift_reg_arr_pos); y ++)
    {
        if (__specific_pid_t == false)
        {
            for (int unsigned(x ) = 0; x != 4; x ++)
            {
                uint8_t(* shift_reg_pid ) = (this-> shift_reg_pid_list).get_darr_ilayer(y,x);
                if (shift_reg_pid == nullptr) return (nullptr);

                if ((* shift_reg_pid) == __digit_pid)
                {
                    int unsigned(* tmp ) = new int unsigned[2];
                    tmp[0] = y;
                    tmp[1] = x;
                    return (tmp);
                }
            }
        }

        if (__specific_pid_t == true)
        {
            uint8_t(* shift_reg_pid ) = (this-> shift_reg_pid_list).get_darr_ilayer(y,__pid_type_id);
            if (shift_reg_pid == nullptr) return (nullptr);

            if ((* shift_reg_pid) == __digit_pid)
            {
                int unsigned(* tmp ) = new int unsigned[2];
                tmp[0] = y;
                tmp[1] = __pid_type_id;
                return (tmp);
            }
        }
    }

    return (nullptr);
}

bool
(shift_reg::is_pid_incheck(uint8_t(__digit_pid), int unsigned(__interface_id)))
{
    // this will check the pin manager io pins
    // if there is a match then its incheck else not
    int unsigned * temp = (this-> find_pid_arr_pos(__digit_pid, true, 0));

    bool return_output = false;

    // i will change this later.
    int unsigned * val = (this-> shift_reg_io_type).get_darr_ilayer(temp[0], 0);

    if (*val == (tmp_config::io_t::__itype))
    {
        return_output = ((this-> get_pmanager_cinst_ptr())-> does_dati_pid_exist(__digit_pid, __interface_id));
    }

    if (*val == (tmp_config::io_t::__otype))
    {
        return_output = ((this-> get_pmanager_cinst_ptr())-> does_dato_pid_exist(__digit_pid, __interface_id));
    }

    std::free(temp);

    return (return_output);
}

shift_reg::shift_reg()
{

    (this-> shift_reg_pid_list).darr_init (4, 0);

    //(this-> shift_reg_ibitset).bitset_init(8, 0);
    //(this-> shift_reg_obitset).bitset_init(8, 0);

    (this-> shift_reg_io_type).darr_init(1, 0);

    (this-> shift_reg_bind_state).darr_init(1, 0);

    (this-> shift_reg_ipcount_l).darr_init(1, 0);

    //(this-> shift_ref_ipstate_l).darr_init (8, 0);
}

shift_reg::~shift_reg()
{

}
}
