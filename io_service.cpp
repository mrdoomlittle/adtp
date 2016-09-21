# include "io_service.hpp"

# ifndef ARDUINO
    # include <iostream>
# endif

itmp::io_service::io_service (
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

    // IO bitset of 8 (00000000)
    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).bitset_init((this-> i_bitset_size));
    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).bitset_init((this-> o_bitset_size));

    // IO bitset Buffer
    (this-> i_bitset_buffer).dbuff_init(1/*sectors of data*/, (this-> ibitset_buff_size), (this-> i_bitset_size));
    (this-> o_bitset_buffer).dbuff_init(1/*sectors of data*/, (this-> obitset_buff_size), (this-> o_bitset_size));

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

        if ( (this-> get_mltick_count( ) ) == 0 ) 
            (this-> call_external_mlinit (this ) );

        (this-> call_external_mltick (this ) );

        for (int unsigned(x ) = 0; x != (this-> obitset_buff_size ); x ++)
            (this-> o_bitset_buffer).add_to_dbuff((this-> get_io_bitset (1, 0, x)), 2, 0, 0, x, true, true, false);

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

# ifndef ARDUINO
                for (int unsigned(x ) = 0; x != (this-> i_bitset_size ); x ++ )
                    std::cout << "STATE: " << i_bitset_buffer.is_block_smarker(true, 0, x) << ", DBUFF_ID: " << x << std::endl;
               
                
 
                std::cout << "DBUFF_POS: " << i_bitset_buff_pos << std::endl;
# endif
                if ( (this-> i_bitset_buff_pos[0] ) == (this-> ibitset_buff_size ) - 1)
                {
                    //std::cout << "Delete/ing  BITSET DBUFF" << std::endl;
                    /* this will mark the data in the buffer as free to use
                    */
                    //for (int unsigned(x ) = 0; x != (this-> ibitset_buff_size ); x ++ )
                    //    (this-> i_bitset_buffer).del_from_dbuffer(1, 0, x, 0);
                    (this-> i_bitset_buff_pos[0] ) = 0;
                }
                else
                    (this-> i_bitset_buff_pos[0] ) ++;

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
           
                //for (int unsigned(x ) = 0; x != (this-> obitset_buff_size ); x++ )
                //{
                    if ((this-> o_bitset_buffer).is_block_smarker(true, 0, (this-> o_bitset_buff_pos[0] )) == true)
                    {
                        for (int unsigned x = 0; x != 8; x ++)
                            (this-> digit_o_bitset [x]) = * (this-> o_bitset_buffer).get_from_dbuff(2, 0, (this-> o_bitset_buff_pos[0] ), x, false, false, false, true);
                        //(this-> o_bitset_buffer).del_from_dbuffer(1, 0, (this-> o_bitset_buff_pos[0] ), 0);
# ifndef ARDUINO
                        std::cout << "PROSSING: B" << (this-> o_bitset_buff_pos[0] ) << std::endl;
# endif
                        
                        
                    }

                //}
 
                if ( (this-> o_bitset_buff_pos[0] ) == (this-> obitset_buff_size ) - 1)
                {
                    (this-> o_bitset_buff_pos[0] ) = 0;
                }
                else
                    (this-> o_bitset_buff_pos[0] ) ++;
            }
        }

        // if you look up that bit of code only calls when the bitset has been pushed to the output so it wont be called at startup) this is a quick fix for that
        
        if ((this-> get_mltick_count()) == 0)
        {
            if ((this-> o_bitset_buffer).is_block_smarker(true, 0, (this-> o_bitset_buff_pos[0] )) == true)
            {
                for (int unsigned x = 0; x != 8; x ++)
                    (this-> digit_o_bitset [x]) = * (this-> o_bitset_buffer).get_from_dbuff(2, 0, (this-> o_bitset_buff_pos[0] ), x, false, false, false, true);

                (this-> o_bitset_buff_pos[0] ) ++;
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
(itmp::io_service::set_digit_pin_mode (uint8_t(__pin_id ), uint8_t(__pin_mode ) ) )
{
    (this-> set_digit_pin_mode_fptr (__pin_id, __pin_mode ) );
}

void
(itmp::io_service::set_digit_pin_state (uint8_t(__pin_id ), uint8_t(__pin_state ) ) )
{
    (this-> set_digit_pin_state_fptr (__pin_id, __pin_state ) );
}

bool
(itmp::io_service::get_digit_pin_state (uint8_t(__pin_id ) ) )
{
    return ( (this-> get_digit_pin_state_fptr (__pin_id ) ) == 1? true: false);
}

void
(itmp::io_service::call_external_mlinit (io_service(* __class_ptr ) ) )
{
    (this-> external_mlinit_fptr (__class_ptr ) );
}

void
(itmp::io_service::call_external_mltick (io_service(* __class_ptr ) ) )
{
    (this-> external_mltick_fptr (__class_ptr ) );
}

void
(itmp::io_service::update_clock_ptcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ptcount ) += __update_amount; }

void
(itmp::io_service::update_clock_ntcount (int unsigned(__update_amount ) ) )
{
    (this-> external_clock_ntcount ) += __update_amount;
}

void
(itmp::io_service::set_clock_ptcount (int unsigned(__clock_ptcount ) ) )
{
    (this-> external_clock_ptcount ) = __clock_ptcount;
}

void
(itmp::io_service::set_clock_ntcount (int unsigned(__clock_ntcount ) ) )
{
    (this-> external_clock_ntcount ) = __clock_ntcount;
}

bool
(itmp::io_service::is_clock_reading (bool(__is_type ) ) )
{
    return ( (this-> external_clock_reading ) == __is_type? true : false);
}

bool
(itmp::io_service::is_external_clock (bool(__is_type ) ) )
{
    return ( (this-> get_digit_pin_state_fptr ( (this-> digit_clock_pin_id ) ) ) == __is_type? true : false);
}

void
(itmp::io_service::toggle_mloop_state( ) )
{
    (this-> service_mloop_running ) = (this-> service_mloop_running ) ? false : true;
}

void
(itmp::io_service::toggle_iloop_state( ) )
{
    (this-> service_iloop_running ) = (this-> service_iloop_running ) ? false : true;
}

void
(itmp::io_service::update_clock_reading( ) )
{
    (this-> external_clock_reading ) = (this-> get_digit_pin_state_fptr ( (this-> digit_clock_pin_id ) ) ) == 1? true : false;
}

void
(itmp::io_service::update_mltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_mltick_count ) += __update_amount;
}

