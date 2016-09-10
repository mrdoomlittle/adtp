# ifndef __dynamic__buffer__hpp__
# define __dynamic__buffer__hpp__
# define sector_is_in_use true
# define block_is_in_use true
# define sector_not_used false
# define block_not_used false
# include <iostream>
// this is still not finished
namespace adtp {
template <typename __dbuff_type>
class dynamic_buffer
{
    private :

    public :
        void (set_sector_arr_pos (int unsigned(__sector_pos_id ), int unsigned(__sector_arr_pos ) ) )
        {
            (this-> sector_pos_id [(data_id::__main)] [__sector_pos_id]) = __sector_arr_pos;
        }

        int unsigned (get_sector_arr_pos (int unsigned(__sector_pos_id ) ) )
        {
            return ( (this-> sector_pos_id [(data_id::__main)] [__sector_pos_id]) );
        }

        void (set_block_arr_pos(int unsigned(__sector_pos_id), int unsigned(__block_pos_id ), int unsigned(__block_arr_pos ) ) )
        {
            (this-> block_pos_id [(data_id::__main)] [((this-> get_sector_arr_pos(__sector_pos_id)) * (this-> blocks_per_sector)) + __block_pos_id]) = (((this-> get_sector_arr_pos(__sector_pos_id)) * (this-> blocks_per_sector)) + __block_arr_pos);
        }

        int unsigned (get_block_arr_pos(int unsigned(__sector_pos_id), int unsigned(__block_pos_id)))
        {
            return ((this-> block_pos_id [(data_id::__main)] [((this-> get_sector_arr_pos(__sector_pos_id)) * (this-> blocks_per_sector)) + __block_pos_id]));
        }

