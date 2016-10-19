# include "io_service.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

// this is for debugging
# define INTERFACE_COUNT 1

# ifndef ARDUINO
    # include <iostream>
# endif

namespace tmp
{
void
(io_service::init_pmanager_cinst( ) )
{
    if ( (this-> has_pmanager_cinst_init) == true) return;

    static pmanager_ct pmanager_cinstance(INTERFACE_COUNT);

    (this-> pmanager_cinst_ptr ) = & pmanager_cinstance;

    (this-> has_pmanager_cinst_init ) = true;
}
io_service::pmanager_ct
(* io_service::get_pmanager_cinst_ptr( ) )
{
    return ( (this-> pmanager_cinst_ptr) );
}

void
(io_service::init_sregister_cinst( ) )
{
    if ( (this-> has_sregister_cinst_init) == true) return;

    static sregister_ct sregister_cinstance;
    // might change this
    sregister_cinstance.set_pmanager_cinst_ptr((this-> pmanager_cinst_ptr));

    (this-> sregister_cinst_ptr ) = & sregister_cinstance;

    (this-> has_sregister_cinst_init ) = true;
}
io_service::sregister_ct
(* io_service::get_sregister_cinst_ptr( ) )
{
    return ( (this-> sregister_cinst_ptr) );
}

void
(io_service::init_interface_cinst( ) )
{
    if ( (this-> has_interface_cinst_init) == true) return;

    static interface_ct interface_cinstance;

    (this-> interface_cinst_ptr ) = & interface_cinstance;

    (this-> has_interface_cinst_init ) = true;
}
io_service::interface_ct
(* io_service::get_interface_cinst_ptr( ) )
{
    return ( (this-> interface_cinst_ptr) );
}

io_service::io_service( )
{

}

io_service::~io_service( )
{
    if ( (this-> has_pmanager_cinst_init) == true)
    {
        //delete ( (this-> get_pmanager_cinst_ptr( ) ) );
    }

    if ( (this-> has_sregister_cinst_init) == true)
    {
        //delete ( (this-> get_sregister_cinst_ptr( ) ) );
    }
}

void
(io_service::service_init (
    set_digit_pmode_func_t(* __set_digit_pmode_func_ptr),
    set_digit_pstate_func_t(* __set_digit_pstate_func_ptr),
    get_digit_pstate_func_t(*__get_digit_pstate_func_ptr),
    get_high_rclock_func_t(* __get_high_rclock_func_ptr),
    extern_mlinit_func_t(* __extern_mlinit_func_ptr),
    extern_mltick_func_t(* __extern_mltick_func_ptr)
) )
{
    (this-> set_ptr_to_sdigit_pmode_func (__set_digit_pmode_func_ptr) );
    if ( (this-> is_ptr_to_sdigit_pmode_func (nullptr) ) )
        return;

    (this-> set_ptr_to_sdigit_pstate_func (__set_digit_pstate_func_ptr) );
    if ( (this-> is_ptr_to_sdigit_pstate_func (nullptr) ) )
        return;

    (this-> set_ptr_to_gdigit_pstate_func (__get_digit_pstate_func_ptr) );
    if ( (this-> is_ptr_to_gdigit_pstate_func (nullptr) ) )
        return;

    (this-> set_ptr_to_ghigh_rclock_func (__get_high_rclock_func_ptr) );
    if ( (this-> is_ptr_to_ghigh_rclock_func (nullptr) ) )
        return;

    (this-> set_ptr_to_extern_mlinit_func (__extern_mlinit_func_ptr) );
    if ( (this-> is_ptr_to_extern_mlinit_func (nullptr) ) )
        return;

    (this-> set_ptr_to_extern_mltick_func (__extern_mltick_func_ptr) );
    if ( (this-> is_ptr_to_extern_mltick_func (nullptr) ) )
        return;

    // toggle main loops to true from false default
    (this-> toggle_mloop_serv_state( (tmp_config::lstate::__not_running), true ) );
    (this-> toggle_iloop_serv_state( (tmp_config::lstate::__not_running), true ) );

    // create a instance of classes
    (this-> init_pmanager_cinst( ) );

    (this-> get_pmanager_cinst_ptr()-> set_max_digit_pid_range(12));
    (this-> get_pmanager_cinst_ptr()-> set_min_digit_pid_range(2));

    (this-> init_sregister_cinst( ) );
    (this-> init_interface_cinst( ) );

    array <uint8_t> iface_dati_pid_list(2, {(tmp_config::def_digit_dati_pids [0]), (tmp_config::def_digit_dati_pids [1])}, true);
    array <uint8_t> iface_dato_pid_list(2, {(tmp_config::def_digit_dato_pids [0]), (tmp_config::def_digit_dato_pids [1])}, true);

    (this-> get_interface_cinst_ptr()-> create_iface("192.168.0.100", iface_dati_pid_list, iface_dato_pid_list, 6, 7, 8, 9));

    //this will activate the default interface and  push the data to the pin manager
    if ((this-> get_interface_cinst_ptr()-> update_pmanager ((this-> get_pmanager_cinst_ptr()), 0)) == 0) return;

    (this-> get_pmanager_cinst_ptr()-> set_mio_clock_pid(10, 0));

    /*
        when looking thru interfaces unless the pin manager state for that iface is __does_exist we will skip it
        NOTE: add that.
    */

    /* this is a simulated output so i can test if its working right
    */

    // the (*(array)) is a temp fix
    ((*(this-> digit_dato_bitset)) [0] ) = 1;
    ((*(this-> digit_dato_bitset)) [1] ) = 1;
    ((*(this-> digit_dato_bitset)) [2] ) = 0;
    ((*(this-> digit_dato_bitset)) [3] ) = 1;
    ((*(this-> digit_dato_bitset)) [4] ) = 1;
    ((*(this-> digit_dato_bitset)) [5] ) = 1;
    ((*(this-> digit_dato_bitset)) [6] ) = 1;
    ((*(this-> digit_dato_bitset)) [7] ) = 1;

    (this-> dati_bitset_length).darr_init(1, (this-> get_interface_cinst_ptr()-> get_iface_count()));
    (this-> dato_bitset_length).darr_init(1, (this-> get_interface_cinst_ptr()-> get_iface_count()));

    (this-> dati_bit_read_holdup ) =
        tmp_config::def_dati_bit_read_holdup;

    (this-> dato_bit_write_holdup ) =
        tmp_config::def_dato_bit_write_holdup;

    (this-> dati_byte_read_holdup ) =
        tmp_config::def_dati_byte_read_holdup;

    (this-> dato_byte_write_holdup ) =
        tmp_config::def_dato_byte_write_holdup;

    if ((this-> dati_bitset_buff_size ) == 0)
        (this-> dati_bitset_buff_size ) =
            tmp_config::def_dati_bitset_buff_size;

    if ((this-> dato_bitset_buff_size ) == 0)
        (this-> dato_bitset_buff_size ) =
            tmp_config::def_dato_bitset_buff_size;


    for (int unsigned iface = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
    {
        // check and see if the interface has been uploaded to the pin_manager
        if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state((interface::__doesent_exist), iface))) continue;

        (this-> dati_bitset_length).set_darr_ilayer(const_cast<int unsigned *>(&(tmp_config::def_dati_bitset_length)), iface, 0);

        (this-> dato_bitset_length).set_darr_ilayer(const_cast<int unsigned *>(&(tmp_config::def_dati_bitset_length)), iface, 0);

        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_mio_clock_pid(iface), tmp_config::digit_pin_input_mode) );

        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dati_clock_pid(iface), tmp_config::digit_pin_input_mode) );

        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dato_clock_pid(iface), tmp_config::digit_pin_output_mode) );

        for (int unsigned(x ) = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dati_pcount(iface); x ++)
            (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dati_pid (x, iface), tmp_config::digit_pin_input_mode) );

        for (int unsigned(x ) = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dato_pcount(iface); x ++)
            (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dato_pid (x, iface), tmp_config::digit_pin_output_mode) );
    }

    /*
        NOTE: need to add somthing to the main loop so if the amount of interfaces incresses it will change the arrarys like digit_datio_bitset
    */
    (this-> digit_datio_bitset[(tmp_config::io_t::__itype)]).bitset_init (0, (this-> get_interface_cinst_ptr()-> get_iface_count()), false);
    (this-> digit_datio_bitset[(tmp_config::io_t::__otype)]).bitset_init (0, (this-> get_interface_cinst_ptr()-> get_iface_count()), false);

    for (int unsigned iface = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
    {
        (this-> digit_datio_bitset[(tmp_config::io_t::__itype)]).get_bitset_cinst_ptr(iface)-> bitset_init(*(this-> dati_bitset_length).get_darr_ilayer(0, 0));
        (this-> digit_datio_bitset[(tmp_config::io_t::__otype)]).get_bitset_cinst_ptr(iface)-> bitset_init(*(this-> dato_bitset_length).get_darr_ilayer(0, 0));
    }

    (this-> dati_bitset_buff).dbuff_init ((this-> get_interface_cinst_ptr()-> get_iface_count()), (this-> dati_bitset_buff_size), *(this-> dati_bitset_length).get_darr_ilayer(0, 0) );
    (this-> dati_bytestream_buff).dbuff_init((this-> get_interface_cinst_ptr()-> get_iface_count()), (this-> dati_bytestream_bsize), *(this-> dati_bitset_length).get_darr_ilayer(0, 0)) ;

    (this-> dato_bitset_buff).dbuff_init ((this-> get_interface_cinst_ptr()-> get_iface_count()), (this-> dato_bitset_buff_size), *(this-> dato_bitset_length).get_darr_ilayer(0, 0) );
    (this-> dato_bytestream_buff).dbuff_init((this-> get_interface_cinst_ptr()-> get_iface_count()), (this-> dato_bytestream_bsize), *(this-> dato_bitset_length).get_darr_ilayer(0, 0));

    if ( (this-> clock_sstate_ignore) == (tmp_config::digit_pin_high_state))
    {
        (this-> ilclockp_toggled ) = true;
        (this-> ilclockp_tcount ) = 1;
    }

    if ( (this-> clock_sstate_ignore) == (tmp_config::digit_pin_low_state))
    {
        (this-> ilclockn_toggled ) = true;
        (this-> ilclockn_tcount ) = 1;
    }

    do
    {
        if ( (this-> get_mltrigger_count( ) ) != ( (this-> mltrigger_holdup - 1) ) )
        {
            (this-> update_mltrigger_count (1) );
            continue;
        }

        (this-> set_mltrigger_count ( (this-> real_mltick_count ) ) );

        if ( (this-> get_mltrigger_count( ) ) == 0 )
            if ( (this-> call_extern_mlinit (this ) ) == 0) return;

        if ( (this-> call_extern_mltick (this ) ) == 0) return;

        if ((this-> get_interface_cinst_ptr()-> get_iface_count()) == 0) continue;

        (this-> update_clock_reading( ) );

        ((this-> get_pmanager_cinst_ptr())-> update_dati_clock_pstate((this-> get_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pid(0))), 0/*iface id*/));

        (this-> set_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dato_clock_pid(0), (this-> get_pmanager_cinst_ptr())-> get_dato_clock_pstate(0/*iface id*/)));

        (this-> dati_bit_read_holdup ) = tmp_config::def_dati_bit_read_holdup;
        (this-> dato_bit_write_holdup ) = tmp_config::def_dato_bit_write_holdup;

        // might need to change this
        (this-> dati_bit_read_holdup ) = ( (this-> dati_bit_read_holdup ) + ( ( (this-> dati_byte_read_holdup ) - 1) * (8/*bitset_length*/ / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ) ) );
        (this-> dato_bit_write_holdup ) = ( (this-> dato_bit_write_holdup ) + ( ( (this-> dato_byte_write_holdup ) - 1) * (8/*bitset_length*/ / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) ) ) );


        for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
            for (int unsigned(x ) = 0; x != (this-> dati_bitset_buff_size ); x ++)
                (this-> dato_bitset_buff).add_to_dbuff((this-> get_io_bitset (0, 1, 0, x)), 2, 0, 0, x, false, true, false);

