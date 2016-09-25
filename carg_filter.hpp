# ifndef __carg__filter__hpp__
# define __carg__filter__hpp__
/*this code is from another one of my projects i will get this working the next day*/

# ifndef ARDUINO
    # include <boost/cstdint.hpp>
# else
    # include <stdint.h>
# endif

namespace tmp { class carg_filter
{
    private :
        char const (* char_list_in ) = nullptr;
        const char (* * char_list_out ) = nullptr;
        char const (* separator_char ) = nullptr;

        size_t (char_list_length ) = 0;

        // we way to check where the separator is located
        // example : ["Hello,All"] = [0,0,0,0,0,1,0,0,0]
        bool (* separator_mapping ) = nullptr;

        size_t (sub_counter ) = 0;

        size_t (* sub_list_size ) = nullptr;

        bool (is_sub_counted ) = false;
        bool (got_sub_size ) = false;

        size_t (* sub_start_point ) = nullptr;

        size_t (sub_point_change ) = 0;

        char (* * temp_out_list ) = nullptr;

    public :
        char const (* * filter_list_in (char const (* _char_list_in ) = nullptr,
        char const (* _separator_char ) = nullptr, size_t (_char_list_length ) = 0) ) ;

        void (set_list_length (size_t (_char_list_length ) = 0 ) );
        size_t (get_list_length( ) );

        void (set_list_in (char const (* _char_list_in ) = nullptr) );
        char const (* get_list_in( ) );

        void (set_list_out (char const (* * _char_list_out ) = nullptr) );
        char const (* * get_list_out( ) );

        void (set_separator (char const (* separator_char ) = nullptr) );
        char const (* get_separator( ) );

        size_t (get_sub_counter( ) );
        size_t (* get_sub_list_size( ) );
} ; }

# endif /*__carg__filter__hpp__*/