        void (dbuff_init(int unsigned(__amount_of_sectors), int unsigned(__blocks_per_sector)))
        {
            if ((this-> is_dbuff_init(true)) == true) return;

            if (__amount_of_sectors < 1) return;
            if (__blocks_per_sector < 1) return;

            (this-> total_block_count) = (__amount_of_sectors * __blocks_per_sector);
            (this-> amount_of_sectors) = __amount_of_sectors;
            (this-> blocks_per_sector) = __blocks_per_sector;

            (this-> sector_smarker [(data_id::__main)]) = new bool [__amount_of_sectors];
            (this-> block_smarker [(data_id::__main)]) = new bool [(this-> total_block_count)];

            (this-> sector_pos_id [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> block_pos_id [(data_id::__main)]) = new int unsigned [(this-> total_block_count)];

            for (int unsigned(sector_pos_id ) = 0; sector_pos_id != __amount_of_sectors; sector_pos_id ++)
            {
                (this-> set_sector_arr_pos(sector_pos_id, sector_pos_id));

                (this-> set_sector_marker(sector_not_used, sector_pos_id));

                for (int unsigned(block_pos_id ) = 0; block_pos_id != __blocks_per_sector; block_pos_id ++)
                {
                    (this-> set_block_arr_pos(sector_pos_id, block_pos_id, block_pos_id));

                    (this-> set_block_marker(block_not_used, sector_pos_id, block_pos_id));
                }
            }

            (this-> sector_free_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> sector_used_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];

            for (int unsigned(sector_pos_id ) = 0; sector_pos_id != __amount_of_sectors; sector_pos_id ++)
            {
                (this-> sector_free_c [(data_id::__main)] [sector_pos_id]) = (__blocks_per_sector - 1);
                (this-> sector_used_c [(data_id::__main)] [sector_pos_id]) = 0;
            }

            (this-> dbuff_blocks [(data_id::__main)]) = new __dbuff_type [(this-> total_block_count)];

            (this-> toggle_dbuff_init( ) );
        }

        void (toggle_dbuff_init( ) )
        {
            (this-> has_dbuff_init ) = (this-> has_dbuff_init ) == true? false : true;
        }

        bool (is_dbuff_init (bool(__is_type ) ) )
        {
            return ((this-> has_dbuff_init) == __is_type? true : false);
        }

        bool (sb_pos_id_incheck( bool(__check_sector ), bool(__check_block ), int unsigned(__sector_pos_id), int unsigned(__block_pos_id) ))
        {
            if (__check_sector == true && __sector_pos_id >= (this-> amount_of_sectors)) return false;
            if (__check_block == true && __block_pos_id >= (this-> blocks_per_sector)) return false;
            return true;
        }

        void (add_to_dbuff (__dbuff_type(__block_data ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), bool(__auto_sector_selc ), bool(__auto_block_selc ) ) )
        {
            if ((this-> sb_pos_id_incheck(true, true, __sector_pos_id, __block_pos_id)) == false) return;

            if (__auto_sector_selc == true) goto auto_sector_selc;

                (this-> sector_position [1]) = __sector_pos_id;

            goto skip_auto_sector_selc;

            auto_sector_selc :

                for (int unsigned(sector_pos_id ) = 0; sector_pos_id != (this-> amount_of_sectors); sector_pos_id ++ )
                {
                    if ( (this-> is_sector_marker (sector_not_used, sector_pos_id) ) == true)
                    {
                        (this-> sector_position [1]) = sector_pos_id;
                        break;
                    }
                }

            skip_auto_sector_selc :

            if (__auto_block_selc == true) goto auto_block_selc;

                (this-> block_position [1]) = __block_pos_id;

            goto skip_auto_block_selc;

            auto_block_selc :

                for (int unsigned(block_pos_id ) = 0; block_pos_id != (this-> blocks_per_sector); block_pos_id ++ )
                {
                    if ( (this-> is_block_marker (block_not_used, (this-> sector_position [1]), block_pos_id) ) == true)
                    {
                        (this-> block_position [1]) = block_pos_id;
                        break;
                    }
                }

            skip_auto_block_selc :

            if ( (this-> is_sector_marker(sector_is_in_use, (this-> sector_position [1]) ) ) == true) return;
            if ( (this-> is_block_marker(block_is_in_use, (this-> sector_position [1]), (this-> block_position [1]) ) ) == true) return;

            (this-> set_dbuff_block(__block_data, (this-> sector_position [1]), (this-> block_position [1]), false) );

            (this-> update_sector_used_c( ) );
            (this-> update_sector_free_c( ) );

        }

        void (update_sector_used_c( ) )
        {
            if ((this-> sector_used_c [(data_id::__main)] [(this-> sector_position [1])]) != (this-> blocks_per_sector))
                (this-> sector_used_c [(data_id::__main)] [(this-> sector_position [1])]) ++;
        }

        void (update_sector_free_c( ) )
        {
            if ((this-> sector_free_c [(data_id::__main)] [(this-> sector_position [1])]) == 0)
                (this-> set_sector_marker(sector_is_in_use, (this-> sector_position [1])));
            else
                (this-> sector_free_c [(data_id::__main)] [(this-> sector_position [1])]) --;
        }

        __dbuff_type (* get_from_dbuff (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), bool(__auto_sector_selc ), bool(__auto_block_selc ), bool(__return_empty ) ) )
        {
            if ((this-> sb_pos_id_incheck(true, true, __sector_pos_id, __block_pos_id)) == false) return nullptr;

            if (__auto_sector_selc == true) goto auto_sector_selc;

                (this-> sector_position [1]) = __sector_pos_id;

            goto skip_auto_sector_selc;

            // still working on auto sb
            auto_sector_selc :

                if ((this-> block_position [0]) == (this-> blocks_per_sector))
                    std::cout << "SP" << std::endl;
                else
                    (this-> sector_position [0]) ++;

                (this-> sector_position [1]) = (this-> sector_position [0]);

            skip_auto_sector_selc : /*skip*/

            if (__auto_block_selc == true) goto auto_block_selc;

                (this-> block_position [1]) = __block_pos_id;

            goto skip_auto_block_selc;

            auto_block_selc :

                if ((this-> block_position [0]) == (this-> blocks_per_sector))
                    std::cout << "BP" << std::endl;
                else
                    (this-> block_position [0]) ++;

                (this-> block_position [1]) = (this-> block_position [0]);

            skip_auto_block_selc : /*skip*/

            if (this-> is_block_marker (block_not_used, __sector_pos_id, __block_pos_id) == true && __return_empty == false) return (nullptr);

            return ( (this-> get_dbuff_block ( (this-> sector_position [1]), (this-> block_position [1]), false) ) );
        }

