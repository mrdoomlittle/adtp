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
    my_buffer.dbuff_init(2,2,2);
    int * h = new int [2];
    h[0] = 2;
    
    h[1] = 4;

    my_buffer.add_to_dbuff(h, 2, 0, 0, 0, false, false, false);
    my_buffer.add_to_dbuff(h, 2, 0, 0, 1, false, false, false);
    //my_buffer.add_to_dbuff(h, 2, 0, 0, 0, false, false, false);
    //my_buffer.del_from_buffer();
    //my_buffer.add_to_dbuff(4, 1, 0, false, false);
    int * * output = new int * [8];
    output[0] = my_buffer.get_from_dbuff(2, 0, 0, 0, false, false, false, false);
    output[1] = my_buffer.get_from_dbuff(2, 0, 0, 1, false, false, false, false);
    if (output[0] != nullptr)
        std::cout << "B0 / S0 > " << *(output[0]) << std::endl;
    else
        std::cout << "Pointer Is Nulled" << std::endl;
    if (output[1] != nullptr)
        std::cout << "B1 / S0 > " << *(output[1])<< std::endl;
    else
        std::cout << "Pointer Is Nulled" << std::endl;
    //std::cout << "B0 / S1 > " << *my_buffer.get_from_dbuff(1,0,false,false,true) << std::endl;
    //std::cout << "B1 / S1 > " << *my_buffer.get_from_dbuff(1,1,false,false,true) << std::endl;*/
    adtp::io_service io_service (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & external_mlinit,
        & external_mltick );
}
