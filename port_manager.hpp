# ifndef __port__manager__hpp__
# define __port__manager__hpp__
# include "dynamic_array.hpp"
# include "bitset_list.hpp"
# include "tmp_config.hpp"
# include "data_packet.hpp"
# include "dpacket_array.hpp"
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

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

// REMINDER: after this is finished and cleaned up put code into .cpp file
// need interface update

namespace tmp { class port_manager
{
    public :

        port_manager();

        void
        (add_port_num(int unsigned(__port_number), bool(__setup_port_num), int unsigned(__interface_id)));
        void
        (set_port_num(int unsigned(__port_number), int unsigned(__port_num_arr_pos)));

        int unsigned
        (get_port_num(int unsigned(__port_num_arr_pos)));
        void
        (change_port_num(int unsigned(__cport_num), int unsigned(__port_number)));

        bool
        (dose_port_num_exist(int unsigned(__port_number)));

        int unsigned
        (get_port_num_arr_pos(int unsigned(__port_number)));

        bool(cant_get_port_num_arr_pos ) = false;

        void
        (set_port_dati_bitset());
        void
        (set_port_dato_bitset());

        void
        (set_port_iface_id(int unsigned(__interface_id), int unsigned(__port_number)));

        int unsigned
        (get_port_iface_id(int unsigned(__port_number)));

        /* example of how we are going to get the packet as a program

            if ((pin_manager-> get_port_dpacket_ptr())-> is_dpacket_complete() == false) return;

            this can be done other ways!

        */

        // hear we are going to send the bitset and add it to the packet
        void
        (update_port_dpacket(int unsigned(__bitset_t), int unsigned(__port_number)));

        void
        (del_port_num());
        
        void
        (mark_port_num());

        void
        (create_port_num());

        void
        (open_port_num());

        void
        (close_port_num());

        int unsigned
        (get_port_num_count());
    private :
        int unsigned(port_num_arr_set_pos) = 0;
        dynamic_array <int unsigned> port_num_list;
        bitset_list <int unsigned> port_ibitset;
        bitset_list <int unsigned> port_obitset;
        dynamic_array <int unsigned> port_iface_id;

        dpacket_array dpackets;


        dynamic_array <int unsigned> port_state_list;
} ; }

# endif /*__port__manager__hpp__*/
