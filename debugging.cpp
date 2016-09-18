# ifndef ARDUINO

# include "io_service.hpp"

# include <boost/cstdint.hpp>

# include "bitset.hpp"

# include <iostream>

# include "dynamic_array.hpp"

void
(set_digit_pin_mode (uint8_t (__pin_id ), uint8_t (__pin_mode ) ) ) { }

int unsigned soc = 0;
uint8_t sim_output[8][8];
int unsigned pins_call_count = 0;
void
(set_digit_pin_state (uint8_t (__pin_id ), uint8_t (__pin_state ) ) )
{
    //std::cout << "###############################################################" << std::endl;
    if (pins_call_count == 7)
    {
        if (soc == 7)
        {
            std::cout << "###############################################################" << std::endl;
            for(int unsigned x = 0; x != 8; x++)
            {
                for(int unsigned y = 0; y != 8; y++)
                    std::cout << unsigned(sim_output[x][y]);
                std::cout << std::endl;
            }
            soc = 0;
        }
        else
            soc ++;
        pins_call_count = 0;
    }
    else
    {
        sim_output[soc][pins_call_count] = __pin_state;
        pins_call_count ++; 
    }
}

int unsigned(simulated_pin_state_i [3] [8]) = {
    {0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1}, {0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1}/*, {0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1} */} ;

int unsigned(simulated_pin_state_c [10]) = {0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1} ;

int unsigned(simulated_return_i ) = 0;
int unsigned(current_pin_pos_i ) = 0;
int unsigned(current_arr_pos ) = 0;

int unsigned(simulated_return_c ) = 0;
int unsigned(current_pin_pos_c ) = 0;

int
(get_digit_pin_state (uint8_t(__pin_id ) ) )
{
    if (__pin_id == 2 || __pin_id == 3)
    {
        simulated_return_i = (simulated_pin_state_i [current_arr_pos] [current_pin_pos_i]);

        if (current_pin_pos_i == 7)
        {
            current_pin_pos_i = 0;
            if (current_arr_pos == 2)
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

int unsigned tcount = 0;
int unsigned ltime = 1;
int unsigned pos = 0;
uint8_t test[8][8] = 
{
    {0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0},
};

void
(external_mlinit (adtp::io_service(* _this ) ) )
{

}

void
(external_mltick (adtp::io_service(* _this ) ) )
{
    
        std::cout << "SET_IO_BITSET" << std::endl;
        _this-> set_io_bitset(1, test[pos], 1, 0);
        tcount = 0;
        if (pos == 7)
            pos = 0;
        else
            pos ++;
    
    for (int unsigned (x ) = 0; x != 8; x ++)
        std::cout << unsigned(* _this-> get_io_bitset(0, 0, x));


    std::cout << "/I::BITSET\n" << std::endl;

    for (int unsigned (x ) = 0; x != 8; x ++)
        std::cout << unsigned(* _this-> get_io_bitset(1, 0, x));

    std::cout << "/O::BITSET\n" << std::endl;

    for (int unsigned(x ) = 0; x != 8; x ++)
    {
        for (int unsigned(y ) = 0; y != 8; y ++)
            std::cout << unsigned(*_this-> i_bitset_buffer.get_from_dbuff(2, 0, x, y, false, false, false, true));
       
        if (_this-> i_bitset_buffer.is_block_smarker(true, 0, x) == true)
            std::cout << " & SM: " << "USED";
        else
            std::cout << " & SM: " << "FREE";
 
        std::cout << " : : ";

        for (int unsigned(y ) = 0; y != 8; y ++)
            std::cout << unsigned(*_this-> o_bitset_buffer.get_from_dbuff(2, 0, x, y, false, false, false, true));

        if (_this-> o_bitset_buffer.is_block_smarker(true, 0, x) == true)
            std::cout << " & SM: " << "USED";
        else
            std::cout << " & SM: " << "FREE";

        if (_this -> o_bitset_buff_pos[0] == x)
        {
            std::cout << " : BPOS<>";
        }

        std::cout << std::endl;
    }
    tcount++;
}

int
(main( ) )
{
    adtp::io_service io_service
    (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & external_mlinit,
        & external_mltick 
    );
}

# endif /*ARDUINO*/
