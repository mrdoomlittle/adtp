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

io_service::pmanager_ct
(* io_service::get_pmanager_cinst_ptr( ) )
{
    return ( (this-> pmanager_cinst_ptr) );
}
io_service::sregister_ct
(* io_service::get_sregister_cinst_ptr( ) )
{
    return ( (this-> sregister_cinst_ptr) );
}

void
(io_service::init_pmanager_cinst( ) )
{
    if ( (this-> has_pmanager_cinst_init) == true) return;

    static pmanager_ct pmanager_cinstance(2);

    (this-> pmanager_cinst_ptr ) = & pmanager_cinstance;

    (this-> has_pmanager_cinst_init ) = true;
}
void
(io_service::init_sregister_cinst( ) )
{
    if ( (this-> has_sregister_cinst_init) == true) return;

    static sregister_ct sregister_cinstance;

    (this-> sregister_cinst_ptr ) = & sregister_cinstance;

    (this-> has_sregister_cinst_init ) = true;
}

io_service::io_service( )
{

}
io_service::~io_service( )
{
    if ( (this-> has_pmanager_cinst_init) == true)
    {
        //std::free ( (this-> get_pmanager_cinst_ptr( ) ) );
    }

    if ( (this-> has_sregister_cinst_init) == true)
    {
        //std::free ( (this-> get_sregister_cinst_ptr( ) ) );
    }
}

