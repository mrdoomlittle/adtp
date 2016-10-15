# ifndef __array__hpp__
# define __array__hpp__
# include "tmp_config.hpp"
# include <initializer_list>
// clean this up later
namespace tmp { template <typename __arr_t> class array
{
    public :
        array (int unsigned(__arr_length ), std::initializer_list<__arr_t> __arr_data, bool(__preset_arr ) = false)
        {
            this-> arr_data = new __arr_t[__arr_length];

            this-> arr_length = __arr_length;

            if (__preset_arr)
                for (int unsigned x = 0; x != __arr_data.size( ); x ++)
                    (this-> arr_data[x]) = *(__arr_data.begin( ) + x);
        }

        __arr_t& operator[](int unsigned __arr_pos)
        {
            return ((this-> arr_data[__arr_pos]) );
        }

        int unsigned(glen())
        {
            return ((this-> arr_length));
        }
    private :
        __arr_t(* arr_data );
        int unsigned(arr_length ) = 0;
} ; }

# endif /*__array__hpp__*/
