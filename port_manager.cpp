# include "port_manager.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

namespace tmp
{
port_manager::port_manager()
{
    (this-> port_num_list).darr_init(1, 0);
    (this-> port_ibitset).bitset_init((tmp_config::def_dati_bitset_length), 0);
    (this-> port_obitset).bitset_init((tmp_config::def_dato_bitset_length), 0);
    (this-> port_iface_id).darr_init(1, 0);

    (this-> dpackets).init_dpacket_array(0);
}

void
(port_manager::add_port_num(int unsigned(__port_number), bool(__setup_port_num), int unsigned(__interface_id)))
{
    if ((this-> dose_port_num_exist(__port_number)) == true) return;

    (this-> port_num_list).add_darr_layer();
    (this-> port_ibitset).add_bitset();
    (this-> port_obitset).add_bitset();
    (this-> port_iface_id).add_darr_layer();

    (this-> dpackets).add_dpacket();

    if (__setup_port_num == true)
    {
        (this-> set_port_num(__port_number, (this-> port_num_arr_set_pos)));
        (this-> set_port_iface_id(__interface_id, __port_number));
        (this-> port_num_arr_set_pos) ++;
    }
}

void
(port_manager::set_port_num(int unsigned(__port_number), int unsigned(__port_num_arr_pos)))
{
    (this-> port_num_list).set_darr_ilayer(&__port_number, __port_num_arr_pos, 0);
}

int unsigned
(port_manager::get_port_num(int unsigned(__port_num_arr_pos)))
{
    return(* (this-> port_num_list).get_darr_ilayer(__port_num_arr_pos, 0));
}

void
(port_manager::change_port_num(int unsigned(__cport_num), int unsigned(__port_number)))
{
    if ((this-> dose_port_num_exist(__cport_num)) == true) return;

    (this-> port_num_list).set_darr_ilayer(&__port_number, (this-> get_port_num_arr_pos(__cport_num)), 0);
}

bool
(port_manager::dose_port_num_exist(int unsigned(__port_number)))
{
    int unsigned port_num_arr_pos = (this-> get_port_num_arr_pos(__port_number));

    if ((this-> cant_get_port_num_arr_pos) == true)
    {
        (this-> cant_get_port_num_arr_pos) = false;
        return (false);
    }

    if (*(this-> port_num_list).get_darr_ilayer(port_num_arr_pos, 0) == __port_number) return (true);

    return (false);
}

int unsigned
(port_manager::get_port_num_arr_pos(int unsigned(__port_number)))
{
    for (int unsigned(x ) = 0; x != (this-> port_num_list).get_darr_depth(); x ++)
    {
        if (*(this-> port_num_list).get_darr_ilayer(x, 0) == __port_number) return (x);
    }

    (this-> cant_get_port_num_arr_pos ) = true;

    return 0;
}

void
(port_manager::set_port_dati_bitset())
{

}

void
(port_manager::set_port_dato_bitset())
{

}

void
(port_manager::set_port_iface_id(int unsigned(__interface_id), int unsigned(__port_number)))
{
    (this-> port_iface_id).set_darr_ilayer(&__interface_id, (this-> get_port_num_arr_pos(__port_number)), 0);
}

int unsigned
(port_manager::get_port_iface_id(int unsigned(__port_number)))
{
    return (* (this-> port_iface_id).get_darr_ilayer((this-> get_port_num_arr_pos(__port_number)), 0));
}

/* example of how we are going to get the packet as a program

    if ((pin_manager-> get_port_dpacket_ptr())-> is_dpacket_complete() == false) return;

    this can be done other ways!

*/

// hear we are going to send the bitset and add it to the packet
void
(port_manager::update_port_dpacket(int unsigned(__bitset_t), int unsigned(__port_number)))
{

    // the header has a fixed size because we cant determine the size of the data packet so we will
    // store the size of the data packet inside the header with the port and anyother data that we need

    // this need cleaning up. need to add a enum to the config for bitset_t io or ...
    /*
    int unsigned arr_pos = (this-> get_port_num_arr_pos(__port_number));
    if ((this-> dpackets).get_dpacket_ptr(arr_pos)-> is_dpheader_complete() == false)
    {
        switch(__bitset_t)
        {
            case 0:
                (this-> dpackets).get_dpacket_ptr(arr_pos)-> add_to_dpheader(__bitset_t, (this-> port_ibitset));
                break;
            case 1:
                (this-> dpackets).get_dpacket_ptr(arr_pos)-> add_to_dpheader(__bitset_t, (this-> port_obitset));
                break;
        }
    }
    else
    {
        if ((this-> dpackets).get_dpacket_ptr(arr_pos)-> is_dpacket_complete() == false)
        {
            switch(__bitset_t)
            {
                case 0:
                    (this-> dpackets).get_dpacket_ptr(arr_pos)-> add_to_dpacket(__bitset_t, (this-> port_ibitset));
                    break;

                case 1:
                    (this-> dpackets).get_dpacket_ptr(arr_pos)-> add_to_dpacket(__bitset_t, (this-> port_obitset));
                    break;
            }
        }
    }*/
}

void
(port_manager::del_port_num())
{

}

void
(port_manager::mark_port_num())
{

}

void
(port_manager::create_port_num())
{

}

void
(port_manager::open_port_num())
{

}

void
(port_manager::close_port_num())
{

}

int unsigned
(port_manager::get_port_num_count())
{
    return((this-> port_num_list).get_darr_depth());
}

}