# ifndef ARDUINO
        for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
        {
            if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

            std::cout << "IFACE ID: " << iface << std::endl;
            std::cout << "  ";

            for (int unsigned(x ) = 0; x != ( *(this-> dati_bitset_length).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ); x ++ )
                std::cout << ((*(this-> dati_bitset_finished)) [x] );
            std::cout << " :IFBIT, ";

            for (int unsigned(x ) = 0; x != ( *(this-> dato_bitset_length).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) ); x ++ )
                std::cout << ((*(this-> dato_bitset_finished)) [x] );
            std::cout << " :OFBIT";

            std::cout << std::endl;
        }
# endif

        for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
        {
            if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

            for (int unsigned(i_bitsetf_pos ) = 0; i_bitsetf_pos != ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ); i_bitsetf_pos ++ )
            {
                if ( ((*(this-> dati_bitset_finished)) [i_bitsetf_pos] ) == true) (this-> dati_bitsetf_truec ) ++;
                if ((this-> dati_bitsetf_truec ) == ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ) )
                {
                    (this-> dati_bitsetf_truec ) = 0;
# ifndef ARDUINO
                    std::cout << "IBITSET_DUMP: ";

                    for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                        std::cout << unsigned( ((*(this-> digit_dati_bitset)) [x] ) );

                    std::cout << std::endl << std::endl;

                    for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                        std::cout << "STATE: " << dati_bitset_buff.is_block_smarker(true, iface, x) << ", DBUFF_ID: " << x << std::endl;

                    std::cout << "DBUFF_POS: " << dati_bitset_buff_pos << std::endl;

# endif
                    for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                        (this-> dati_bitset_buff).add_to_dbuff(&((*(this-> digit_dati_bitset)) [x]), 2, iface, 0, 0, false, true, true);

                    if ( (this-> dati_bitset_buff_pos ) == (this-> dati_bitset_buff_size ) - 1)
                        (this-> dati_bitset_buff_pos ) = 0;
                    else
                        (this-> dati_bitset_buff_pos ) ++;

                    for (int unsigned(x ) = 0; x != ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ); x ++ )
                        ((*(this-> dati_bitset_finished)) [x] ) = false;
                }
            }

            (this-> dati_bitsetf_truec ) = 0;

            for (int unsigned(o_bitsetf_pos ) = 0; o_bitsetf_pos != ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)); o_bitsetf_pos ++ )
            {
                if ( ((*(this-> dato_bitset_finished)) [o_bitsetf_pos] ) == true) (this-> dato_bitsetf_truec ) ++;
                if ( (this-> dato_bitsetf_truec ) == ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) )
                {
                    (this-> dato_bitsetf_truec ) = 0;
# ifndef ARDUINO
                    std::cout << "OBITSET_DUMP: ";

                    for (int unsigned(x ) = 0; x != *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0); x++ )
                        std::cout << unsigned( ((*(this-> digit_dato_bitset)) [x] ) );

                    std::cout << std::endl;