void
(itmp::io_service::update_iltick_count (int unsigned(__update_amount ) ) )
{
    (this-> service_iltick_count ) += __update_amount;
}

void
(itmp::io_service::set_mltick_count (int unsigned(__mltick_count ) ) )
{
    (this-> service_mltick_count ) = __mltick_count;
}

void
(itmp::io_service::set_iltick_count (int unsigned(__iltick_count ) ) )
{
    (this-> service_iltick_count ) = __iltick_count;
}

int unsigned
(itmp::io_service::get_mltick_count( ) )
{
    return (this-> service_mltick_count );
}

int unsigned
(itmp::io_service::get_iltick_count( ) )
{
    return (this-> service_iltick_count );
}

bool
(itmp::io_service::is_mloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_mloop_running ) == __is_type? true : false);
}

bool
(itmp::io_service::is_iloop_running (bool(__is_type ) ) )
{
    return ( (this-> service_iloop_running ) == __is_type? true : false);
}

void
(itmp::io_service::set_io_bitset (int unsigned(__bitset_id), __bitset_type(* __io_bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)))
{
    switch(__bitset_id)
    {
        case (bitset_id::__i_bitset) :
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos);
                break;
                case (sg_type::__total_array):
                    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos/*not needed*/);
                break;
                default : return;
            }
        break;

        case (bitset_id::__o_bitset) :   
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).set_bitset(__io_bitset, (sg_type::__individual), __ibitset_arr_pos);
                break;

                case (sg_type::__total_array):
                    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).set_bitset(__io_bitset, (sg_type::__total_array), __ibitset_arr_pos/*not needed*/);
                break;

                default : return;
            }
 
        default : return;
    }
}

