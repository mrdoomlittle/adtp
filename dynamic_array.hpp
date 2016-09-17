# ifndef __dynamic__array__hpp__
# define __dynamic__array__hpp__

/* NOTE: this works the same way as the dynamic buffer but its more light wight
* and isent automatic and has no ids 
*/

# include <iostream>
namespace adtp { template <typename __darr_type> class dynamic_array
{
    public :
        void
        (darr_init (int unsigned(__darr_length), int unsigned(__darr_depth ) ) )
        {
            if ((this-> is_darr_init(true)) == true) return;
            if (__darr_length < 1 || __darr_depth < 1) return;

            (this-> darr_length) = __darr_length;
            (this-> darr_depth) = __darr_depth;

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

        int unsigned(darr_length ) = 0;
        int unsigned(darr_depth ) = 0;
        __darr_type(* * darr_ilayers ) = new __darr_type * [2];
} ; }

# endif /*__dynamic__array__hpp__*/
