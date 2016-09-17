# include "io_service.hpp"

# define digit_pin_mode_output 0x0
# define digit_pin_mode_input 0x1

# define digit_pin_state_high 0x1
# define digit_pin_state_low 0x0

# ifndef ARDUINO
    # include <iostream>
# endif

adtp::io_service::io_service (
    set_digit_pin_mode_ft(* __set_digit_pin_mode_fptr ),

    set_digit_pin_state_ft(* __set_digit_pin_state_fptr ),

    get_digit_pin_state_ft(*__get_digit_pin_state_fptr ),

    external_mlinit_ft(* __external_mlinit_fptr ),

    external_mltick_ft(* __external_mltick_fptr ) )
{
    if (__set_digit_pin_mode_fptr == nullptr) return;
    if (__set_digit_pin_state_fptr == nullptr) return;
    if (__get_digit_pin_state_fptr == nullptr) return;
    if (__external_mlinit_fptr == nullptr) return;
    if (__external_mltick_fptr == nullptr) return;

    (this-> set_digit_pin_mode_fptr ) = __set_digit_pin_mode_fptr;
    (this-> set_digit_pin_state_fptr ) = __set_digit_pin_state_fptr;
    (this-> get_digit_pin_state_fptr ) = __get_digit_pin_state_fptr;

    (this-> external_mlinit_fptr ) = __external_mlinit_fptr;
    (this-> external_mltick_fptr ) = __external_mltick_fptr;

    (this-> toggle_mloop_state( ) );
    (this-> toggle_iloop_state( ) );

    for (int unsigned x = 0; x != digit_i_pin_count; x++)
        (this-> digit_i_pin_ids [x] ) = (def_digit_i_pin_id [x]);

    for (int unsigned x = 0; x != digit_o_pin_count; x++)
        (this-> digit_o_pin_ids [x] ) = (def_digit_o_pin_id [x]);

    (this-> set_digit_pin_mode (
        (this-> digit_clock_pin_id ),
        digit_pin_mode_input
    ) );

    // this is for debugging
    (this-> digit_o_bitset [0] ) = 1;
    (this-> digit_o_bitset [1] ) = 1;
    (this-> digit_o_bitset [2] ) = 0;
    (this-> digit_o_bitset [3] ) = 1;
    (this-> digit_o_bitset [4] ) = 1;
    (this-> digit_o_bitset [5] ) = 1;
    (this-> digit_o_bitset [6] ) = 1;
    (this-> digit_o_bitset [7] ) = 1;

    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).bitset_init((this-> i_bitset_size));
    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).bitset_init((this-> o_bitset_size));

    (this-> i_bitset_buffer).dbuff_init(1, (this-> ibitset_buff_size), (this-> i_bitset_size));
    (this-> o_bitset_buffer).dbuff_init(1, (this-> obitset_buff_size), (this-> o_bitset_size));

    if ( (this-> clock_start_state ) == digit_pin_state_high )
    {
        (this-> ilclockp_toggled ) = true;
        (this-> ilclockp_tcount ) = 1;
    }

    if ( (this-> clock_start_state ) == digit_pin_state_low )
    {
        (this-> ilclockn_toggled ) = true;
        (this-> ilclockn_tcount ) = 1;
    }

    do
    {
        if ( (this-> get_mltick_count( ) ) != ( (this-> mltick_delay - 1) ) )
        {
            (this-> update_mltick_count (1) );
            continue;
        }

        (this-> set_mltick_count ( (this-> real_mltick_count ) ) );

        (this-> update_clock_reading( ) );
      
        // this might be moved or changed 
        //(this-> set_io_bitset((bitset_id::__i_bitset), (this-> get_i_bitset((sg_type::__total_array), 0)), (sg_type::__total_array), 0));

        //(this-> set_o_bitset( (this-> get_io_bitset((bitset_id::__o_bitset), (sg_type::__total_array), 0)), (sg_type::__total_array), 0));
 
        (this-> ibit_read_delay ) = def_ibit_read_delay;
        (this-> obit_write_delay ) = def_obit_write_delay;

        (this-> ibit_read_delay ) = ( (this-> ibit_read_delay ) + ( ( (this-> ibyte_read_delay ) - 1) * ( (this-> i_bitset_size ) / (this-> digit_i_pin_count ) ) ) );
        (this-> obit_write_delay ) = ( (this-> obit_write_delay ) + ( ( (this-> obyte_write_delay ) - 1) * ( (this-> o_bitset_size ) / (this-> digit_o_pin_count ) ) ) );

        if ( (this-> get_mltick_count( ) ) == 0 ) (this-> call_external_mlinit (this ) );

        if ( (this-> get_mltick_count( ) ) != 0 ) (this-> call_external_mltick (this ) );

# ifndef ARDUINO
        for (int unsigned(x ) = 0; x != ( (this-> i_bitset_size ) / (this->digit_i_pin_count ) ); x ++ )
                std::cout << (this-> i_bitset_finished [x] );
       
        std::cout << " :IFBIT, ";

        for (int unsigned(x ) = 0; x != ( (this-> o_bitset_size ) / (this->digit_o_pin_count ) ); x ++ )
            std::cout << (this-> o_bitset_finished [x] );
        std::cout << " :OFBIT";

        std::cout << std::endl;
# endif
        for (int unsigned(i_bitsetf_pos ) = 0; i_bitsetf_pos != ( (this-> i_bitset_size ) / (this-> digit_i_pin_count ) ); i_bitsetf_pos ++ )
        {
            if ( (this-> i_bitset_finished [i_bitsetf_pos] ) == true) (this-> i_bitsetf_truec ) ++;
            if ((this-> i_bitsetf_truec ) == ( (this-> i_bitset_size ) / (this-> digit_i_pin_count ) ) )
            {
                (this-> i_bitsetf_truec ) = 0;
# ifndef ARDUINO
                std::cout << "IBITSET: Finished, TrueC: " << (this-> i_bitsetf_truec ) << ", MTickC: " << (this-> get_mltick_count( ) ) << std::endl;

                std::cout << "IBITSET_DUMP: ";

                for (int unsigned(x ) = 0; x != (this-> i_bitset_size ); x ++ )
                    std::cout << unsigned( (this-> digit_i_bitset [x] ) );

                std::cout << std::endl << std::endl;
# endif
                for (int unsigned(x ) = 0; x != (this-> i_bitset_size ); x ++ )
                    (this-> i_bitset_buffer).add_to_dbuff(&(this-> digit_i_bitset [x]), 2, 0, 0, 0, true, true, true);
            
                for (int unsigned(x ) = 0; x != (this-> i_bitset_size ); x ++ )
                    std::cout << "STATE: " << i_bitset_buffer.is_block_smarker(true, 0, x) << ", DBUFF_ID: " << x << std::endl;

                std::cout << "DBUFF_POS: " << i_bitset_buff_pos << std::endl;
                if ( (this-> i_bitset_buff_pos ) == (this-> ibitset_buff_size ) - 1)
                {
                    //std::cout << "Delete/ing  BITSET DBUFF" << std::endl;
                    /* this will mark the data in the buffer as free to use
                    */
                    //for (int unsigned(x ) = 0; x != (this-> ibitset_buff_size ); x ++ )
                    //    (this-> i_bitset_buffer).del_from_dbuffer(1, 0, x, 0);
                    (this-> i_bitset_buff_pos ) = 0;
                }
                else
                    (this-> i_bitset_buff_pos ) ++;

                for (int unsigned(x ) = 0; x != ( (this-> i_bitset_size ) / (this-> digit_i_pin_count ) ); x ++ )
                    (this-> i_bitset_finished [x] ) = false;
            }
        }

        (this-> i_bitsetf_truec ) = 0;

        for (int unsigned(o_bitsetf_pos ) = 0; o_bitsetf_pos != ( (this-> o_bitset_size ) / (this-> digit_o_pin_count ) ); o_bitsetf_pos ++ )
        {
            if ( (this-> o_bitset_finished [o_bitsetf_pos] ) == true) (this-> o_bitsetf_truec ) ++;
            if ( (this-> o_bitsetf_truec ) == ( (this-> o_bitset_size ) / (this-> digit_o_pin_count ) ) )
            {
                (this-> o_bitsetf_truec ) = 0;
# ifndef ARDUINO
                std::cout << "OBITSET: Finished, TrueC: " << (this-> o_bitsetf_truec) << ", MTickC: " << (this-> get_mltick_count()) << std::endl;

                std::cout << "OBITSET_DUMP: ";

                for (int unsigned(x ) = 0; x != (this-> o_bitset_size ); x++ )
                    std::cout << unsigned( (this-> digit_o_bitset [x] ) );

                std::cout << std::endl << std::endl;
# endif
                for (int unsigned(x ) = 0; x != ( (this-> o_bitset_size ) / (this-> digit_o_pin_count ) ); x ++ )
                    (this-> o_bitset_finished [x] ) = false;
            }
        }

        (this-> o_bitsetf_truec ) = 0;

        do
        {
            if ( (this-> get_iltick_count( ) ) != ( (this-> iltick_delay - 1) ) )
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

            if ( (this-> get_iltick_count( ) ) <= ( ((this-> digit_i_pin_count) - 1) + ((this-> ibit_read_delay) - 1) ) && ( (this-> get_iltick_count( ) ) ) >= ((this-> ibit_read_delay) - 1) )
            {
                (this-> digit_i_buffer [(this-> digit_i_buffer_pos)] ) = (this-> get_digit_pin_state ( (this-> digit_i_pin_ids [(this-> digit_i_buffer_pos)] ) ) );

                if ( (this-> get_iltick_count( ) ) == ( ( ((this-> digit_i_pin_count ) - 1) + ((this-> ibit_read_delay) - 1) ) + (this-> ibp_pcount_multiplier) ) )
                {
                    (this-> ibp_pcount_multiplier ) += (this-> digit_i_pin_count);
                    (this-> digit_i_buffer_pos ) = 0;
                    if ( (this-> get_iltick_count( ) ) == 0)
                        (this-> ibp_pcount_multiplier ) = 0;
                }
                else
                {
                    (this-> digit_i_buffer_pos) ++;
                    if ( (this-> ibp_pcount_multiplier) == (this-> digit_i_pin_count) )
                        (this-> ibp_pcount_multiplier ) = 0;
                }

                if ( (this-> get_iltick_count( ) ) == ( ((this-> ibit_read_delay ) - 1) + ((this-> digit_i_pin_count ) - 1) ) )
                {
                    for (int unsigned(i_bitset_pos ) = 0; i_bitset_pos != (this-> digit_i_pin_count ); i_bitset_pos ++)
                        (this-> digit_i_bitset [( (this-> i_bitset_fcount ) * (this-> digit_i_pin_count ) + i_bitset_pos)] ) = (this-> digit_i_buffer [i_bitset_pos] );

                    if ( (this-> i_bitset_finished [(this-> i_bitset_fcount )] ) == false)
                        (this-> i_bitset_finished [(this-> i_bitset_fcount )] ) = true;

                    if ( (this-> i_bitset_fcount ) == ((this-> i_bitset_size ) / (this-> digit_i_pin_count ) ) - 1)
                        (this-> i_bitset_fcount ) = 0;
                    else
                        (this-> i_bitset_fcount ) ++;
                }
            }

            (this-> set_iltick_count ( (this-> o_iltick_count ) ) );

            if ( (this-> get_iltick_count( ) ) <= ( ( (this-> digit_o_pin_count ) - 1) + (this-> obit_write_delay - 1) ) && (this-> get_iltick_count( ) ) >= (this-> obit_write_delay - 1) )
            {
                if ( (this-> get_iltick_count( ) ) == ( ( (this-> obit_write_delay ) - 1) + ( (this-> digit_o_pin_count ) ) ) || (this-> get_iltick_count( ) ) == (this-> obit_write_delay - 1) )
                {
                    for (int unsigned(o_bitset_pos ) = 0; o_bitset_pos != (this-> digit_o_pin_count ); o_bitset_pos ++)
                        (this-> digit_o_buffer [o_bitset_pos] ) = (this-> digit_o_bitset [( (this-> o_bitset_fcount ) * (this-> digit_o_pin_count ) + o_bitset_pos )] );

                    if ( (this-> o_bitset_finished [(this-> o_bitset_fcount )] ) == false)
                        (this-> o_bitset_finished [(this-> o_bitset_fcount )] ) = true;

                    if ( (this-> o_bitset_fcount ) == ( (this-> o_bitset_size ) / (this-> digit_o_pin_count ) ) - 1)
                        (this-> o_bitset_fcount ) = 0;
                    else
                        (this-> o_bitset_fcount ) ++;
                }

                (this-> set_digit_pin_state (
                    (this-> digit_o_pin_ids [(this-> digit_o_buffer_pos )] ),
                    (this-> digit_o_buffer [(this-> digit_o_buffer_pos )] )
                ) );

                if ( (this-> get_iltick_count( ) ) == ( ( ( (this-> digit_o_pin_count ) - 1) + (this-> obit_write_delay - 1) ) + (this-> obp_pcount_multiplier ) ) )
                {
                    (this-> obp_pcount_multiplier ) += (this-> digit_o_pin_count );
                    (this-> digit_o_buffer_pos ) = 0;
                    if ( (this-> get_iltick_count( ) ) == 0)
                        (this-> obp_pcount_multiplier ) = 0;
                }
                else
                {
                    (this-> digit_o_buffer_pos ) ++;
                    if ( (this-> obp_pcount_multiplier ) == (this-> digit_o_pin_count ) )
                        (this-> obp_pcount_multiplier ) = 0;
                }
            }

            (this-> set_iltick_count ( (this-> temp_iltick_count ) ) );

            if ( ( (this-> digit_i_pin_count - 1) + (this-> ibit_read_delay - 1) ) == ( (this-> digit_o_pin_count - 1) + (this-> obit_write_delay - 1) ) )
            {
                if ( (this-> get_iltick_count( ) ) == ( ( (this-> digit_i_pin_count - 1) + (this-> ibit_read_delay - 1) ) + ( (this-> digit_o_pin_count - 1) + (this-> obit_write_delay - 1) ) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    (this-> o_iltick_count ) = 0;
                    break;
                }
            }
            else
            {
                if ( (this-> i_iltick_count ) == ( (this-> digit_i_pin_count - 1) + (this-> ibit_read_delay - 1) ) )
                {
                    (this-> i_iltick_count ) = 0;
                    break;
                }

                if ( (this-> o_iltick_count ) == ( (this-> digit_o_pin_count - 1) + (this-> obit_write_delay - 1) ) )
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
(adtp::io_service::set_digit_pin_mode (uint8_t(__pin_id ), uint8_t(__pin_mode ) ) )
{
    (this-> set_digit_pin_mode_fptr (__pin_id, __pin_mode ) );
}

void
(adtp::io_service::set_digit_pin_state (uint8_t(__pin_id ), uint8_t(__pin_state ) ) )
{
    (this-> set_digit_pin_state_fptr (__pin_id, __pin_state ) );
}

bool
(adtp::io_service::get_digit_pin_state (uint8_t(__pin_id ) ) )
{
    return ( (this-> get_digit_pin_state_fptr (__pin_id ) ) == 1? true: false);
}

void
(adtp::io_service::call_external_mlinit (io_service(* __class_ptr ) ) )
{
    (this-> external_mlinit_fptr (__class_ptr ) );
}

void
(adtp::io_service::call_external_mltick (io_service(* __class_ptr ) ) )
{
    (this-> external_mltick_fptr (__class_ptr ) );
}

void
(adtp::io_service::update_clock_ptcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ptcount ) += __update_amount; }

void
(adtp::io_service::update_clock_ntcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ntcount ) += __update_amount;
}

void
(adtp::io_service::set_clock_ptcount (int unsigned(__clock_ptcount ) ) )
{
    (this-> external_clock_ptcount ) = __clock_ptcount;
}

void
(adtp::io_service::set_clock_ntcount (int unsigned(__clock_ntcount ) ) )
{
    (this-> external_clock_ntcount ) = __clock_ntcount;
}

bool
(adtp::io_service::is_clock_reading (bool(__is_type ) ) )
{
    return ( (this-> external_clock_reading ) == __is_type? true : false);
}

bool
(adtp::io_service::is_external_clock (bool(__is_type ) ) )
{
    return ( (this-> get_digit_pin_state_fptr ( (this-> digit_clock_pin_id ) ) ) == __is_type? true : false);
}

void
(adtp::io_service::toggle_mloop_state( ) )
{
    (this-> service_mloop_running ) = (this-> service_mloop_running ) ? false : true;
}

void
(adtp::io_service::toggle_iloop_state( ) )
{
    (this-> service_iloop_running ) = (this-> service_iloop_running ) ? false : true;
}

void
(adtp::io_service::update_clock_reading( ) )
{
    (this-> external_clock_reading ) = (this-> get_digit_pin_state_fptr ( (this-> digit_clock_pin_id ) ) ) == 1? true : false;
}

void
(adtp::io_service::update_mltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_mltick_count ) += __update_amount;
}

void
(adtp::io_service::update_iltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_iltick_count ) += __update_amount;
}

void
(adtp::io_service::set_mltick_count (int unsigned(__mltick_count ) ) )
{
    (this-> service_mltick_count ) = __mltick_count;
}

void
(adtp::io_service::set_iltick_count (int unsigned(__iltick_count ) ) )
{
    (this-> service_iltick_count ) = __iltick_count;
}

int unsigned
(adtp::io_service::get_mltick_count( ) )
{
    return (this-> service_mltick_count );
}

int unsigned
(adtp::io_service::get_iltick_count( ) )
{
    return (this-> service_iltick_count );
}

bool
(adtp::io_service::is_mloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_mloop_running ) == __is_type? true : false);
}

bool
(adtp::io_service::is_iloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_iloop_running ) == __is_type? true : false);
}
