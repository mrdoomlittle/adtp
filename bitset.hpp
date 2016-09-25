# ifndef __bitset__hpp__
# define __bitset__hpp__

# include "dynamic_array.hpp"

namespace tmp { template <typename __bitset_type> class bitset
{
    public :
        void
        (bitset_init (int unsigned(__bitset_length )))
        {
            if (__bitset_length < 1) return;

            (this-> bitset_length) = __bitset_length;

            /* if we shift right or left we dont want to lose the data
            * example :
            * [bitset_left] [bitset_list] [bitset_right]
            */
            (this-> bitset_right).darr_init(__bitset_length, 1/*depth of array*/);
            (this-> bitset_left).darr_init(__bitset_length, 1/*depth of array*/);

            (this-> bitset_temp).darr_init(__bitset_length, 1/*depth of array*/);
            (this-> bitset_list).darr_init(__bitset_length, 1/*depth of array*/);
        }

        void
        (set_bitset(__bitset_type(* __bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos)))
        {
            switch(__set_type)
            {
                case (sg_type::__individual):
                    (this-> bitset_list).set_darr_ilayer(__bitset, 0, __ibitset_arr_pos);
                break;

                case (sg_type::__total_array):
                    for (int unsigned(x ) = 0; x != (this-> bitset_length); x ++)
                        (this-> set_bitset(&__bitset[x], (sg_type::__individual), x));
                break;

                default : break;
            }
        }

        __bitset_type
        (* get_bitset(int unsigned(__get_type), int unsigned(__ibitset_arr_pos)))
        {
            switch(__get_type)
            {
                case (sg_type::__individual):
                    return ((this-> bitset_list).get_darr_ilayer(0, __ibitset_arr_pos));
                break;

                case (sg_type::__total_array):
                    return ((this-> bitset_list).get_darr_layer(0));
                break;

                default : return (nullptr);
            }
        }

        void
        (shift_bitset(int unsigned(__shift_direction), int unsigned(__shift_amount) ))
        {
            switch (__shift_direction)
            {
                case (shift_direction::__right):
                    for (int unsigned (y ) = 0; y != __shift_amount; y ++)
                    {
                        (this-> bitset_right).set_darr_ilayer((this-> bitset_list).get_darr_ilayer(0, (((this-> bitset_length) - __shift_amount) + y)), 0, y);

                        __bitset_type temp = 0;
                        (this-> bitset_list).set_darr_ilayer(&temp, 0, (((this-> bitset_length) - __shift_amount) + y));
                    }

                    for (int unsigned (x ) = (this-> bitset_length)-1; x != __shift_amount-1; x --)
                        (this-> bitset_list).set_darr_ilayer((this-> bitset_list).get_darr_ilayer(0, (x - __shift_amount)), 0, x);

                    for (int unsigned (y ) = 0; y != __shift_amount; y ++)
                        (this-> bitset_list).set_darr_ilayer((this-> bitset_left).get_darr_ilayer(0, (((this-> bitset_length) - __shift_amount) + y)), 0, y);
                break;

                case (shift_direction::__left):
                    for (int unsigned (y ) = 0; y != __shift_amount; y ++)
                    {
                        (this-> bitset_left).set_darr_ilayer((this-> bitset_list).get_darr_ilayer(0, y), 0, (((this-> bitset_length) - __shift_amount) + y) );

                        __bitset_type temp = 0;
                        (this-> bitset_list).set_darr_ilayer(&temp, 0, y);
                    }

                    for (int unsigned (x ) = 0; x != (this-> bitset_length) - __shift_amount; x ++)
                        (this-> bitset_list).set_darr_ilayer((this-> bitset_list).get_darr_ilayer(0, (x + __shift_amount)), 0, x);

                    for (int unsigned (y ) = (this-> bitset_length) - __shift_amount; y != (this-> bitset_length); y ++)
                        (this-> bitset_list).set_darr_ilayer((this-> bitset_right).get_darr_ilayer(0, ((this-> bitset_length) - y)), 0, y);

                break;

                default : return;
            }
        }

        void
        (flip_bitset( ) )
        {
            for (int unsigned(x ) = 0; x != (this-> bitset_length); x++)
                 (this-> bitset_temp).set_darr_ilayer((this-> bitset_list).get_darr_ilayer(0, x), 0, x);

            for (int unsigned(x ) = 0; x != ((this-> bitset_length)); x++)
                (this-> bitset_list).set_darr_ilayer((this-> bitset_temp).get_darr_ilayer(0, ((this-> bitset_length - 1) - x)), 0, x);
        }

    private :
        enum sg_type : int unsigned { __individual = 0, __total_array = 1 } ;
        enum shift_direction : int unsigned { __right = 0, __left = 1 };

        int unsigned(bitset_length) = 0;;

        int unsigned(max_right_shift) = 0;
        int unsigned(max_left_shift) = 0;

        dynamic_array <__bitset_type> bitset_right;
        dynamic_array <__bitset_type> bitset_left;
        dynamic_array <__bitset_type> bitset_temp;
        dynamic_array <__bitset_type> bitset_list;
} ; }

# endif /*__bitset__hpp__*/