void
(io_service::service_init (
    set_digit_pmode_ft
        (* __set_digit_pmode_fptr),
    set_digit_pstate_ft
        (* __set_digit_pstate_fptr),
    get_digit_pstate_ft
        (*__get_digit_pstate_fptr),
    get_high_rclock_ft
        (* __get_high_rclock_fptr),
    extern_mlinit_ft
        (* __extern_mlinit_fptr),
    extern_mltick_ft
        (* __extern_mltick_fptr)
) )
{
    (this-> set_ptr_to_sdigit_pmode_f (__set_digit_pmode_fptr) );
    (this-> set_ptr_to_sdigit_pstate_f (__set_digit_pstate_fptr) );
    (this-> set_ptr_to_gdigit_pstate_f (__get_digit_pstate_fptr) );
    (this-> set_ptr_to_ghigh_rclock_f (__get_high_rclock_fptr) );
    (this-> set_ptr_to_extern_mlinit_f (__extern_mlinit_fptr) );
    (this-> set_ptr_to_extern_mltick_f (__extern_mltick_fptr) );

    if ( (this-> is_ptr_to_sdigit_pmode_f (nullptr) ) ) return;
    if ( (this-> is_ptr_to_sdigit_pstate_f (nullptr) ) ) return;
    if ( (this-> is_ptr_to_gdigit_pstate_f (nullptr) ) ) return;
    if ( (this-> is_ptr_to_ghigh_rclock_f (nullptr) ) ) return;
    if ( (this-> is_ptr_to_extern_mlinit_f (nullptr) ) ) return;
    if ( (this-> is_ptr_to_extern_mltick_f (nullptr) ) ) return;

    (this-> toggle_mloop_state( ) );

    (this-> toggle_iloop_state( ) );

    // create a instance of classes
    (this-> init_pmanager_cinst( ) );
    (this-> init_sregister_cinst( ) );

    for (int unsigned x = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dati_pcount( 0); x++)
        (this-> get_pmanager_cinst_ptr( ) )-> set_dati_pid ( (tmp_config::def_digit_dati_pids [x]), x, 0/*interface id*/);

    for (int unsigned x = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dato_pcount( 0); x++)
        (this-> get_pmanager_cinst_ptr( ) )-> set_dato_pid ( (tmp_config::def_digit_dato_pids [x]), x, 0/*interface id*/);

    (this-> get_pmanager_cinst_ptr( ) )->
        set_mio_clock_pid (tmp_config::def_digit_mio_clock_pid, 0);
    (this-> get_pmanager_cinst_ptr( ) )->
        set_dati_clock_pid (tmp_config::def_digit_dati_clock_pid, 0);
    (this-> get_pmanager_cinst_ptr( ) )->
        set_dato_clock_pid (tmp_config::def_digit_dato_clock_pid, 0);

    (this-> get_pmanager_cinst_ptr( ) )->
        set_dati_latch_pid (tmp_config::def_digit_dati_latch_pid, 0);
    (this-> get_pmanager_cinst_ptr( ) )->
        set_dato_latch_pid (tmp_config::def_digit_dato_latch_pid, 0);

    /* this is a simulated output so i can test if its working right
    */
    (this-> digit_dato_bitset [0] ) = 1;
    (this-> digit_dato_bitset [1] ) = 1;
    (this-> digit_dato_bitset [2] ) = 0;
    (this-> digit_dato_bitset [3] ) = 1;
    (this-> digit_dato_bitset [4] ) = 1;
    (this-> digit_dato_bitset [5] ) = 1;
    (this-> digit_dato_bitset [6] ) = 1;
    (this-> digit_dato_bitset [7] ) = 1;

    (this-> dati_bitset_length).darr_init(1, INTERFACE_COUNT);
    (this-> dato_bitset_length).darr_init(1, INTERFACE_COUNT);

    for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++)
    {
        (this-> dati_bitset_length).set_darr_ilayer(const_cast<int unsigned *>(&(tmp_config::def_dati_bitset_length)), iface, 0);
        (this-> dato_bitset_length).set_darr_ilayer(const_cast<int unsigned *>(&(tmp_config::def_dati_bitset_length)), iface, 0);
    }

    this-> ibit_read_holdup = tmp_config::def_ibit_read_holdup;

    this-> obit_write_holdup = tmp_config::def_obit_write_holdup;

    this-> ibyte_read_holdup = tmp_config::def_ibyte_read_holdup;

    this-> obyte_write_holdup = tmp_config::def_obyte_write_holdup;

    this-> ibitset_buff_size = tmp_config::def_ibitset_buff_size;

    this-> obitset_buff_size = tmp_config::def_obitset_buff_size;

    for (int unsigned(iface ) = 0; iface != INTERFACE_COUNT; iface ++)
        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )->
            get_mio_clock_pid(iface), tmp_config::digit_pin_input_mode) );

    for (int unsigned(iface ) = 0; iface != INTERFACE_COUNT; iface ++)
        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )->
            get_dati_clock_pid(iface), tmp_config::digit_pin_input_mode) );

    for (int unsigned(iface ) = 0; iface != INTERFACE_COUNT; iface ++)
        (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )->
            get_dato_clock_pid(iface), tmp_config::digit_pin_output_mode) );

    for (int unsigned(iface ) = 0; iface != INTERFACE_COUNT; iface ++)
        for (int unsigned(x ) = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dati_pcount(iface); x ++)
            (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dati_pid (x, 0/*interface id*/), tmp_config::digit_pin_input_mode) );

    for (int unsigned(iface ) = 0; iface != INTERFACE_COUNT; iface ++)
        for (int unsigned(x ) = 0; x != (this-> get_pmanager_cinst_ptr( ) )-> get_dato_pcount(iface); x ++)
            (this-> set_digit_pmode ( (this-> get_pmanager_cinst_ptr( ) )-> get_dato_pid (x, 0/*interface id*/), tmp_config::digit_pin_output_mode) );

    //for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++)
    //{
        (this-> digit_datio_bitset[(bitset_id::__i_bitset)]).bitset_init ( *(this-> dati_bitset_length).get_darr_ilayer(0, 0), INTERFACE_COUNT, false);
        (this-> digit_datio_bitset[(bitset_id::__o_bitset)]).bitset_init ( *(this-> dato_bitset_length).get_darr_ilayer(0, 0), INTERFACE_COUNT, false);
        for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++)
        {
            (this-> digit_datio_bitset[(bitset_id::__i_bitset)]).get_bitset_cinst_ptr(iface)-> bitset_init(INTERFACE_COUNT);
            (this-> digit_datio_bitset[(bitset_id::__o_bitset)]).get_bitset_cinst_ptr(iface)-> bitset_init(INTERFACE_COUNT);
        }

        (this-> dati_bitset_buff).dbuff_init (INTERFACE_COUNT, (this-> ibitset_buff_size), *(this-> dati_bitset_length).get_darr_ilayer(0, 0) );
        (this-> dati_bitset_buff).dbuff_init (INTERFACE_COUNT, (this-> obitset_buff_size), *(this-> dato_bitset_length).get_darr_ilayer(0, 0) );
    //}

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
        if ( (this-> get_mltick_count( ) ) != ( (this-> mltick_holdup - 1) ) )
        {
            (this-> update_mltick_count (1) );
            continue;
        }

        (this-> set_mltick_count ( (this-> real_mltick_count ) ) );

        (this-> update_clock_reading( ) );

        ((this-> get_pmanager_cinst_ptr())-> update_dati_clock_pstate((this-> get_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pid(0))), 0/*iface id*/));

        (this-> set_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dato_clock_pid(0), (this-> get_pmanager_cinst_ptr())-> get_dato_clock_pstate(0/*iface id*/)));

        (this-> ibit_read_holdup ) = tmp_config::def_ibit_read_holdup;
        (this-> obit_write_holdup ) = tmp_config::def_obit_write_holdup;

        // when ibit_read_holdup / etc are arrays like dati_bitset_length then i will update it
        (this-> ibit_read_holdup ) = ( (this-> ibit_read_holdup ) + ( ( (this-> ibyte_read_holdup ) - 1) * (8/*bitset_length*/ / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ) ) );
        (this-> obit_write_holdup ) = ( (this-> obit_write_holdup ) + ( ( (this-> obyte_write_holdup ) - 1) * (8/*bitset_length*/ / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) ) ) );

        if ( (this-> get_mltick_count( ) ) == 0 )
            if ( (this-> call_extern_mlinit (this ) ) == 0) return;

        if ( (this-> call_extern_mltick (this ) ) == 0) return;
