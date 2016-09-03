# include "io_service.hpp"
# include <cstdint>
# include <iostream>

void(set_digit_pin_mode(uint8_t __pin_id, uint8_t __pin_mode)) { }

void(set_digit_pin_state(uint8_t __pin_id, uint8_t __pin_state))
{
    //std::cout << "PINID: " << unsigned(__pin_id) << ", PINSTATE: " << unsigned(__pin_state) << std::endl;
}

int simulated_pin_state_i [2][8] = {{1, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1}} ;
int simulated_pin_state_c [10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ;
int simulated_return_i = 0; 
int current_pin_pos_i = 0;
int current_arr_pos = 0;
int simulated_return_c = 0;
int current_pin_pos_c = 0;
int(get_digit_pin_state(uint8_t __pin_id))
{
    if (__pin_id == 2 || __pin_id == 3)
    {
        simulated_return_i = simulated_pin_state_i[current_arr_pos][current_pin_pos_i];

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

    if (__pin_id == 6 )  {
    simulated_return_c = simulated_pin_state_c[current_pin_pos_c];
    if (current_pin_pos_c == 9)
        current_pin_pos_c = 0;
    else
        current_pin_pos_c ++;
    //std::cout << "Type: StateGet, " << "PinID: " << unsigned(__pin_id) << std::endl;

    return simulated_return_c; } return 0;
}

void(external_mlinit(adtp::io_service * _this))
{
    std::cout << "Init" << std::endl;
    
}

void(external_mltick(adtp::io_service * _this))
{
   // std::cout << "Tick" << std::endl;
}

int(main())
{
    adtp::io_service io(
        &set_digit_pin_mode,
        &set_digit_pin_state,
        &get_digit_pin_state,
        &external_mlinit,
        &external_mltick
    );
}
