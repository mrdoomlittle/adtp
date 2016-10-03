# ifndef __bitset__array__hpp__
# define __bitset__array__hpp__

# include "bitset.hpp"

namespace tmp { template <typename __bitset_type> class bitset_array
{
    public :
        void
        (bitset_init(int unsigned(__bitset_length ), int unsigned(__bitset_depth)))
        {
            if (__bitset_depth != 0)
            {
            (this-> bitset_array) = new bitset <__bitset_type> [__bitset_depth];
            //(this-> bitset_array).darr_init(__bitset_depth, 0);
            for (int unsigned(x ) = 0; x != __bitset_depth; x ++)
            {
               (this-> bitset_array [x]).bitset_init(__bitset_length); 
            }
            }

            (this-> bitset_length) = __bitset_length;
            (this-> bitset_depth) = __bitset_depth;
        }
    
        void
        (set_bitset(__bitset_type(* __bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos), int unsigned(__bitset_arr_pos)))
        {
            (this-> bitset_array [__bitset_arr_pos]).set_bitset(__bitset, __set_type , __ibitset_arr_pos); 
        }

        __bitset_type
        (* get_bitset(int unsigned(__get_type), int unsigned(__ibitset_arr_pos), int unsigned(__bitset_arr_pos)))
        {
            return((this-> bitset_array [__bitset_arr_pos]).get_bitset(__get_type, __ibitset_arr_pos));
        }
   
        void
        (shift_bitset(int unsigned(__shift_direction), int unsigned(__shift_amount), int unsigned(__bitset_arr_pos)))
        {
            (this-> bitset_array [__bitset_arr_pos]).shift_bitset(__shift_direction, __shift_amount);
        }

        void
        (flip_bitset(int unsigned(__bitset_arr_pos)))
        {
            (this-> bitset_array [__bitset_arr_pos]).flip_bitset();
        } 

        void
        (add_bitset())
        {
            if (bitset_depth != 0) {
            // this take memory up by *2 so might need to fix that
            (this-> bitset_array_swp) = new bitset <__bitset_type> [(this-> bitset_depth)];
            for (int unsigned(x ) = 0; x != (this-> bitset_depth); x ++)
            {
               (this-> bitset_array_swp [x]).bitset_init((this-> bitset_length));
               (this-> bitset_array_swp [x]).set_bitset((this-> bitset_array [x]).get_bitset(1, x), 1, x);
            } 

            delete[] (this-> bitset_array); 
            }

            if (bitset_depth == 0)
            {
                (this-> bitset_array) = new bitset <__bitset_type> [(this-> bitset_depth) + 1];
                (this-> bitset_array [0]).bitset_init((this-> bitset_length));
            }
            if (bitset_depth != 0) {
            for (int unsigned(x ) = 0; x != (this-> bitset_depth); x ++)
            {
                (this-> bitset_array [x]).bitset_init((this-> bitset_length));
                (this-> bitset_array [x]).set_bitset((this-> bitset_array_swp [x]).get_bitset(1, x), 1, x);
            }

            delete[] (this-> bitset_array_swp);
            }
            (this-> bitset_depth)++;
        }

        int unsigned
        (get_bitset_depth())
        {
            return((this-> bitset_depth));
        }
    private :
        int unsigned(bitset_length) = 0;
        int unsigned(bitset_depth) = 0;

    private :
        bitset <__bitset_type> * bitset_array;
        bitset <__bitset_type> * bitset_array_swp;
} ; }

# endif /*__bitset__array__hpp__*/