return;
        for (int unsigned(x ) = 0; x != (this-> obitset_buff_size ); x ++)
            (this-> dati_bitset_buff).add_to_dbuff((this-> get_io_bitset (0, 1, 0, x)), 2, 0, 0, x, true, true, false);

# ifndef ARDUINO
        for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++)
            for (int unsigned(x ) = 0; x != ( *(this-> dati_bitset_length).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(iface)) ); x ++ )
                std::cout << (this-> i_bitset_finished [x] );

        std::cout << " :IFBIT, ";

        for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++)
            for (int unsigned(x ) = 0; x != ( *(this-> dato_bitset_length).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(iface)) ); x ++ )
                std::cout << (this-> o_bitset_finished [x] );
        std::cout << " :OFBIT";

        std::cout << std::endl;
# endif



for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++) {
        for (int unsigned(i_bitsetf_pos ) = 0; i_bitsetf_pos != ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ); i_bitsetf_pos ++ )
        {
            if ( (this-> i_bitset_finished [i_bitsetf_pos] ) == true) (this-> i_bitsetf_truec ) ++;
            if ((this-> i_bitsetf_truec ) == ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ) )
            {
                (this-> i_bitsetf_truec ) = 0;

# ifndef ARDUINO
                std::cout << "IBITSET: Finished, TrueC: " << (this-> i_bitsetf_truec ) << ", MTickC: " << (this-> get_mltick_count( ) ) << std::endl;

                std::cout << "IBITSET_DUMP: ";

                for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                    std::cout << unsigned( (this-> digit_dati_bitset [x] ) );

                std::cout << std::endl << std::endl;

                for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                    std::cout << "STATE: " << dati_bitset_buff.is_block_smarker(true, iface, x) << ", DBUFF_ID: " << x << std::endl;

                std::cout << "DBUFF_POS: " << i_bitset_buff_pos << std::endl;
# endif

                for (int unsigned(x ) = 0; x != *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0); x ++ )
                    (this-> dati_bitset_buff).add_to_dbuff(&(this-> digit_dati_bitset [x]), 2, iface, 0, 0, false, true, true);

                if ( (this-> i_bitset_buff_pos[0] ) == (this-> ibitset_buff_size ) - 1)
                    (this-> i_bitset_buff_pos[0] ) = 0;

                else (this-> i_bitset_buff_pos[0] ) ++;

                for (int unsigned(x ) = 0; x != ( *(this-> dati_bitset_length ).get_darr_ilayer(iface, 0) / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ); x ++ )
                    (this-> i_bitset_finished [x] ) = false;
            }
        }}

        (this-> i_bitsetf_truec ) = 0;

