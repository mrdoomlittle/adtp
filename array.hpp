# ifndef __array__hpp__
# define __array__hpp__
# include "tmp_config.hpp"
# include <initializer_list>
// clean this up later
namespace tmp {
    template <typename __arr_t>
        class array
        {
            public :
            array(int unsigned __size, std::initializer_list<__arr_t> p, bool preset = false)
            {

                arr = new __arr_t[__size];
                s = __size;

                if (preset)
                {
                    for (int unsigned x = 0; x != p.size(); x ++)
                    {
                        arr[x] = *(p.begin() + x);
                    }
                }
            }

            __arr_t& operator[](__arr_t x)
            {
                return(arr[x]);
            }

            int unsigned(size())
            {
                return(s);
            }
        private :
            __arr_t * arr;
            int unsigned s = 0;
        } ;
}

# endif /*__array__hpp__*/