itmp::io_service::__bitset_type
(* itmp::io_service::get_io_bitset (int unsigned(__bitset_id), int unsigned(__get_type), int unsigned(__ibitset_arr_pos)))
{
    switch(__bitset_id)
    {
        case (bitset_id::__i_bitset) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_io_bitset [(bitset_id::__i_bitset)]).get_bitset((sg_type::__individual), __ibitset_arr_pos));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_io_bitset [(bitset_id::__i_bitset)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos/*not needed*/));
                    break;

                default : return (nullptr);
            }

            break;

        case (bitset_id::__o_bitset) :
            switch(__get_type)
            {
                case (sg_type::__individual) :
                    return ((this-> digit_io_bitset [(bitset_id::__o_bitset)]).get_bitset((sg_type::__individual), __ibitset_arr_pos));
                    break;

                case (sg_type::__total_array) :
                    return ((this-> digit_io_bitset [(bitset_id::__o_bitset)]).get_bitset((sg_type::__total_array), __ibitset_arr_pos/*not needed*/));
                    break;

                default : return (nullptr);
            }

            break;

        default : return(nullptr);
    }
}

void
(itmp::io_service::shift_io_bitset (int unsigned(__bitset_id), int unsigned(__shift_direction), int unsigned(__shift_amount)))
{
    switch(__bitset_id)
    {
        case (bitset_id::__i_bitset) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).shift_bitset((shift_direction::__right), __shift_amount);
                    break;

                case (shift_direction::__left):
                    (this-> digit_io_bitset [(bitset_id::__i_bitset)]).shift_bitset((shift_direction::__left), __shift_amount);
                    break;

                default : return;
            }

       break;
        case (bitset_id::__o_bitset) :
            switch(__shift_direction)
            {
                case (shift_direction::__right):
                    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).shift_bitset((shift_direction::__right), __shift_amount);
                    break;

                case (shift_direction::__left):
                    (this-> digit_io_bitset [(bitset_id::__o_bitset)]).shift_bitset((shift_direction::__left), __shift_amount);
                    break;

                default : return;
            }
        break;

        default : return;
    }
}

void
(itmp::io_service::flip_io_bitset (int unsigned(__bitset_id)))
{
    switch(__bitset_id)
    {
        case (bitset_id::__i_bitset) :
            (this-> digit_io_bitset [(bitset_id::__i_bitset)]).flip_bitset();
        break;
        case (bitset_id::__o_bitset) :
            (this-> digit_io_bitset [(bitset_id::__o_bitset)]).flip_bitset();
        break;
        default : return;
    }
}

void
(itmp::io_service::set_i_bitset (uint8_t(* __i_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)))
{
    switch(__set_type)
    {
        case (sg_type::__individual) :
            (this-> digit_i_bitset [__bitset_arr_pos]) = * __i_bitset;
            break;

        case (sg_type::__total_array) :
            for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != (this-> i_bitset_size); bitset_arr_pos ++)
                (this-> set_i_bitset(&__i_bitset[bitset_arr_pos], (sg_type::__individual), bitset_arr_pos));

            break;

        default : return;
    }
}

uint8_t
(* itmp::io_service::get_i_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)))
{
    switch(__get_type)
    {
        case (sg_type::__individual) :
            return(&(this-> digit_i_bitset [__bitset_arr_pos]));
            break;

        case (sg_type::__total_array) :
            return((this-> digit_i_bitset)); break;

        default : return(nullptr);
    }
}

void
(itmp::io_service::set_o_bitset (uint8_t(* __o_bitset), int unsigned(__set_type), int unsigned(__bitset_arr_pos)))
{
    switch(__set_type)
    {
        case (sg_type::__individual) :
            (this-> digit_o_bitset [__bitset_arr_pos]) = * __o_bitset;
            break;

        case (sg_type::__total_array) :
            for (int unsigned(bitset_arr_pos ) = 0; bitset_arr_pos != (this-> o_bitset_size); bitset_arr_pos ++)
                (this-> set_o_bitset(&__o_bitset[bitset_arr_pos], (sg_type::__individual), bitset_arr_pos));

            break;

        default : return;
    }
}

uint8_t
(* itmp::io_service::get_o_bitset (int unsigned(__get_type), int unsigned(__bitset_arr_pos)))
{
    switch(__get_type)
    {
        case (sg_type::__individual) :
            return(&(this-> digit_o_bitset [__bitset_arr_pos]));
            break;

        case (sg_type::__total_array) :
            return((this-> digit_o_bitset)); break;

        default : return(nullptr);
    }
}