for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++) {
        for (int unsigned(o_bitsetf_pos ) = 0; o_bitsetf_pos != ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0) ); o_bitsetf_pos ++ )
        {
            if ( (this-> o_bitset_finished [o_bitsetf_pos] ) == true) (this-> o_bitsetf_truec ) ++;
            if ( (this-> o_bitsetf_truec ) == ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0) ) )
            {
                (this-> set_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dato_latch_pid(0), tmp_config::digit_pin_high_state));

                for (int x = 0; x != 1000; x++){} // this is only temporary

                (this-> set_digit_pstate((this-> get_pmanager_cinst_ptr())-> get_dato_latch_pid(0), tmp_config::digit_pin_low_state));

                (this-> o_bitsetf_truec ) = 0;
# ifndef ARDUINO
                std::cout << "OBITSET: Finished, TrueC: " << (this-> o_bitsetf_truec) << ", MTickC: " << (this-> get_mltick_count()) << std::endl;

                std::cout << "OBITSET_DUMP: ";

                for (int unsigned(x ) = 0; x != *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0); x++ )
                    std::cout << unsigned( (this-> digit_dato_bitset [x] ) );

                std::cout << std::endl << std::endl;
# endif
                for (int unsigned(x ) = 0; x != ( *(this-> dato_bitset_length ).get_darr_ilayer(iface, 0) / (this-> get_pmanager_cinst_ptr())->get_dato_pcount(0) ); x ++ )
                    (this-> o_bitset_finished [x] ) = false;

                if ((this-> dati_bitset_buff).is_block_smarker(true, iface, (this-> o_bitset_buff_pos[0] )) == true)
                {
                    for (int unsigned x = 0; x != 8; x ++)
                        (this-> digit_dato_bitset [x]) = *(this-> dati_bitset_buff).get_from_dbuff(2, iface, (this-> o_bitset_buff_pos[0] ), x, false, false, false, true);
                        // (this-> dati_bitset_buff).del_from_dbuffer(1, 0, (this-> o_bitset_buff_pos[0] ), 0);
# ifndef ARDUINO
                    std::cout << "PROSSING: B" << (this-> o_bitset_buff_pos[0] ) << std::endl;
# endif

                }

                if ( (this-> o_bitset_buff_pos[0] ) == (this-> obitset_buff_size ) - 1)
                {
                    (this-> o_bitset_buff_pos[0] ) = 0;
                }
                else
                    (this-> o_bitset_buff_pos[0] ) ++;
            }
        }}

        // if you look up that bit of code only calls when the bitset has been pushed to the output so it wont be called at startup) this is a quick fix for that
