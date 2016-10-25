# ifndef __time__hpp__
# define __time__hpp__

# include "tmp_config.hpp"
# include "dynamic_array.hpp"


/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
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
