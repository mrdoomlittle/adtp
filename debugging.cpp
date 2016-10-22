# ifndef ARDUINO

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

# include "io_service.hpp"

# include <boost/cstdint.hpp>

# include "bitset.hpp"

# include <iostream>

# include "dynamic_array.hpp"
# include "tmp_config.hpp"

void
(set_digit_pin_mode (uint8_t (__digit_pid ), uint8_t (__digit_pmode ) ) ) { }

int unsigned inner_call_count = 0;
uint8_t output_buffer[8][8];
int unsigned set_call_count = 0;
bool o_buffer_finished = false;

void
(set_digit_pin_state (uint8_t (__digit_pid ), uint8_t (__digit_pstate ) ) )
{
    if (__digit_pid == 4 || __digit_pid == 5)
    {
        if (set_call_count == 8)
        {
            if (inner_call_count == 7)
            {
                o_buffer_finished = true;
                inner_call_count = 0;
            }
            else inner_call_count ++;

            set_call_count = 0;
        }

        output_buffer[inner_call_count][set_call_count] = __digit_pstate;
        set_call_count ++;
    }

    if (__digit_pid == 9 && __digit_pstate == 0x1)
    {
        std::cout << "SCC: " << set_call_count << ", ICC: " << inner_call_count << std::endl;
        for (int unsigned y = 0; y != 8; y ++)
        {
            std::cout << "OBITSET( ID: " << y << " ): ";
            for (int unsigned x = 0; x != 8; x ++)
            {
                std::cout << unsigned(output_buffer[y][x]);
            }
            std::cout << std::endl;
        }
        o_buffer_finished = false;
    }
}

#include <chrono>
#include <ctime>
// NOTE: add somthing so i can check if a int is null
int unsigned long (get_high_res_clock (int unsigned(__time_format) ) )
{
    if (__time_format == (tmp_config::time_format::__nano_seconds) )
    {
        auto hrc_now = std::chrono::high_resolution_clock::now( );

        auto nano_seconds = std::chrono::duration_cast <std::chrono::nanoseconds> (hrc_now.time_since_epoch( ) ).count( );

        return(nano_seconds);
    }
    return 0;
}
// clean this up and use the dynamic_array.hpp or just array.hpp
int unsigned(simulated_pin_state_i [3] [8]) = {
    {0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1},
    {0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1} } ;

int unsigned(simulated_pin_state_c [10]) = {0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1} ;

int unsigned(simulated_return_i ) = 0;
int unsigned(current_pin_pos_i ) = 0;
int unsigned(current_arr_pos ) = 0;

int unsigned(simulated_return_c ) = 0;
int unsigned(current_pin_pos_c ) = 0;


int unsigned tttt [4] = {0x1, 0x0, 0x1, 0x0};
int unsigned xcc = 0;
int unsigned out = 0;

bool ddodhjiu = false;