for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++) {
        if ((this-> get_mltick_count( ) ) == 0)
        {
            if ((this-> dati_bitset_buff).is_block_smarker(true, iface, (this-> o_bitset_buff_pos[0] )) == true)
            {
                for (int unsigned x = 0; x != 8; x ++)
                    (this-> digit_dato_bitset [x]) = * (this-> dati_bitset_buff).get_from_dbuff(2, iface, (this-> o_bitset_buff_pos[0] ), x, false, false, false, true);

                (this-> o_bitset_buff_pos[0] ) ++;
            }
        }}

        (this-> o_bitsetf_truec ) = 0;

        do
        {
            if ( (this-> get_iltick_count( ) ) != ( (this-> iltick_holdup - 1) ) )
            {
                (this-> update_iltick_count (1) );
                continue;
            }

            (this-> set_iltick_count ( (this-> real_iltick_count ) ) );

            if ((this-> get_iltick_count( ) ) == 0)
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

            (this-> temp_iltick_count ) = (this-> get_iltick_count( ) );

            (this-> set_iltick_count ( (this-> i_iltick_count ) ) );

            for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++) {
            if ( (this-> get_iltick_count( ) ) <= ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + ((this-> ibit_read_holdup) - 1) ) && ( (this-> get_iltick_count( ) ) ) >= ((this-> ibit_read_holdup) - 1) )
            {
                // input
                if (((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pstate(0/*iface id*/)) != 0x1)
                {
                    (this-> is_dati_clock_ppos) = true;
                    ((this-> get_pmanager_cinst_ptr())-> set_dati_clock_ppos_count( ((this-> get_pmanager_cinst_ptr())-> get_dati_clock_ppos_count(iface)) + 1, iface));
                }

                if (((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pstate(0/*iface id*/)) != 0x0)
                {
                    (this-> is_dati_clock_ppos) = false;
                    ((this-> get_pmanager_cinst_ptr())-> set_dati_clock_pneg_count(((this-> get_pmanager_cinst_ptr())-> get_dati_clock_pneg_count(iface)) + 1, iface));
                }

                if ((this-> is_dati_clock_ppos) == true)
                {

                (this-> digit_i_buffer [(this-> digit_i_buffer_pos)] ) = (this-> get_digit_pstate ( ((this-> get_pmanager_cinst_ptr())-> get_dati_pid((this-> digit_i_buffer_pos), 0/*interface id*/)) ) );

                if ( (this-> get_iltick_count( ) ) == ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + ((this-> ibit_read_holdup) - 1) ) + (this-> ibp_pcount_multiplier) ) )
                {
                    (this-> ibp_pcount_multiplier ) += ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0));
                    (this-> digit_i_buffer_pos ) = 0;
                    if ( (this-> get_iltick_count( ) ) == 0)
                        (this-> ibp_pcount_multiplier ) = 0;
                }
                else
                {
                    (this-> digit_i_buffer_pos) ++;
                    if ( (this-> ibp_pcount_multiplier) == ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) )
                        (this-> ibp_pcount_multiplier ) = 0;
                }

                if ( (this-> get_iltick_count( ) ) == ( ((this-> ibit_read_holdup ) - 1) + (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) ) )
                {
                    for (int unsigned(i_bitset_pos ) = 0; i_bitset_pos != ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)); i_bitset_pos ++)
                        (this-> digit_dati_bitset [( (this-> i_bitset_fcount ) * ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) + i_bitset_pos)] ) = (this-> digit_i_buffer [i_bitset_pos] );

                    if ( (this-> i_bitset_finished [(this-> i_bitset_fcount )] ) == false)
                    {
                        (this-> i_bitset_finished [(this-> i_bitset_fcount )] ) = true;
                    }

                    // REMINDER: fix this
                    if ( (this-> i_bitset_fcount ) == (/*bitset_length*/8 / ((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) ) - 1)
                        (this-> i_bitset_fcount ) = 0;
                    else
                        (this-> i_bitset_fcount ) ++;
                }
                    (this-> dati_clock_ltcount) ++ ;

                    (this-> is_dati_clock_ppos) = false;
                }
            } }

            (this-> set_iltick_count ( (this-> o_iltick_count ) ) );

            for (int unsigned iface = 0; iface != INTERFACE_COUNT; iface ++) {
            if ( (this-> get_iltick_count( ) ) <= ( ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> obit_write_holdup - 1) ) && (this-> get_iltick_count( ) ) >= (this-> obit_write_holdup - 1) )
            {
                if ( (this-> get_iltick_count( ) ) == ( ( (this-> obit_write_holdup ) - 1) + ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) ) ) || (this-> get_iltick_count( ) ) == (this-> obit_write_holdup - 1) )
                {
                    for (int unsigned(o_bitset_pos ) = 0; o_bitset_pos != ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)); o_bitset_pos ++)
                        (this-> digit_o_buffer [o_bitset_pos] ) = (this-> digit_dato_bitset [( (this-> o_bitset_fcount ) * ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) + o_bitset_pos )] );

                    if ( (this-> o_bitset_finished [(this-> o_bitset_fcount )] ) == false)
                    {
                        //(this-> set_digit_pstate((this-> get_dato_latch_pid(0)), tmp_config::digit_pin_high_state));
                        (this-> o_bitset_finished [(this-> o_bitset_fcount )] ) = true;
                    }

                    // REMINDER: fix this
                    if ( (this-> o_bitset_fcount ) == ( /*bitset_length*/8 / ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) ) - 1)
                        (this-> o_bitset_fcount ) = 0;
                    else
                        (this-> o_bitset_fcount ) ++;
                }

                (this-> set_digit_pstate (
                    ((this-> get_pmanager_cinst_ptr())-> get_dato_pid((this-> digit_o_buffer_pos), 0/*interface id*/)),
                    (this-> digit_o_buffer [(this-> digit_o_buffer_pos )] )
                ) );

                if ( (this-> get_iltick_count( ) ) == ( ( ( ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> obit_write_holdup - 1) ) + (this-> obp_pcount_multiplier ) ) )
                {
                    (this-> obp_pcount_multiplier ) += ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0));
                    (this-> digit_o_buffer_pos ) = 0;
                    if ( (this-> get_iltick_count( ) ) == 0)
                        (this-> obp_pcount_multiplier ) = 0;
                }
                else
                {
                    (this-> digit_o_buffer_pos ) ++;
                    if ( (this-> obp_pcount_multiplier ) == ((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) )
                        (this-> obp_pcount_multiplier ) = 0;
                }
            } }

            (this-> set_iltick_count ( (this-> temp_iltick_count ) ) );

            if ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> ibit_read_holdup - 1) ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> obit_write_holdup - 1) ) )
            {
                if ( (this-> get_iltick_count( ) ) == ( ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> ibit_read_holdup - 1) ) + ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> obit_write_holdup - 1) ) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    (this-> o_iltick_count ) = 0;
                    break;
                }
            }
            else
            {
                if ( (this-> i_iltick_count ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dati_pcount(0)) - 1) + (this-> ibit_read_holdup - 1) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    break;
                }

                if ( (this-> o_iltick_count ) == ( (((this-> get_pmanager_cinst_ptr())-> get_dato_pcount(0)) - 1) + (this-> obit_write_holdup - 1) ) )
                {
                    (this-> o_iltick_count ) = 0;
                    break;
                }
            }

            (this-> reset_iltick_count( ) );

            (this-> i_iltick_count ) ++;
            (this-> o_iltick_count ) ++;

            (this-> update_rimltick_count (1) );
        } while ( (this-> is_iloop_running (true) ) == true);

        (this-> reset_iltick_count( ) );

        (this-> real_iltick_count ) = 0;

        if ((this-> is_clock_reading (true) ) == true) (this-> update_clock_ptcount (1) );

        if ( (this-> is_clock_reading (false) ) == true) (this-> update_clock_ntcount (1) );

        (this-> reset_mltick_count( ) );

        (this-> update_rmltick_count (1) );
    } while ( (this-> is_mloop_running (true) ) == true);
}

