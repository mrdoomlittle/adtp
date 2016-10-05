# ifndef __dpacket__array__hpp__
# define __dpacket__array__hpp__
# include "data_packet.hpp"


// need to work on this more and test it as i speed coded it
// so there might be alot of problems + might need to fix
// the add_packet func as i dont know if it works i was going
// to delete it and reinit it with the data from the other
// but i will test it later 
// this requires cleaning up and renaming vars
namespace tmp { class dpacket_array
{
    public :
        void (init_dpacket_array(int unsigned(__array_size)))
        {
            (this-> array_size) = __array_size;

            if (__array_size != 0)
                (this-> dpacket[(this-> __main)]) = new data_packet [__array_size]; 
        }

        void (add_dpacket())
        {
            if ((this-> array_size) == 0)
            {
                (this-> dpacket[(this-> __main)]) = new data_packet [this-> array_size+1];

                (this-> array_size) ++;
            }
    
            if ((this-> array_size) != 0)
            {
                (this-> dpacket[(this-> __swap)]) = new data_packet [this-> array_size+1];

                for(int unsigned(x) = 0; x != (this-> array_size); x ++)
                {
                    (this-> dpacket[(this-> __swap)][x]) = (this-> dpacket[(this-> __main)][x]);
                    //(this-> dpacket[(this-> __main)][x]) = nullptr; // this is only hear as i dont know if delete [] will deinitlize the classes inside            
                }

                delete[] (this-> dpacket[(this-> __main)]);

                (this-> dpacket[(this-> __main)]) = new data_packet [this-> array_size+1];

                for(int unsigned(x) = 0; x != (this-> array_size); x ++)
                {
                    (this-> dpacket[(this-> __main)][x]) = (this-> dpacket[(this-> __swap)][x]);
                
                    //(this-> dpacket[(this-> __swap)][x]) = nullptr;
                }

                delete[] (this-> dpacket[(this-> __swap)]);

                (this-> array_size) ++;
            }
        }

        int unsigned(get_dparray_size())
        {
            return((this-> array_size));
        }

        data_packet (* get_dpacket_ptr(int unsigned(__arr_pos)))
        {
            return (&(this-> dpacket[(this-> __main)][__arr_pos]));
        } 

    private :

        int unsigned(array_size) = 0;

        enum : int unsigned const
        {
            __swap,
            __main
        };

        data_packet * dpacket[2];

} ; }

# endif /*__dpacket__array__hpp__*/
