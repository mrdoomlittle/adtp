# ifndef __time__hpp__
# define __time__hpp__

# include "tmp_config.hpp"
# include "dynamic_array.hpp"


/*
what am i doing hear / what is going hear?

this will hold function's for time so like a stop watch get the time and etc

*/

namespace tmp { class time
{
    public :
        void (create_stopwatch());

        void (delete_stopwatch());

        void (reset_stopwatch());

        void (get_stopwatch_val());

        bool (is_stopwatch_val())
        {
            return false;
        }

//        time()
//        {
//            (this-> stopwatch_ssv).
//        }

    private :
        dynamic_array <int unsigned long> stopwatch_ssv;


} ; }


# endif /*__time__hpp__*/