void
(io_service::set_ptr_to_sdigit_pmode_f (set_digit_pmode_ft(* __set_digit_pmode_fptr) ) )
{
    (this-> set_digit_pmode_fptr ) = __set_digit_pmode_fptr;
}
void
(io_service::set_ptr_to_sdigit_pstate_f (set_digit_pstate_ft(* __set_digit_pstate_fptr) ) )
{
    (this-> set_digit_pstate_fptr ) = __set_digit_pstate_fptr;
}
void
(io_service::set_ptr_to_gdigit_pstate_f (get_digit_pstate_ft(* __get_digit_pstate_fptr) ) )
{
    (this-> get_digit_pstate_fptr ) = __get_digit_pstate_fptr;
}
void
(io_service::set_ptr_to_ghigh_rclock_f (get_high_rclock_ft(* __get_high_rclock_fptr) ) )
{
    (this-> get_high_rclock_fptr ) = __get_high_rclock_fptr;
}
void
(io_service::set_ptr_to_extern_mlinit_f (extern_mlinit_ft(* __extern_mlinit_fptr) ) )
{
    (this-> extern_mlinit_fptr ) = __extern_mlinit_fptr;
}
void
(io_service::set_ptr_to_extern_mltick_f (extern_mltick_ft(* __extern_mltick_fptr) ) )
{
    (this-> extern_mltick_fptr ) = __extern_mltick_fptr;
}

