# include "io_service.hpp"
# include "dynamic_buffer.hpp"
# include <boost/cstdint.hpp>

# include <iostream>

void(set_digit_pin_mode (uint8_t (__pin_id ), uint8_t (__pin_mode ) ) ) { }

void(set_digit_pin_state (uint8_t (__pin_id ), uint8_t (__pin_state ) ) ) { }

int unsigned (simulated_pin_state_i [2] [8]) = { {1, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1} } ;

int unsigned (simulated_pin_state_c [10]) = {1, 0, 1, 1, 1, 1, 1, 1, 1, 1} ;

int unsigned (simulated_return_i ) = 0; 
int unsigned (current_pin_pos_i ) = 0;
int unsigned (current_arr_pos ) = 0;

int unsigned (simulated_return_c ) = 0;
int unsigned (current_pin_pos_c ) = 0;

int(get_digit_pin_state (uint8_t (__pin_id ) ) )
{
    if (__pin_id == 2 || __pin_id == 3)
    {
        simulated_return_i = (simulated_pin_state_i [current_arr_pos] [current_pin_pos_i]);

        if (current_pin_pos_i == 7)
        {
            current_pin_pos_i = 0;
            if (current_arr_pos == 1)
                current_arr_pos = 0;
            else
                current_arr_pos ++;
        }
        else current_pin_pos_i ++; 
        return simulated_return_i;
    }

    if (__pin_id == 6 )
    {
        simulated_return_c = (simulated_pin_state_c [current_pin_pos_c]);
        if (current_pin_pos_c == 9)
            current_pin_pos_c = 0;
        else
            current_pin_pos_c ++;
        return simulated_return_c;
    } return 0;
}

void(external_mlinit (adtp::io_service (* _this ) ) )
{
    
}

void(external_mltick (adtp::io_service (* _this ) ) )
{

}

int(main( ) )
{
    adtp::dbint_t my_buffer;
    my_buffer.dbuff_init(2,2);
    my_buffer.add_to_dbuff(21299, 0, 0, true, true);
    my_buffer.add_to_dbuff(21299, 0, 0, true, true);
    my_buffer.add_to_dbuff(21299, 0, 0, true, true);
    my_buffer.add_to_dbuff(21299, 0, 0, true, true);
    //std::cout << ">>>>>>>" << my_buffer.get_from_dbuff(0,1,false,false) << std::endl;
    adtp::io_service io_service (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & external_mlinit,
        & external_mltick );
}
