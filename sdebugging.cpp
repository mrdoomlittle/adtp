// doing debugging in the other makes it harder to debug
// as you change onething and many error/s appear


# include "interface.hpp"
# include "array.hpp"
# include <iostream>
int main()
{
    tmp::array <int> a(12, {2,5}, true);

    std::cout << a[0] << a[1] << std::endl;

    tmp::interface iface;
    tmp::array <uint8_t> dati(2, {0, 0}, true);
    tmp::array <uint8_t> dato(2, {0, 0}, true);
    iface.create_iface("192.168.0.100", dati, dato, 0, 0, 0, 0);
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