bool
(io_service::is_ptr_to_sdigit_pmode_f (set_digit_pmode_ft(* __is_type) ) )
{
    return ( (this-> set_digit_pmode_fptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_sdigit_pstate_f (set_digit_pstate_ft(* __is_type) ) )
{
    return ( (this-> set_digit_pstate_fptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_gdigit_pstate_f (get_digit_pstate_ft(* __is_type) ) )
{
    return ( (this-> get_digit_pstate_fptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_ghigh_rclock_f (get_high_rclock_ft(* __is_type) ) )
{
    return ( (this-> get_high_rclock_fptr ) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_extern_mlinit_f (extern_mlinit_ft(* __is_type) ) )
{
    return ( (this-> extern_mlinit_fptr) == __is_type? true : false);
}
bool
(io_service::is_ptr_to_extern_mltick_f (extern_mltick_ft(* __is_type) ) )
{
    return ( (this-> extern_mltick_fptr) == __is_type? true : false);
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
    (this-> set_digit_pmode_fptr (__digit_pid, __digit_pmode ) );
}
void
(io_service::set_digit_pstate (uint8_t(__digit_pid ), uint8_t(__digit_pstate ), int unsigned(__interface_id ) ) )
{
    (this-> set_digit_pstate_fptr (__digit_pid, __digit_pstate ) );

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
    return ( (this-> get_digit_pstate_fptr (__digit_pid ) ) == 1? true: false);
}

int unsigned
(io_service::call_extern_mlinit (io_service(* __class_ptr ) ) )
{
    return ( (this-> extern_mlinit_fptr (__class_ptr ) ) );
}
int unsigned
(io_service::call_extern_mltick (io_service(* __class_ptr ) ) )
{
    return ( (this-> extern_mltick_fptr (__class_ptr ) ) );
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
    return ( (this-> get_digit_pstate_fptr ( ((this-> get_pmanager_cinst_ptr())-> get_mio_clock_pid(0) ) ) ) == __is_type? true : false);
}

void
(io_service::toggle_mloop_state( ) )
{
    (this-> service_mloop_running ) = (this-> service_mloop_running ) ? false : true;
}
void
(io_service::toggle_iloop_state( ) )
{
    (this-> service_iloop_running ) = (this-> service_iloop_running ) ? false : true;
}

void
(io_service::update_clock_reading( ) )
{
    (this-> external_clock_reading ) = (this-> get_digit_pstate_fptr ( ((this-> get_pmanager_cinst_ptr())-> get_mio_clock_pid(0) ) ) ) == 1? true : false;
}

void
(io_service::update_mltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_mltick_count ) += __update_amount;
}
void
(io_service::update_iltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_iltick_count ) += __update_amount;
}

void
(io_service::set_mltick_count (int unsigned(__mltick_count ) ) )
{
    (this-> service_mltick_count ) = __mltick_count;
}
void
(io_service::set_iltick_count (int unsigned(__iltick_count ) ) )
{
    (this-> service_iltick_count ) = __iltick_count;
}

int unsigned
(io_service::get_mltick_count( ) )
{
    return (this-> service_mltick_count );
}
int unsigned
(io_service::get_iltick_count( ) )
{
    return (this-> service_iltick_count );
}

void
(io_service::reset_mltick_count( ) )
{
    (this-> service_mltick_count) = 0;
}
void
(io_service::reset_iltick_count( ) )
{
    (this-> service_iltick_count) = 0;
}

bool
(io_service::is_mloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_mloop_running ) == __is_type? true : false);
}
bool
(io_service::is_iloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_iloop_running ) == __is_type? true : false);
}

void
(io_service::set_io_bitset (int unsigned(__interface_id), int unsigned(__bitset_id), __bitset_type(* __io_bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)))
{
    switch(__bitset_id)
    {
        case (bitset_id::__i_bitset) :
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_datio_bitset [(bitset_id::__i_bitset)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos, __interface_id);
                break;
                case (sg_type::__total_array):
                    (this-> digit_datio_bitset [(bitset_id::__i_bitset)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos, __interface_id);
                break;
                default : return;
            }
        break;

        case (bitset_id::__o_bitset) :
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_datio_bitset [(bitset_id::__o_bitset)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos, __interface_id);
                break;

                case (sg_type::__total_array):
                    (this-> digit_datio_bitset [(bitset_id::__o_bitset)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos, __interface_id);
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
        case (bitset_id::__i_bitset) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_datio_bitset [(bitset_id::__i_bitset)]).get_bitset((sg_type::__individual), __ibitset_arr_pos, __interface_id));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_datio_bitset [(bitset_id::__i_bitset)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos, __interface_id));
                    break;

                default : return (nullptr);
            }

            break;

        case (bitset_id::__o_bitset) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_datio_bitset [(bitset_id::__o_bitset)]).get_bitset((sg_type::__individual), __ibitset_arr_pos, __interface_id));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_datio_bitset [(bitset_id::__o_bitset)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos, __interface_id));
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
        case (bitset_id::__i_bitset) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_datio_bitset [(bitset_id::__i_bitset)]).shift_bitset((shift_direction::__right), __shift_amount, __interface_id);
                    break;

                case (shift_direction::__left):
                    (this-> digit_datio_bitset [(bitset_id::__i_bitset)]).shift_bitset((shift_direction::__left), __shift_amount, __interface_id);
                    break;

                default : return;
            }

       break;
        case (bitset_id::__o_bitset) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_datio_bitset [(bitset_id::__o_bitset)]).shift_bitset((shift_direction::__right), __shift_amount, __interface_id);
                    break;

                case (shift_direction::__left):
                    (this-> digit_datio_bitset [(bitset_id::__o_bitset)]).shift_bitset((shift_direction::__left), __shift_amount, __interface_id);
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
        case (bitset_id::__i_bitset) :
            (this-> digit_datio_bitset [(bitset_id::__i_bitset)]).flip_bitset(__interface_id);
        break;
        case (bitset_id::__o_bitset) :
            (this-> digit_datio_bitset [(bitset_id::__o_bitset)]).flip_bitset(__interface_id);
        break;
        default : return;
    }
}

