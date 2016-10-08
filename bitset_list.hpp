# ifndef __bitset__array__hpp__
# define __bitset__array__hpp__

# include "bitset.hpp"
# include "error.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

namespace tmp { template <typename __bitset_t> class bitset_list
{
    public :
        // REMINDER: change func name to  init_bitset_list and not bitset_init
        void
        (bitset_init(int unsigned(__length_of_ebitset ), int unsigned(__amount_of_bitsets), bool(__init_bitsets_now) = false ))
        {
            if ((this-> has_bitset_list_init) == true)
            {
                error_detection.add_error(0);
                return;
            }

            if (__length_of_ebitset == 0)
            {
                error_detection.add_error(0);
                return;
            }

            (this-> bitset_list) = new bitset <__bitset_t> * [2];

            if (__amount_of_bitsets != 0)
            {
                (this-> bitset_list[0]) = new bitset <__bitset_t> [__amount_of_bitsets];

                if (__init_bitsets_now == true)
                {
                    for (int unsigned(x ) = 0; x != __amount_of_bitsets; x ++)
                    {
                        (this-> bitset_list [0][x]).bitset_init(__length_of_ebitset);
                    }
                }
            }

            (this-> has_bitset_list_init ) = true;
            (this-> length_of_ebitset ) = __length_of_ebitset;
            (this-> amount_of_bitsets ) = __amount_of_bitsets;
        }

        bitset <__bitset_t> * get_bitset_cinst_ptr (int unsigned(__bitset_list_pos))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return (nullptr);
            }

            return (& (this-> bitset_list[0][__bitset_list_pos]) );
        }

        void
        (set_bitset(__bitset_t(* __bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos), int unsigned(__bitset_arr_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            (this-> bitset_list [0][__bitset_arr_pos]).set_bitset(__bitset, __set_type , __ibitset_arr_pos);
        }

        __bitset_t
        (* get_bitset(int unsigned(__get_type), int unsigned(__ibitset_list_pos), int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return (nullptr);
            }

            return((this-> bitset_list [0][__bitset_list_pos]).get_bitset(__get_type, __ibitset_list_pos));
        }

        void
        (shift_bitset(int unsigned(__shift_direction), int unsigned(__shift_amount), int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            (this-> bitset_list [0][__bitset_list_pos]).shift_bitset(__shift_direction, __shift_amount);
        }

        void
        (flip_bitset(int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            (this-> bitset_list [0][__bitset_list_pos]).flip_bitset();
        }

        void
        (add_bitset())
        {
            if (amount_of_bitsets != 0)
            {

                // this take memory up by *2 so might need to fix that
                (this-> bitset_list[1]) = new bitset <__bitset_t> [(this-> amount_of_bitsets)];

                for (int unsigned(x ) = 0; x != (this-> amount_of_bitsets); x ++)
                {
                    (this-> bitset_list[1][x]).bitset_init((this-> length_of_ebitset));
                    (this-> bitset_list[1][x]).set_bitset((this-> bitset_list [0][x]).get_bitset(1, x), 1, x);
                }

                delete[] (this-> bitset_list[0]);
            }

            if (amount_of_bitsets == 0)
            {
                (this-> bitset_list[0]) = new bitset <__bitset_t> [(this-> amount_of_bitsets) + 1];
                (this-> bitset_list[0][0]).bitset_init((this-> length_of_ebitset));
            }

            if (amount_of_bitsets != 0)
            {
                for (int unsigned(x ) = 0; x != (this-> amount_of_bitsets); x ++)
                {
                    (this-> bitset_list[0][x]).bitset_init((this-> length_of_ebitset));
                    (this-> bitset_list[0][x]).set_bitset((this-> bitset_list [1][x]).get_bitset(1, x), 1, x);
                }

                delete[] (this-> bitset_list [1]);
            }

            (this-> amount_of_bitsets) ++;
        }

        int unsigned
        (get_bitset_count())
        {
            return((this-> amount_of_bitsets));
        }

        // this will be change later
        bool(is_there_any_errors())
        {
            return ((this-> error_detection).is_everthing_ok == 1? false : true);
        }
    private :
        bool(has_bitset_list_init) = false;
        int unsigned(length_of_ebitset) = 0;
        int unsigned(amount_of_bitsets) = 0;

    private :
        bitset <__bitset_t> * * bitset_list;
        error error_detection;
} ; }

# endif /*__bitset__array__hpp__*/