# endif
                    for (int unsigned(x ) = 0; x != ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())->get_dato_pcount(iface)); x ++ )
                        ((*(this-> dato_bitset_finished)) [x] ) = false;

                    if ((this-> dato_bitset_buff).is_block_smarker(true, iface, (this-> dato_bitset_buff_pos )) == true)
                    {
                        for (int unsigned x = 0; x != 8; x ++)
                            ((*(this-> digit_dato_bitset)) [x]) = *(this-> dato_bitset_buff).get_from_dbuff(2, iface, (this-> dato_bitset_buff_pos ), x, false, false, false, true);
                    }

                    if ( (this-> dato_bitset_buff_pos ) == (this-> dato_bitset_buff_size ) - 1)
                        (this-> dato_bitset_buff_pos ) = 0;
                    else
                        (this-> dato_bitset_buff_pos ) ++;
                }
            }
        }

        // if you look up that bit of code only calls when the bitset has been pushed to the output so it wont be called at startup) this is a quick fix for that
        for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
        {
            if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

            if ((this-> get_mltrigger_count( ) ) == 0)
            {
                if ((this-> dato_bitset_buff).is_block_smarker(true, iface, (this-> dato_bitset_buff_pos )) == true)
                {
                    for (int unsigned x = 0; x != 8; x ++)
                        ((*(this-> digit_dato_bitset)) [x]) = * (this-> dato_bitset_buff).get_from_dbuff(2, iface, (this-> dato_bitset_buff_pos ), x, false, false, false, true);

                    (this-> dato_bitset_buff_pos ) ++;
                }
            }
        }

        (this-> dato_bitsetf_truec ) = 0;

        do
        {
            if ( (this-> get_iltrigger_count( ) ) != ( (this-> iltrigger_holdup - 1) ) )
            {
                (this-> update_iltrigger_count (1) );
                continue;
            }


            (this-> set_iltrigger_count ( (this-> real_iltick_count ) ) );

            if ((this-> get_iltrigger_count( ) ) == 0)
            {
                if ( (this-> is_clock_reading (true) ) == true && (this-> ilclockp_toggled ) == false)
                {
                    (this-> ilclockn_tcount ) = 0;
                    (this-> ilclockn_toggled ) = false;
                    (this-> ilclockp_toggled ) = true;
                }

                if ( (this-> is_clock_reading (false) ) == true && (this-> ilclockn_toggled ) == false)
                {
                    (this-> ilclockp_tcount ) = 0;
                    (this-> ilclockp_toggled ) = false;
                    (this-> ilclockn_toggled ) = true;
                }

                if ( (this-> ilclockp_toggled ) == true && (this-> is_clock_reading (true) ) == true && (this-> ilclockp_tcount ) != 0) break;
                if ( (this-> ilclockn_toggled ) == true && (this-> is_clock_reading (false) ) == true && (this-> ilclockn_tcount ) != 0) break;

                if ( (this-> ilclockp_toggled ) == true)
                    (this-> ilclockp_tcount ) ++;

                if ( (this-> ilclockn_toggled ) == true)
                    (this-> ilclockn_tcount ) ++;
            }

            (this-> temp_iltick_count ) = (this-> get_iltrigger_count( ) );

            (this-> set_iltrigger_count ( (this-> i_iltick_count ) ) );

            /*
                NOTE: e.g. digit_dati_buff_pos needs to have an array size of how many interfaces
            */

            for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
            {
                if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

                if ( (this-> get_iltrigger_count( ) ) <= ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) - 1) + ((this-> dati_bit_read_holdup) - 1) ) && ( (this-> get_iltrigger_count( ) ) ) >= ((this-> dati_bit_read_holdup) - 1) )
                {
                    // input
                    if (((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pstate(iface)) != 0x1)
                    {
                        (this-> is_dati_clock_ppos) = true;
                        ((this-> get_pmanager_cinst_ptr())-> set_dati_clock_ppos_count( ((this-> get_pmanager_cinst_ptr())-> get_dati_clock_ppos_count(iface)) + 1, iface));
                    }

                    if (((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pstate(iface)) != 0x0)
                    {
                        (this-> is_dati_clock_ppos) = false;
                        ((this-> get_pmanager_cinst_ptr())-> set_dati_clock_pneg_count(((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pneg_count(iface)) + 1, iface));
                    }

                    if ((this-> is_dati_clock_ppos) == true)
                    {
                        ((*(this-> digit_dati_bitbuff)) [(this-> digit_dati_buff_pos)] ) = (this-> get_digit_pstate ( ((this-> get_pmanager_cinst_ptr())-> get_dati_pid((this-> digit_dati_buff_pos), iface)) ) );

                        if ( (this-> get_iltrigger_count( ) ) == ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) - 1) + ((this-> dati_bit_read_holdup) - 1) ) + (this-> ibp_pcount_multiplier) ) )
                        {
                            (this-> ibp_pcount_multiplier ) += ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface));
                            (this-> digit_dati_buff_pos ) = 0;
                            if ( (this-> get_iltrigger_count( ) ) == 0)
                            (this-> ibp_pcount_multiplier ) = 0;
                        }
                        else
                        {
                            (this-> digit_dati_buff_pos) ++;
                            if ( (this-> ibp_pcount_multiplier) == ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) )
                            (this-> ibp_pcount_multiplier ) = 0;
                        }

                        if ( (this-> get_iltrigger_count( ) ) == ( ((this-> dati_bit_read_holdup ) - 1) + (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) - 1) ) )
                        {
                            for (int unsigned(i_bitset_pos ) = 0; i_bitset_pos != ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)); i_bitset_pos ++)
                            ((*(this-> digit_dati_bitset)) [( (this-> dati_bitset_fcount ) * ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) + i_bitset_pos)] ) = ((*(this-> digit_dati_bitbuff)) [i_bitset_pos] );

                            if ( ((*(this-> dati_bitset_finished)) [(this-> dati_bitset_fcount )] ) == false)
                                ((*(this-> dati_bitset_finished)) [(this-> dati_bitset_fcount )] ) = true;

                                // REMINDER: fix this
                            if ( (this-> dati_bitset_fcount ) == (/*bitset_length*/8 / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ) - 1)
                                (this-> dati_bitset_fcount ) = 0;
                            else
                                (this-> dati_bitset_fcount ) ++;
                        }

                        (this-> dati_clock_ltcount) ++ ;

                        (this-> is_dati_clock_ppos) = false;
                    }
                }
            }

            (this-> set_iltrigger_count ( (this-> o_iltick_count ) ) );

            for (int unsigned(iface ) = 0; iface != (this-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
            {
                if ((this-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

                if ( (this-> get_iltrigger_count( ) ) <= ( ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) - 1) + (this-> dato_bit_write_holdup - 1) ) && (this-> get_iltrigger_count( ) ) >= (this-> dato_bit_write_holdup - 1) )
                {
                    if ( (this-> get_iltrigger_count( ) ) == ( ( (this-> dato_bit_write_holdup ) - 1) + ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) ) ) || (this-> get_iltrigger_count( ) ) == (this-> dato_bit_write_holdup - 1) )
                    {
                        for (int unsigned(o_bitset_pos ) = 0; o_bitset_pos != ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)); o_bitset_pos ++)
                            ((*(this-> digit_dato_bitbuff)) [o_bitset_pos] ) = ((*(this-> digit_dato_bitset)) [( (this-> dato_bitset_fcount ) * ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) + o_bitset_pos )] );

                        if ( ((*(this-> dato_bitset_finished)) [(this-> dato_bitset_fcount )] ) == false)
                        {
                            //(this-> set_digit_pstate((this-> get_dato_latch_pid(0)), tmp_config::digit_pin_high_state));
                            ((*(this-> dato_bitset_finished)) [(this-> dato_bitset_fcount )] ) = true;
                        }

                        // REMINDER: fix this
                        if ( (this-> dato_bitset_fcount ) == ( /*bitset_length*/8 / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) ) - 1)
                            (this-> dato_bitset_fcount ) = 0;
                        else
                            (this-> dato_bitset_fcount ) ++;
                    }

                    (this-> set_digit_pstate (
                        ((this-> get_pmanager_cinst_ptr())-> get_dato_pid((this-> digit_dato_buff_pos), iface)),
                        ((*(this-> digit_dato_bitbuff)) [(this-> digit_dato_buff_pos )] )
                    ) );

                    if ( (this-> get_iltrigger_count( ) ) == ( ( ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) - 1) + (this-> dato_bit_write_holdup - 1) ) + (this-> obp_pcount_multiplier ) ) )
                    {
                        (this-> obp_pcount_multiplier ) += ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface));
                        (this-> digit_dato_buff_pos ) = 0;
                        if ( (this-> get_iltrigger_count( ) ) == 0)
                            (this-> obp_pcount_multiplier ) = 0;
                    }
                    else
                    {
                        (this-> digit_dato_buff_pos ) ++;
                        if ( (this-> obp_pcount_multiplier ) == ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) )
                            (this-> obp_pcount_multiplier ) = 0;
                    }
                }
            }

            (this-> set_iltrigger_count ( (this-> temp_iltick_count ) ) );

            // this need editing so it works with interfaces
            if ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> dati_bit_read_holdup - 1) ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> dato_bit_write_holdup - 1) ) )
            {
                if ( (this-> get_iltrigger_count( ) ) == ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> dati_bit_read_holdup - 1) ) + ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> dato_bit_write_holdup - 1) ) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    (this-> o_iltick_count ) = 0;
                    break;
                }
            }
            else
            {
                if ( (this-> i_iltick_count ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> dati_bit_read_holdup - 1) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    break;
                }

                if ( (this-> o_iltick_count ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> dato_bit_write_holdup - 1) ) )
                {
                    (this-> o_iltick_count ) = 0;
                    break;
                }
            }

            (this-> reset_iltrigger_count( ) );

            (this-> i_iltick_count ) ++;
            (this-> o_iltick_count ) ++;

            (this-> update_rimltick_count (1) );
        } while ( (this-> is_iloop_serv_running ((tmp_config::lstate::__running)) ) == true);

        (this-> reset_iltrigger_count( ) );

        (this-> real_iltick_count ) = 0;

        if ((this-> is_clock_reading (true) ) == true) (this-> update_clock_ptcount (1) );

        if ( (this-> is_clock_reading (false) ) == true) (this-> update_clock_ntcount (1) );

        (this-> reset_mltrigger_count( ) );

        (this-> update_rmltick_count (1) );
    } while ( (this-> is_mloop_serv_running ((tmp_config::lstate::__running)) ) == true);
}