void
(io_service::set_i_bitset (uint8_t(* __i_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)))
{
    switch(__set_type)
    {
        case (sg_type::__individual) :
            (this-> digit_dati_bitset [__bitset_arr_pos]) = * __i_bitset;
            break;

        case (sg_type::__total_array) : // fix this
            for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != /*bitset length*/8; bitset_arr_pos ++)
                (this-> set_i_bitset(&__i_bitset[bitset_arr_pos], (sg_type::__individual), bitset_arr_pos));

            break;

        default : return;
    }
}

uint8_t
(* io_service::get_i_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)))
{
    switch(__get_type)
    {
        case (sg_type::__individual) :
            return(&(this-> digit_dati_bitset [__bitset_arr_pos]));
            break;

        case (sg_type::__total_array) :
            return((this-> digit_dati_bitset)); break;

        default : return(nullptr);
    }
}

void
(io_service::set_o_bitset (uint8_t(* __o_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)))
{
    switch(__set_type)
    {
        case (sg_type::__individual) :
            (this-> digit_dato_bitset [__bitset_arr_pos]) = * __o_bitset;
            break;

        case (sg_type::__total_array) : // fix this
            for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != /*bitset length*/8; bitset_arr_pos ++)
                (this-> set_o_bitset(&__o_bitset[bitset_arr_pos], (sg_type::__individual), bitset_arr_pos));

            break;

        default : return;
    }
}

uint8_t
(* io_service::get_o_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)))
{
    switch(__get_type)
    {
        case (sg_type::__individual) :
            return(&(this-> digit_dato_bitset [__bitset_arr_pos]));
            break;

        case (sg_type::__total_array) :
            return((this-> digit_dato_bitset)); break;

        default : return(nullptr);
    }
} }
