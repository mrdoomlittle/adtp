// doing debugging in the other makes it harder to debug
// as you change onething and many error/s appear


# include "interface.hpp"
# include "dynamic_array.hpp"
# include "pin_manager.hpp"
# include "array.hpp"
# include <iostream>
# include "dynamic_buffer.hpp"
int main()
{
    tmp::array <uint8_t> a(6 ,{}, false);
//    tmp::array <uint8_t>
    //(* _digit_dati_bitset ) = new tmp::array <uint8_t> (8, {}, false);

//    (*_digit_dati_bitset)[0] = 21;


    /*
    int unsigned o = 55;
    tmp::dynamic_buffer <int> hpp;

    hpp.dbuff_init(5,o,8);

    int x = 22;
    for (int unsigned(l ) = 0; l != o; l ++)
        for (int unsigned(y ) = 0; y != 8; y ++)
            hpp.add_to_dbuff(&x, 2, 0, 0, 0, false, true, true);


    for (int unsigned(l ) = 0; l != o; l ++)
        for (int unsigned(y ) = 0; y != 8; y ++)
            std::cout << *hpp.get_from_dbuff(2,0, l, y, false, false, false, false) << std::endl;




    tmp::pin_manager pmanager(5);

    (pmanager.set_max_digit_pid_range(22));
    (pmanager.set_min_digit_pid_range(2));

    tmp::interface iface;

    tmp::array <uint8_t> dati(2, {2, 3}, true);
    tmp::array <uint8_t> dato(2, {4, 5}, true);

    iface.create_iface("192.168.0.100", dati, dato, 6, 7, 8, 9);

    dati[0] = 6;
    dati[1] = 7;
    dato[0] = 8;
    dato[1] = 9;

    iface.create_iface("192.168.0.100", dati, dato, 10, 11, 12, 13);
    std::cout << iface.update_pmanager(&pmanager, 0) << std::endl;
    std::cout << iface.update_pmanager(&pmanager, 1) << std::endl;

*/

/*
    tmp::dynamic_array <char>dy;
    dy.darr_init(3, 0);
    dy.add_darr_layer();

    dy.resize_darr(0, 0, 44);

    dy.add_darr_layer();
    dy.resize_darr(0, 0, 21);


    char t = 'A';
    dy.set_darr_ilayer(&t, 0, 0);

    t = 'B';
    dy.set_darr_ilayer(&t, 0, 1);

    t ='C';
    dy.set_darr_ilayer(&t, 0, 2);


    t = 'D';
    dy.set_darr_ilayer(&t, 1, 0);

    t = 'E';
    dy.set_darr_ilayer(&t, 1, 1);

    t = 'F';
    dy.set_darr_ilayer(&t, 1, 2);

    std::cout << dy.get_darr_depth() << std::endl;

    for (int unsigned y = 0; y != dy.get_darr_depth(); y ++){
        for (int unsigned x = 0; x != dy.get_darr_length(y); x ++)
            std::cout << *dy.get_darr_ilayer(y, x);

        std::cout << std::endl;
    }*/


}

/*
tmp::dynamic_array <int unsigned>dy;
dy.darr_init(2, 0);
dy.add_darr_layer(3);
dy.add_darr_layer(3);



int unsigned t = 0;
dy.set_darr_ilayer(&t, 0, 0);
t = 1;
dy.set_darr_ilayer(&t, 0, 1);
t = 2;
dy.set_darr_ilayer(&t, 1, 0);
t = 3;
dy.set_darr_ilayer(&t, 1, 1);
t = 4;
dy.set_darr_ilayer(&t, 2, 0);
t = 5;
dy.set_darr_ilayer(&t, 2, 1);

dy.resize_darr(0, 0, 3);
//dy.resize_darr(0, 1, 4);
//t = 21;
//dy.set_darr_ilayer(&t, 0, 2);
dy.del_darr_layer(1);
dy.add_darr_layer(3);

for (int unsigned y = 0; y != dy.get_darr_depth(); y ++)
    for (int unsigned x = 0; x != dy.get_darr_length(y); x ++)
        std::cout << *dy.get_darr_ilayer(y, x) << std::endl;


//dy.set_darr_ilayer(&t, 2, 0);
*/
