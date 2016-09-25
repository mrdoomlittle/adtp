# ifndef __dynamic__array__hpp__
# define __dynamic__array__hpp__

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

/* NOTE: this works the same way as the dynamic buffer but its more light wight
* and isent automatic and has no ids
*/

# ifdef ARDUINO
    # include <stdlib.h>
# else
    # include <boost/cstdlib.hpp>
# endif

namespace tmp { template <typename __darr_type> class dynamic_array
{
    public :
        void
        (darr_init (int unsigned(__darr_length), int unsigned(__darr_depth ) ) )
        {
            if ((this-> is_darr_init(true)) == true) return;
            if (__darr_length < 1) return;

            (this-> darr_length) = __darr_length;
            (this-> darr_depth) = __darr_depth;

            if (__darr_depth != 0)
                (this-> darr_ilayers [(data_id::__main)]) = new __darr_type [__darr_length * __darr_depth];

            (this-> toggle_darr_init());
        }

        void
        (set_darr_ilayer(__darr_type(* __ilayer_data), int unsigned(__layer_arr_pos), int unsigned(__ilayer_arr_pos)))
        {
            /* we might need to apply somthing to dected if this is not a independent var
            */
            (this-> darr_ilayers [(data_id::__main)] [(__layer_arr_pos * (this-> darr_length)) + __ilayer_arr_pos]) = *__ilayer_data;
        }

        __darr_type
        (* get_darr_ilayer(int unsigned(__layer_arr_pos), int unsigned(__ilayer_arr_pos)))
        {
            return (& (this-> darr_ilayers [(data_id::__main)] [(__layer_arr_pos * (this-> darr_length)) + __ilayer_arr_pos]));
        }

        void
        (set_darr_layer(__darr_type(* __layer_data), int unsigned(__layer_arr_pos)))
        {
            for (int unsigned(ilayer_arr_pos) = 0; ilayer_arr_pos != (this-> darr_length); ilayer_arr_pos ++)
                (this-> set_darr_ilayer((& __layer_data [ilayer_arr_pos]), __layer_arr_pos, ilayer_arr_pos));
        }

        __darr_type
        (* get_darr_layer(int unsigned(__layer_arr_pos)))
        {
            if ((this-> darr_layer_tmp) != nullptr )
            {
                std::free((this-> darr_layer_tmp));
                (this-> darr_layer_tmp) = nullptr;
            }

            (this-> darr_layer_tmp) = new __darr_type [(this-> darr_length)];

            for (int unsigned(ilayer_arr_pos ) = 0; ilayer_arr_pos != (this-> darr_length); ilayer_arr_pos ++)
                (this-> darr_layer_tmp [ilayer_arr_pos]) = *(this-> get_darr_ilayer (__layer_arr_pos, ilayer_arr_pos));


            return((this-> darr_layer_tmp));
        }

        // NOTE: add functions to resize the array
        void(resize_darr(int unsigned(__resize_type), int unsigned(__layer_arr_pos), int unsigned(__resize_to)))
        {
            switch(__resize_type)
            {
                case (resize_t::__single_layer) :
                    
                    break;
                case (resize_t::__all_layers) :
                    
                    if (__resize_to <= (this-> darr_length)) return;

                    (this-> darr_ilayers [(data_id::__swap)]) = new __darr_type [__resize_to * (this-> darr_depth)];

                    for (int unsigned(x ) = 0; x != ((this-> darr_length) * (this-> darr_depth)); x ++)
                        (this-> darr_ilayers [(data_id::__swap)] [x]) = (this-> darr_ilayers [(data_id::__main)] [x]);

                    std::free((this-> darr_ilayers [(data_id::__main)]));

                    (this-> darr_ilayers [(data_id::__main)]) = new __darr_type [__resize_to * (this-> darr_depth)];

                    for (int unsigned(x ) = 0; x != (__resize_to * (this-> darr_depth)); x ++)
                        (this-> darr_ilayers [(data_id::__main)] [x]) = (this-> darr_ilayers [(data_id::__swap)] [x]);

                    std::free((this-> darr_ilayers [(data_id::__swap)]));

                    (this-> darr_length ) = __resize_to;

                    break;
                default : return;
            }
        }

        void(add_darr_layer())
        {
            if ((this-> darr_depth) != 0)
            {
                (this-> darr_ilayers [(data_id::__swap)]) = new __darr_type [(this-> darr_length) * (this-> darr_depth)];

                for (int unsigned(x ) = 0; x != ((this-> darr_length) * (this-> darr_depth)); x ++)
                    (this-> darr_ilayers [(data_id::__swap)] [x]) = (this-> darr_ilayers [(data_id::__main)] [x]);

                std::free((this-> darr_ilayers [(data_id::__main)]));
            }
            
            if ((this-> darr_depth) == 0)
            {
                (this-> darr_depth) ++;

                (this-> darr_ilayers [(data_id::__main)]) = new __darr_type [(this-> darr_length) * (this-> darr_depth)];

                return;
            }

            if ((this-> darr_depth) != 0) 
            {
                for (int unsigned(x ) = 0; x != ((this-> darr_length) * (this-> darr_depth)); x ++)
                    (this-> darr_ilayers [(data_id::__main)] [x]) = (this-> darr_ilayers [(data_id::__swap)] [x]);

                std::free((this-> darr_ilayers [(data_id::__swap)]));
            }
        }

        int unsigned(get_darr_length())
        {
            return((this-> darr_length));
        }

        int unsigned(get_darr_depth())
        {
            return((this-> darr_depth));
        }

        dynamic_array() {}

        ~dynamic_array()
        {
            std::free(this-> darr_ilayers);
            std::free(this-> darr_layer_tmp);
        }

        void
        (toggle_darr_init())
        {
            (this-> has_darr_init ) = (this-> has_darr_init ) == true? false : true;
        }

        bool
        (is_darr_init(bool(__is_type)))
        {
            return (this-> has_darr_init ) == __is_type? true : false;
        }

    private :
        __darr_type(* darr_layer_tmp ) = nullptr;

        bool(has_darr_init ) = false;

        enum data_id : const int unsigned { __main = 0, __swap = 1 } ;
        enum resize_t : const int unsigned { __single_layer = 0, __all_layers = 1 };

        int unsigned(darr_length ) = 0;
        int unsigned(darr_depth ) = 0;
        __darr_type(* * darr_ilayers ) = new __darr_type * [2];
} ; }

# endif /*__dynamic__array__hpp__*/