void
(io_service::set_ptr_to_sdigit_pmode_func (set_digit_pmode_func_t(* __set_digit_pmode_func_ptr) ) )
{
    (this-> set_digit_pmode_func_ptr ) = __set_digit_pmode_func_ptr;
}
void
(io_service::set_ptr_to_sdigit_pstate_func (set_digit_pstate_func_t(* __set_digit_pstate_func_ptr) ) )
{
    (this-> set_digit_pstate_func_ptr ) = __set_digit_pstate_func_ptr;
}
void
(io_service::set_ptr_to_gdigit_pstate_func (get_digit_pstate_func_t(* __get_digit_pstate_func_ptr) ) )
{
    (this-> get_digit_pstate_func_ptr ) = __get_digit_pstate_func_ptr;
}
void
(io_service::set_ptr_to_ghigh_rclock_func (get_high_rclock_func_t(* __get_high_rclock_func_ptr) ) )
{
    (this-> get_high_rclock_func_ptr ) = __get_high_rclock_func_ptr;
}
void
(io_service::set_ptr_to_extern_mlinit_func (extern_mlinit_func_t(* __extern_mlinit_func_ptr) ) )
{
    (this-> extern_mlinit_func_ptr ) = __extern_mlinit_func_ptr;
}
void
(io_service::set_ptr_to_extern_mltick_func (extern_mltick_func_t(* __extern_mltick_func_ptr) ) )
{
    (this-> extern_mltick_func_ptr ) = __extern_mltick_func_ptr;
}