        void (del_from_buffer( ) )
        {
            (this-> del_dbuff_block (1,0) );
        }

        void (set_sector_marker (bool(__sector_state ), int unsigned(__sector_pos_id ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, false, __sector_pos_id, 0) ) == false) return;

            (this-> sector_smarker [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id))]) = __sector_state;
        }

        void (set_block_marker (bool(__block_state ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, true, __sector_pos_id, __block_pos_id) ) == false) return;

            (this-> block_smarker [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) = __block_state;
        }

        bool (is_sector_marker (bool(__is_type ), int unsigned(__sector_pos_id ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, false, __sector_pos_id, 0) ) == false) return (false);

            return ((this-> sector_smarker [(data_id::__main)] [(this-> get_sector_arr_pos(__sector_pos_id))]) == __is_type? true : false);
        }

        bool (is_block_marker (bool(__is_type ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, true, __sector_pos_id, __block_pos_id) ) == false) return (false);

            return ((this-> block_smarker [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) == __is_type? true : false);
        }

        void (set_dbuff_block (__dbuff_type (__block_data ), int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ), bool(__overwrite ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, true, __sector_pos_id, __block_pos_id) ) == false) return;

            if (__overwrite == false && (this-> is_block_marker (block_is_in_use, __sector_pos_id, __block_pos_id) ) == true) return;

            (this-> set_block_marker (block_is_in_use, __sector_pos_id, __block_pos_id) );

            (this-> dbuff_blocks [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) = __block_data;
        }

        __dbuff_type (* get_dbuff_block (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), bool(__return_empty ) ) )
        {
            if ( (this-> sb_pos_id_incheck (true, true, __sector_pos_id, __block_pos_id) ) == false) return (nullptr);

            if (__return_empty == false && (this-> is_block_marker (block_not_used, __sector_pos_id, __block_pos_id) ) == true) return nullptr;

            return & (this-> dbuff_blocks [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]);
        }

        void (del_dbuff_block (int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            (this-> set_block_marker (block_not_used, __sector_pos_id, __block_pos_id) );
        }

    private :
    enum unit_id { __sector, __block } ;
    enum data_id { __main = 0, __swap = 1 } ;
    int unsigned(total_block_count) = 0;
    int unsigned(amount_of_sectors) = 0;
    int unsigned(blocks_per_sector) = 0;

    int unsigned(* curr_sector_pos) = new int unsigned [2];
    int unsigned(* curr_block_pos) = new int unsigned [2];

    int unsigned(* sector_position) = new int unsigned [2];
    int unsigned(* block_position) = new int unsigned [2];

    int unsigned(* * sector_free_c) = new int unsigned * [2];
    int unsigned(* * sector_used_c) = new int unsigned * [2];
   
    int unsigned(* * sector_pos_id) = new int unsigned * [2];
    int unsigned(* * block_pos_id) = new int unsigned * [2];

    bool(* * sector_smarker) = new bool * [2];
    bool(* * block_smarker) = new bool * [2];
    bool(has_dbuff_init) = false;

    __dbuff_type(* * dbuff_blocks) = new __dbuff_type * [2];
} ;

// NOTE: only for debugging
typedef dynamic_buffer <int> dbint_t;
}
# endif /*__dynamic__buffer__hpp__*/
