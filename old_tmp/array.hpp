# ifndef __array__hpp__
# define __array__hpp__
# include "tmp_config.hpp"
# include <cstring>
# include <initializer_list>
// clean this up later
namespace tmp { template <typename __arr_t> class array
{
    public :
        array
        (int unsigned(__arr_length ), std::initializer_list <__arr_t> (__arr_data), bool(__preset_arr ) = false)
        {
            (this-> arr_data[0]) = new __arr_t [__arr_length];

            (this-> arr_length ) = __arr_length;

            if (__preset_arr == true)
                for (int unsigned(x ) = 0; x != (__arr_data.size( ) ); x ++)
                    (this-> arr_data[0] [x]) = *(__arr_data.begin( ) + x);
        }

        __arr_t &
        operator[] (int unsigned(__arr_pos ) )
        {
            return ( (this-> arr_data[0] [__arr_pos]) );
        }

        int unsigned
        (garr_len( ) )
        {
            return ((this-> arr_length));
        }

        void
        (resize_arr (int unsigned(__arr_size ) ) )
        {
            if (__arr_size <= (this-> arr_length) ) return;

            (this-> arr_data[1]) = new __arr_t [(this-> arr_length)];

            for (int unsigned(x ) = 0; x != (this-> arr_length); x ++)
                (this-> arr_data[1][x]) = (this-> arr_data[0][x]);

            //memcpy ( (this-> arr_data[1]), (this-> arr_data[0]), (this-> arr_length) );

            delete[] ( (this-> arr_data[0]) );

            (this-> arr_data[0]) = new __arr_t [__arr_size];

            for (int unsigned(x ) = 0; x != (this-> arr_length); x ++)
                (this-> arr_data[0][x]) = (this-> arr_data[1][x]);

            //memcpy ( (this-> arr_data[0]), (this-> arr_data[1]), (this-> arr_length) );

            delete[] ( (this-> arr_data[1]) );

            (this-> arr_length ) = __arr_size;
        }

        void
        del_from_arr (int unsigned(__arr_pos ) )
        {
            (this-> arr_data[1]) = new __arr_t [(this-> arr_length - 1)];

            int unsigned(r ) = 0;
            for (int unsigned(x ) = 0; x != (this-> arr_length); x ++)
            {
                if (x == __arr_pos) { r ++; continue; };
                (this-> arr_data[1] [(x-r)]) = (this-> arr_data[0]);
            }

            std::free ( (this-> arr_data[0]) );

            (this-> arr_length) --;

            (this-> arr_data [0]) = new __arr_t [(this-> arr_length)];

            memcpy ( (this-> arr_data[0]), (this-> arr_data[1]), (this-> arr_length) );

            std::free( (this-> arr_data[1]) );
        }
    public :
        __arr_t(* * arr_data ) = new __arr_t * [2];
        int unsigned(arr_length ) = 0;
} ; }

# endif /*__array__hpp__*/
