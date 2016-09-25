/*this code is from another one of my projects i will get this working the next day*/
# include "carg_filter.hpp"
namespace itmp {
char const (* * carg_filter::filter_list_in (char const (* _char_list_in ),
    char const (* _separator_char ), size_t (_char_list_length ) ) )
{
    if (_char_list_in != nullptr && (this-> char_list_in ) == nullptr )
          (this-> char_list_in ) = _char_list_in;

    if (_separator_char != nullptr && (this-> separator_char ) == nullptr )
        (this-> separator_char ) = _separator_char;

    if (_char_list_length > 1 && (this-> char_list_length ) < 1 )
        (this-> char_list_length ) = _char_list_length;

    if ((this-> char_list_in ) == nullptr || (this-> separator_char ) == nullptr) return (nullptr );

    if ( (this-> char_list_length ) < 1 ) return (nullptr );

    (this-> separator_mapping ) = new bool [(this-> char_list_length ) ];

    for (size_t (list_pos ) = 0; list_pos != (this-> char_list_length); list_pos ++)
    {
        if ((this-> char_list_in [list_pos ]) == (this-> separator_char [0]) )
            (this-> separator_mapping [list_pos]) = true;

        if ((this-> char_list_in [list_pos ]) != (this-> separator_char [0]) )
            (this-> separator_mapping [list_pos]) = false;
    }

    for (size_t (list_pos ) = 0; list_pos != (this-> char_list_length ) + 1; list_pos ++)
    {
        if (list_pos == (this-> char_list_length ) )
        {
            if ( (this-> is_sub_counted ) == true && (this-> got_sub_size ) == true )
            {

                for (size_t (sub_list_pos ) = 0; sub_list_pos != (this-> sub_counter ); sub_list_pos ++)
                    for (size_t (list_pos ) = 0; list_pos != (this-> sub_list_size [sub_list_pos ] ); list_pos ++)
                        (this-> temp_out_list [sub_list_pos ] [list_pos ] ) = (this-> char_list_in [ (list_pos + (this-> sub_start_point [sub_list_pos ]))] );

                break;
            }

            if ( (this-> is_sub_counted ) == true && (this-> got_sub_size ) == false )
            {
                (this-> got_sub_size ) = true;
                for (size_t (sub_list_pos ) = 0; sub_list_pos != (this-> sub_counter ); sub_list_pos ++)
                    (this-> temp_out_list [sub_list_pos ] ) = new char [(this-> sub_list_size [sub_list_pos ] ) ];
            }

            if ( (this-> is_sub_counted ) == false )
            {
                (this-> is_sub_counted ) = true;
                (this-> sub_list_size ) = new size_t [(this-> sub_counter ) ];
                (this-> sub_start_point ) = new size_t [(this-> sub_counter ) ];
                (this-> temp_out_list ) = new char * [(this-> sub_counter ) ];
            }

            list_pos = 0;
        }

        if ( (this-> separator_mapping [list_pos ] ) == false && list_pos == 0 )
        {
            if ( (this-> is_sub_counted ) == false ) (this-> sub_counter ) ++;

            if ( (this-> is_sub_counted ) == true && (this-> got_sub_size ) == false )
            {
                (this-> sub_start_point [(this-> sub_point_change ) ] ) = list_pos;
                for (size_t (sub_list_pos ) = list_pos; sub_list_pos != (this-> char_list_length ); sub_list_pos ++)
                {
                    if ((this-> separator_mapping [sub_list_pos ] ) == false ) (this-> sub_list_size [(this-> sub_point_change) ] ) ++;
                    else break;
                }

                (this-> sub_point_change ) ++;
            }
        }

        if ( (this-> separator_mapping [list_pos ] ) == true )
        {
            if ( (this-> is_sub_counted ) == false ) (this-> sub_counter ) ++;

            if ( (this-> is_sub_counted ) == true && (this-> got_sub_size ) == false )
            {
                (this-> sub_start_point [(this-> sub_point_change ) ] ) = list_pos + 1;
                for (size_t (sub_list_pos ) = (list_pos + 1); sub_list_pos != (this-> char_list_length ); sub_list_pos ++)
                {
                    if ((this-> separator_mapping [sub_list_pos ] ) == false ) (this-> sub_list_size [(this-> sub_point_change) ] ) ++;
                    else break;
                }

                (this-> sub_point_change ) ++;
            }
        }
    }

    (this-> char_list_out ) = const_cast <const char * *> (this-> temp_out_list );

    return (this-> char_list_out );
}

size_t (carg_filter::get_sub_counter( ) ) { return (this-> sub_counter ); }
size_t (* carg_filter::get_sub_list_size( ) ) { return (this-> sub_list_size ); }
}
