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

            if (__length_of_ebitset == 0 && __init_bitsets_now == true)
            {
                error_detection.add_error(0);
                return;
            }

            if (__amount_of_bitsets != 0)
            {
                (this-> bitset_list) = new array <bitset <__bitset_t>*> (__amount_of_bitsets, {}, false);

                for (int unsigned(x ) = 0; x != __amount_of_bitsets; x ++)
                {
                    (*(this-> bitset_list)) [x] = new bitset <__bitset_t>;
                }

                if (__init_bitsets_now == true)
                {
                    for (int unsigned(x ) = 0; x != __amount_of_bitsets; x ++)
                    {
                        ((*(this-> bitset_list)) [x])-> bitset_init(__length_of_ebitset);
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

            return ( ((*(this-> bitset_list))[__bitset_list_pos]) );
        }

        void
        (set_bitset(__bitset_t(* __bitset), int unsigned(__set_type), int unsigned(__ibitset_arr_pos), int unsigned(__bitset_arr_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            ((*(this-> bitset_list))[__bitset_arr_pos])-> set_bitset(__bitset, __set_type , __ibitset_arr_pos);
        }

        __bitset_t
        (* get_bitset(int unsigned(__get_type), int unsigned(__ibitset_list_pos), int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return (nullptr);
            }

            return(((*(this-> bitset_list))[__bitset_list_pos])-> get_bitset(__get_type, __ibitset_list_pos));
        }

        void
        (shift_bitset(int unsigned(__shift_direction), int unsigned(__shift_amount), int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            ((*(this-> bitset_list))[__bitset_list_pos])-> shift_bitset(__shift_direction, __shift_amount);
        }

        void
        (flip_bitset(int unsigned(__bitset_list_pos)))
        {
            if ((this-> has_bitset_list_init) == false)
            {
                error_detection.add_error(0);
                return;
            }

            ((*(this-> bitset_list))[__bitset_list_pos])-> flip_bitset();
        }

        void
        (add_bitset())
        {
            (this-> amount_of_bitsets) ++;

            (this-> bitset_list)-> resize_arr((this-> amount_of_bitsets));

            //(this-> bitset_list).arr_data[0][0].get_bitset_length();

            (*(this-> bitset_list)) [(this-> amount_of_bitsets)-1] = new bitset <__bitset_t>;

            (*(this-> bitset_list)) [(this-> amount_of_bitsets)-1]-> bitset_init((this-> length_of_ebitset));


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

        array <bitset <__bitset_t>*> * bitset_list;

        error error_detection;
} ; }

# endif /*__bitset__array__hpp__*/