bool
(io_service::is_ptr_to_sdigit_pmode_func (set_digit_pmode_func_t(* __is_type) ) )
{
    return ( (this-> set_digit_pmode_func_ptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_sdigit_pstate_func (set_digit_pstate_func_t(* __is_type) ) )
{
    return ( (this-> set_digit_pstate_func_ptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_gdigit_pstate_func (get_digit_pstate_func_t(* __is_type) ) )
{
    return ( (this-> get_digit_pstate_func_ptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_ghigh_rclock_func (get_high_rclock_func_t(* __is_type) ) )
{
    return ( (this-> get_high_rclock_func_ptr ) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_extern_mlinit_func (extern_mlinit_func_t(* __is_type) ) )
{
    return ( (this-> extern_mlinit_func_ptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_extern_mltick_func (extern_mltick_func_t(* __is_type) ) )
{
    return ( (this-> extern_mltick_func_ptr) == __is_type? true : false);
}

void
(io_service::update_rmltick_count(int unsigned(__update_amount )))
{
    (this-> real_mltick_count ) += __update_amount;
}
void
(io_service::update_rimltick_count(int unsigned(__update_amount )))
{
    (this-> real_iltick_count ) += __update_amount;
}

void
(io_service::set_digit_pmode (uint8_t(__digit_pid ), uint8_t(__digit_pmode ) ) )
{
    (this-> set_digit_pmode_func_ptr (__digit_pid, __digit_pmode ) );
}
void
(io_service::set_digit_pstate (uint8_t(__digit_pid ), uint8_t(__digit_pstate ), int unsigned(__interface_id ) ) )
{
    if (__digit_pid > (this-> get_pmanager_cinst_ptr())-> get_max_digit_pid_range())
    {
        (this-> toggle_mloop_serv_state((tmp_config::lstate::__running), true)); // this will stop the main loop
        return;
    }
    if (__digit_pid < (this-> get_pmanager_cinst_ptr())-> get_min_digit_pid_range())
    {
        (this-> toggle_mloop_serv_state((tmp_config::lstate::__running), true)); // this will stop the main loop
        return;
    }

    for (int unsigned(x ) = (this-> get_pmanager_cinst_ptr())-> get_min_digit_pid_range(); x != __digit_pid; x ++)
    {
        //if ((this-> get_sregister_cinst_ptr())-> is_pid_being_used() == true) __digit_pid += 8;
    }

    (this-> set_digit_pstate_func_ptr (__digit_pid, __digit_pstate ) );

    if (__digit_pid == ((this-> get_pmanager_cinst_ptr())-> get_dato_clock_pid(__interface_id) ))
        ((this-> get_pmanager_cinst_ptr())-> update_dato_clock_pstate(__digit_pstate, __interface_id));

    else if (__digit_pid == ((this-> get_pmanager_cinst_ptr())-> get_dato_latch_pid(__interface_id) ))
        ((this-> get_pmanager_cinst_ptr())-> update_dato_latch_pstate(__digit_pstate, __interface_id));
    else
    {
        for (int unsigned(x ) = 0; x != ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(__interface_id)); x ++)
        {
            if (__digit_pid == ((this-> get_pmanager_cinst_ptr())-> get_dati_pid (x, __interface_id) ) )
            {

                return;
            }
        }
    }
}
bool
(io_service::get_digit_pstate (uint8_t(__digit_pid ) ) )
{
    return ( (this-> get_digit_pstate_func_ptr (__digit_pid ) ) == 1? true: false);
}

int unsigned
(io_service::call_extern_mlinit (io_service(* __class_ptr ) ) )
{
    return ( (this-> extern_mlinit_func_ptr (__class_ptr ) ) );
}
int unsigned
(io_service::call_extern_mltick (io_service(* __class_ptr ) ) )
{
    return ( (this-> extern_mltick_func_ptr (__class_ptr ) ) );
}

void
(io_service::update_clock_ptcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ptcount ) += __update_amount;
}
void
(io_service::update_clock_ntcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ntcount ) += __update_amount;
}

void
(io_service::set_clock_ptcount (int unsigned(__clock_ptcount ) ) )
{
    (this-> external_clock_ptcount ) = __clock_ptcount;
}
void
(io_service::set_clock_ntcount (int unsigned(__clock_ntcount ) ) )
{
    (this-> external_clock_ntcount ) = __clock_ntcount;
}

bool
(io_service::is_clock_reading (bool(__is_type ) ) )
{
    return ( (this-> external_clock_reading ) == __is_type? true : false);
}

bool
(io_service::is_external_clock (bool(__is_type ), int unsigned(__interface_id)) )
{
    return ( (this-> get_digit_pstate_func_ptr ( ((this-> get_pmanager_cinst_ptr())-> get_mio_clock_pid(0) ) ) ) == __is_type? true : false);
}

void
(io_service::toggle_mloop_serv_state(std::uint8_t(__if_type), bool(__logic)))
{
    if (__logic && (this-> serv_mloop_running ) == __if_type)
    {
        (this-> serv_mloop_running ) = (this-> serv_mloop_running )? (tmp_config::lstate::__not_running) : (tmp_config::lstate::__running);
    }
    else
        (this-> serv_mloop_running ) = (this-> serv_mloop_running )? (tmp_config::lstate::__not_running) : (tmp_config::lstate::__running);
}
void
(io_service::toggle_iloop_serv_state(std::uint8_t(__if_type), bool(__logic)))
{
    if (__logic && (this-> serv_mloop_running ) == __if_type)
    {
        (this-> serv_iloop_running ) = (this-> serv_iloop_running )? (tmp_config::lstate::__not_running) : (tmp_config::lstate::__running);
    }
    else
        (this-> serv_iloop_running ) = (this-> serv_iloop_running )? (tmp_config::lstate::__not_running) : (tmp_config::lstate::__running);
}

void
(io_service::update_clock_reading( ) )
{
    (this-> external_clock_reading ) = (this-> get_digit_pstate_func_ptr ( ((this-> get_pmanager_cinst_ptr())-> get_mio_clock_pid(0) ) ) ) == 1? true : false;
}

void
(io_service::update_mltrigger_count (int unsigned(__update_amount ) ) )
{
    (this-> serv_mltrigger_count ) += __update_amount;
}
void
(io_service::update_iltrigger_count (int unsigned(__update_amount ) ) )
{
    (this-> serv_iltrigger_count ) += __update_amount;
}

void
(io_service::set_mltrigger_count (int unsigned(__mltick_count ) ) )
{
    (this-> serv_mltrigger_count ) = __mltick_count;
}
void
(io_service::set_iltrigger_count (int unsigned(__iltick_count ) ) )
{
    (this-> serv_iltrigger_count ) = __iltick_count;
}

int unsigned
(io_service::get_mltrigger_count( ) )
{
    return (this-> serv_mltrigger_count );
}
int unsigned
(io_service::get_iltrigger_count( ) )
{
    return (this-> serv_iltrigger_count );
}

void
(io_service::reset_mltrigger_count( ) )
{
    (this-> serv_mltrigger_count) = 0;
}
void
(io_service::reset_iltrigger_count( ) )
{
    (this-> serv_iltrigger_count) = 0;
}

bool
(io_service::is_mloop_serv_running (std::uint8_t(__is_type ) ) )
{
    return ( (this-> serv_mloop_running ) == __is_type? true : false);
}
bool
(io_service::is_iloop_serv_running (std::uint8_t(__is_type ) ) )
{
    return ( (this-> serv_iloop_running ) == __is_type? true : false);
}

void
(io_service::set_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), __bitset_type(* __io_bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)))
{
    switch(__bitset_id)
    {
        case (tmp_config::io_t::__itype) :
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos, __interface_id);
                break;
                case (sg_type::__total_array):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos, __interface_id);
                break;
                default : return;
            }
        break;

        case (tmp_config::io_t::__otype) :
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos, __interface_id);
                break;

                case (sg_type::__total_array):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos, __interface_id);
                break;

                default : return;
            }

        default : return;
    }
}

