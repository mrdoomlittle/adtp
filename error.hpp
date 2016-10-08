# ifndef __error__hpp__
# define __error__hpp__
# include "dynamic_array.hpp"

namespace tmp { class error
{
    public :
        error()
        {
            (this-> error_id_ls).darr_init(1, 0);
        }

        void(add_error(int(__error_id)))
        {
            (this-> error_id_ls).add_darr_layer();
            (this-> error_id_ls).set_darr_ilayer(&__error_id, error_ls_pos, 0);
            (this-> error_ls_pos) ++;
        }

        bool(is_everthing_ok())
        {
            return ((this-> error_ls_pos) != 0? false : true);
        }

    private :
        dynamic_array <int> error_id_ls; 
        int unsigned(error_ls_pos ) = 0;
} ; }

# endif /*__error__hpp__*/
