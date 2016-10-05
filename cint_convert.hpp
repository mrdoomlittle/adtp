# ifndef __cint__convert__hpp__
# define __cint__convert__hpp__

# define _1as_char '1'
# define _2as_char '2'
# define _3as_char '3'
# define _4as_char '4'
# define _5as_char '5'
# define _6as_char '6'
# define _7as_char '7'
# define _8as_char '8'
# define _9as_char '9'
/*
    still working on this
*/


// this might me extreamly inefficient but i dont know how else to do it and only other way i could think of was to use bitwise 
// this will stay like this for now and i might fix it later
namespace tmp { template <typename __int_type> __int_type(get_num_unit(const char __char, int unsigned(__pos), int unsigned(__char_length)))
{
    int unsigned ltcount = 0;
    int unsigned nlength = 0;
    int unsigned unit = 10;

    for (;;)
    {
        if (ltcount == 0) nlength ++;
        if (ltcount != 0)
        {
            if (ltcount == unit)
            {
                nlength ++;

                unit = (unit * 10);
            }
        }

        if (nlength == (__char_length - __pos))
        {
            if (ltcount == 0) return 1;
            return(ltcount);
        }

        ltcount ++;
    }

    return 0;
}

template <typename __int_type> __int_type(convert_to_int(const char * __char_contains, int unsigned(__char_length)))
{
    __int_type(__output_intdata) = 0;

    for (int unsigned(x ) = 0; x != __char_length; x ++)
    {
        switch((__char_contains [x]))
        {
            case _1as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 1);
                break;
            case _2as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 2);   
                break;
            case _3as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 3);
                break;
            case _4as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 4);
                break;
            case _5as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 5);
                break;
            case _6as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 6);
                break;
            case _7as_char: 
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 7);
                break;
            case _8as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 8);
                break;
            case _9as_char:
                __output_intdata += (get_num_unit<__int_type>(__char_contains[x], x, __char_length) * 9);
                break;
        }
    }

    return(__output_intdata);
} }


# endif /*__cint__convert__hpp__*/
