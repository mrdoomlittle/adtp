# ifndef __port__manager__hpp__
# define __port__manager__hpp__
# include "dynamic_array.hpp"
# include "bitset_array.hpp"


// all of the code hear will be change when i have time
# define port_active 0
# define port_inactive 1
# define port_enabled 2
# define port_disabled 3
# define port_reserved 4
# define port_taken 5
# define port_nottaken 6

# define max_port_num_range 0
# define min_port_num_range 0

namespace tmp { class port_manager
{
    public :

        port_manager()
        {
            (this-> port_num_list).darr_init(1, 0);
            (this-> port_ibitset).bitset_init(8, 0);
            (this-> port_obitset).bitset_init(8, 0);
        }

        void
        (add_port_num(int unsigned(__port_number), bool(__set_port_num)))
        {
            if ((this-> dose_port_num_exist(__port_number)) == true) return;       

            (this-> port_num_list).add_darr_layer();
            (this-> port_ibitset).add_bitset();
            (this-> port_obitset).add_bitset();

            if (__set_port_num == true)
            {
                (this-> set_port_num(__port_number, (this-> port_num_arr_set_pos)));
                (this-> port_num_arr_set_pos) ++;
            }
        }

        void
        (set_port_num(int unsigned(__port_number), int unsigned(__port_num_arr_pos)))
        {
            (this-> port_num_list).set_darr_ilayer(&__port_number, __port_num_arr_pos, 0);
        }

        int unsigned
        (get_port_num(int unsigned(__port_num_arr_pos)))
        {
            return(* (this-> port_num_list).get_darr_ilayer(__port_num_arr_pos, 0));
        }

        void
        (change_port_num(int unsigned(__cport_num), int unsigned(__port_number)))
        {
            if ((this-> dose_port_num_exist(__cport_num)) == true) return;

            (this-> port_num_list).set_darr_ilayer(&__port_number, (this-> get_port_num_arr_pos(__cport_num)), 0);
        }

        bool
        (dose_port_num_exist(int unsigned(__port_number)))
        {
            int unsigned port_num_arr_pos = (this-> get_port_num_arr_pos(__port_number));

            if ((this-> cant_get_port_num_arr_pos) == true)
            {
                (this-> cant_get_port_num_arr_pos) = false;
                return (false);
            }

            if (*(this-> port_num_list).get_darr_ilayer(port_num_arr_pos, 0) == __port_number) return (true);
            
            return (false);
        }

        int unsigned
        (get_port_num_arr_pos(int unsigned(__port_number)))
        {
            for (int unsigned(x ) = 0; x != (this-> port_num_list).get_darr_depth(); x ++)
            {
                if (*(this-> port_num_list).get_darr_ilayer(x, 0) == __port_number) return (x); 
            }

            (this-> cant_get_port_num_arr_pos ) = true;

            return 0;
        }

        bool(cant_get_port_num_arr_pos ) = false;
        
        void 
        (del_port_num())
        {

        }

        void 
        (mark_port_num())
        {

        }

        void
        (create_port_num())
        {

        }

        void
        (open_port_num())
        {

        }

        void
        (close_port_num())
        {
    
        }

        int unsigned
        (get_port_num_count())
        {
            return((this-> port_num_list).get_darr_depth());
        }
    private :
        int unsigned(port_num_arr_set_pos) = 0;
        dynamic_array <int unsigned> port_num_list;
        bitset_array <int unsigned> port_ibitset;
        bitset_array <int unsigned> port_obitset; 

     
        dynamic_array <int unsigned> port_state_list;
} ; }

# endif /*__port__manager__hpp__*/