int
(get_digit_pin_state (uint8_t(__digit_pid ) ) )
{
    if (__digit_pid == 2 || __digit_pid == 3)
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

    if (__digit_pid == 10)
    {
        simulated_return_c = (simulated_pin_state_c [current_pin_pos_c]);
        if (current_pin_pos_c == 9)
            current_pin_pos_c = 0;
        else
            current_pin_pos_c ++;
        return simulated_return_c;
    }

    if (__digit_pid == 6)
    {
        ddodhjiu = ddodhjiu == false? true : false;

        return 0x0;
    }

    if (__digit_pid == 7 )
    {
        out = tttt[xcc];
        if (xcc == 3)
        {
            xcc = 0;
        } else xcc ++;

        return (out);
    }

    return(0);
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
# include "bitset.hpp"
tmp::bitset <uint8_t> obs;
tmp::dynamic_array <uint8_t> overf;
int unsigned overf_count = 0;
void overflow (int unsigned(iface_id), tmp::bitset <uint8_t> (* __bitset))
{
    overf.add_darr_layer();
    std::cout << "Overflow DUMP: \n";
    for (int unsigned x = 0; x != __bitset-> get_bitset_length(); x ++)
        overf.set_darr_ilayer(__bitset-> get_bitset(0, x), overf_count, x);

    for (int unsigned y = 0; y != overf_count; y ++) {
        for (int unsigned x = 0; x != __bitset-> get_bitset_length(); x ++)
            std::cout << unsigned(*overf.get_darr_ilayer(y, x));
        std::cout << "\n";
    }
    std::cout << "\n";
    overf_count ++;
}

int unsigned
(external_mlinit (tmp::io_service(* __io_service ) ) )
{
    overf.darr_init(8, 0);
    obs.bitset_init(8);
    __io_service-> set_dato_bstream_buff_offunc_ptr(&overflow);
    std::cout << "This Project is Still Early Development and Many things Need Fixing. Sorry :(" << std::endl;

    return 0;
}
# include "bitset.hpp"
uint8_t bitset_c[8] = {1, 0, 0, 1, 0, 0, 0, 1};
uint8_t bitset_a[8] = {0, 1, 1, 0, 1, 1, 1, 0};
uint8_t c = false;


int unsigned
(external_mltick (tmp::io_service(* __io_service ) ) )
{
    //uint8_t *test = __io_service-> get_from_dato_bytestream(0).get_bitset(1, 0);

    //for (int unsigned(x ) = 0; x != 8; x ++)
        //std::cout << unsigned(test[x]);
    //std::cout << "\n";

    for (int unsigned iface = 0; iface != (__io_service-> get_interface_cinst_ptr()-> get_iface_count()); iface ++)
    {
        if (__io_service-> is_dato_bstream_buff_full() == false)
        {
            if (c == false) {
            obs.set_bitset(bitset_c, 1, 0);
            __io_service-> add_to_dato_bytestream(iface, &obs);}
            if (c == true) {
            obs.set_bitset(bitset_a, 1, 0);
            __io_service-> add_to_dato_bytestream(iface, &obs);}

            c = c == false? true : false;
        }

        if ((__io_service-> get_interface_cinst_ptr()-> is_iface_pmanager_state(1/*__doesent_exist*/, iface))) continue;

        std::cout << "\nINTERFACE_ID: " << iface << std::endl;

        std::cout << "  ";
        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned((*(__io_service-> digit_dati_bitbuff))[x]);

        std::cout << ", O::BITBUFF, ";
        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned((*(__io_service-> digit_dato_bitbuff))[x]);

        std::cout << ", O::BITBUFF";

        std::cout << std::endl;

        std::cout << "  ";
        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned((*(__io_service-> digit_dati_bitset))[x]);

        std::cout << ", I::BITSET" << ", ";

        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned((*(__io_service-> digit_dato_bitset))[x]);

        std::cout << ", O::BITSET\n\n";

        std::cout << "  ";
        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned(* __io_service-> get_io_bitset(iface, (tmp_config::io_t::__itype), 0, x));

        std::cout << ", IO::I::BITSET" << ", ";

        for (int unsigned(x ) = 0; x != 8; x ++)
            std::cout << unsigned(* __io_service-> get_io_bitset(iface,  (tmp_config::io_t::__otype), 0, x));

        std::cout << ", IO::O::BITSET\n\n";
        std::cout << "  ";

        std::cout << "  ";
        std::cout << "\nBYTE_STREAMBUFF\n";

        for (int unsigned(x ) = 0; x != (__io_service-> dati_bytestream_bsize) + (__io_service-> dato_bytestream_bsize); x ++)
        {
            std::cout << "  ";
            if (x < (__io_service-> dati_bytestream_bsize)) {

                for (int unsigned(y ) = 0; y != 8; y ++)
                    std::cout << unsigned(*__io_service-> dati_bytestream_buff.get_from_dbuff(2, iface, x, y, false, false, false, true));

                if (x >= (__io_service-> dato_bytestream_bsize)) {

                    std::cout << std::endl;
                }

                if ((__io_service-> dati_bytestream_buff).is_block_smarker(true, iface, x) == true)
                    std::cout << ", SM: " << "USED, ";
                else
                    std::cout << ", SM: " << "FREE, ";

                if (__io_service-> dati_bytestream_bpos[0] == x)
                    std::cout << "SG_POS: X:";
                else
                    std::cout << "SG_POS: O:";

                if (__io_service-> dati_bytestream_bpos[1] == x)
                    std::cout << "X : : ";
                else
                    std::cout << "O : : ";
            }

            if (x < (__io_service-> dato_bytestream_bsize)) {
                for (int unsigned(y ) = 0; y != 8; y ++)
                    std::cout << unsigned(*__io_service-> dato_bytestream_buff.get_from_dbuff(2, iface, x, y, false, false, false, true));

                if ((__io_service-> dato_bytestream_buff).is_block_smarker(true, iface, x) == true)
                    std::cout << ", SM: " << "USED,";
                else
                    std::cout << ", SM: " << "FREE,";

                if (__io_service-> dato_bytestream_bpos[0] == x)
                    std::cout << " SG_POS: X:";
                else
                    std::cout << " SG_POS: O:";
                if (__io_service-> dato_bytestream_bpos[1] == x)
                    std::cout << "X, ";
                else
                    std::cout << "O, ";

                std::cout << std::endl;
            }


        }
        std::cout << std::endl;
        std::cout << "  I::BYTE_STREAMBUFF / SUSED: " << __io_service-> dati_bytestream_buff.get_sector_used_c(iface) << ", SFREE: " <<  __io_service-> dati_bytestream_buff.get_sector_free_c(iface) << std::endl;
        std::cout << "  O::BYTE_STREAMBUFF / SUSED: " << __io_service-> dato_bytestream_buff.get_sector_used_c(iface) << ", SFREE: " <<  __io_service-> dato_bytestream_buff.get_sector_free_c(iface) << std::endl;

        std::cout << std::endl;

        std::cout << "BITSET_BUFF\n";
        for (int unsigned(x ) = 0; x != (__io_service-> dati_bitset_buff_size) + (__io_service-> dato_bitset_buff_size); x ++)
        {
            if (x < (__io_service-> dati_bitset_buff_size)) {
            std::cout << "  ";
            for (int unsigned(y ) = 0; y != 8; y ++)
                std::cout << unsigned(*__io_service-> dati_bitset_buff.get_from_dbuff(2, iface, x, y, false, false, false, true));

            if ((__io_service-> dati_bitset_buff).is_block_smarker(true, iface, x) == true)
                std::cout << ", SM: " << "USED,";
            else
                std::cout << ", SM: " << "FREE,";

            if (__io_service -> dati_bitset_buff_pos[0] == x)
                std::cout << " SG_POS: X:";
            else
                std::cout << " SG_POS: O:";
            if (__io_service -> dati_bitset_buff_pos[1] == x)
                std::cout << "X";
            else
                std::cout << "O";
            std::cout << " : : ";

            if (x >= (__io_service-> dato_bitset_buff_size)) {
                std::cout << std::endl;
            }
            }

            if (x < (__io_service-> dato_bitset_buff_size)) {
            for (int unsigned(y ) = 0; y != 8; y ++)
                std::cout << unsigned(*__io_service-> dato_bitset_buff.get_from_dbuff(2, iface, x, y, false, false, false, true));

            if (__io_service-> dato_bitset_buff.is_block_smarker(true, iface, x) == true)
                std::cout << ", SM: " << "USED";
            else
                std::cout << ", SM: " << "FREE";

            if (__io_service -> dato_bitset_buff_pos[0] == x)
                std::cout << ", SG_POS: X:";
            else
                std::cout << ", SG_POS: O:";
            if (__io_service -> dato_bitset_buff_pos[1] == x)
                std::cout << "X";
            else
                std::cout << "O";
            std::cout << std::endl;
            }


        }
        std::cout << std::endl;
        std::cout << "  I::BITSET_BUFF / SUSED: " << __io_service-> dati_bitset_buff.get_sector_used_c(iface) << ", SFREE: " <<  __io_service-> dati_bitset_buff.get_sector_free_c(iface) << std::endl;
        std::cout << "  O::BITSET_BUFF / SUSED: " << __io_service-> dato_bitset_buff.get_sector_used_c(iface) << ", SFREE: " <<  __io_service-> dato_bitset_buff.get_sector_free_c(iface) << std::endl;
    }

    return 1;
}
# include "array.hpp"
int
(main( ) )
{

    tmp::io_service __io_service;
    __io_service.service_init
    (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & get_high_res_clock,
        & external_mlinit,
        & external_mltick
    );
}

# endif /*ARDUINO*/