io_service::__bitset_type
(* io_service::get_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), int unsigned(__get_type), int unsigned(__ibitset_arr_pos)))
{
    switch(__bitset_id)
    {
        case (tmp_config::io_t::__itype) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).get_bitset((sg_type::__individual), __ibitset_arr_pos, __interface_id));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos, __interface_id));
                    break;

                default : return (nullptr);
            }

            break;

        case (tmp_config::io_t::__otype) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).get_bitset((sg_type::__individual), __ibitset_arr_pos, __interface_id));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos, __interface_id));
                    break;

                default : return (nullptr);
            }

            break;

        default : return(nullptr);
    }
}

void
(io_service::shift_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), int unsigned(__shift_direction), int unsigned(__shift_amount)))
{
    switch(__bitset_id)
    {
        case (tmp_config::io_t::__itype) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).shift_bitset((shift_direction::__right), __shift_amount, __interface_id);
                    break;

                case (shift_direction::__left):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).shift_bitset((shift_direction::__left), __shift_amount, __interface_id);
                    break;

                default : return;
            }

       break;
        case (tmp_config::io_t::__otype) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).shift_bitset((shift_direction::__right), __shift_amount, __interface_id);
                    break;

                case (shift_direction::__left):
                    (this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).shift_bitset((shift_direction::__left), __shift_amount, __interface_id);
                    break;

                default : return;
            }
        break;

        default : return;
    }
}

void
(io_service::flip_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id)))
{
    switch(__bitset_id)
    {
        case (tmp_config::io_t::__itype) :
            (this-> digit_datio_bitset [(tmp_config::io_t::__itype)]).flip_bitset(__interface_id);
        break;
        case (tmp_config::io_t::__otype) :
            (this-> digit_datio_bitset [(tmp_config::io_t::__otype)]).flip_bitset(__interface_id);
        break;
        default : return;
    }
}

void
(io_service::set_dati_bitset (array <uint8_t> (* __dati_bitset)))
{
    for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != 8; bitset_arr_pos ++)
    (*(this-> digit_dati_bitset))[bitset_arr_pos] = (*(__dati_bitset))[bitset_arr_pos];
}
void
(io_service::set_dato_bitset (array <uint8_t> (* __dato_bitset)))
{
    for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != 8; bitset_arr_pos ++)
        (*(this-> digit_dato_bitset))[bitset_arr_pos] = (*(__dato_bitset))[bitset_arr_pos];
}

array <uint8_t>
(* io_service::get_dati_bitset ())
{
    return((this-> digit_dati_bitset));
}
array <uint8_t>
(* io_service::get_dato_bitset ())
{
    return((this-> digit_dati_bitset));
}
}
