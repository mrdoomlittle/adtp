# ifndef __dynamic__buffer__hpp__
# define __dynamic__buffer__hpp__

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

namespace tmp { template <typename __dbuff_type> class dynamic_buffer
{
    private :
        void
        (set_sector_arr_pos (int unsigned(__sector_pos_id ), int unsigned(__sector_arr_pos ) ) )
        {
            (this-> sector_pos_id [(data_id::__main)] [__sector_pos_id]) = __sector_arr_pos;
        }

        void
        (set_block_arr_pos (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_arr_pos ) ) )
        {
            (this-> block_pos_id [(data_id::__main)] [( (this-> get_sector_arr_pos (__sector_pos_id) ) * (this-> blocks_per_sector) ) + __block_pos_id]) =
                ( ( (this-> get_sector_arr_pos (__sector_pos_id) ) * (this-> blocks_per_sector) ) + __block_arr_pos);
        }

        void
        (set_block_iarr_pos (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ), int unsigned(__block_iarr_pos ) ) )
        {
            (this-> block_pos_id [(data_id::__main)] [( (this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) ) * (this-> block_inner_length) ) + __block_ipos_id]) =
                ( ( (this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) ) * (this-> block_inner_length) ) + __block_ipos_id);
        }

        int unsigned
        (get_sector_arr_pos (int unsigned(__sector_pos_id ) ) )
        {
            return ( (this-> sector_pos_id [(data_id::__main)] [__sector_pos_id]) );
        }

        int unsigned
        (get_block_arr_pos (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            return ( (this-> block_pos_id [(data_id::__main)] [( (this-> get_sector_arr_pos (__sector_pos_id) ) * (this-> blocks_per_sector) ) + __block_pos_id]) );
        }

        int unsigned
        (get_block_iarr_pos (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            return ( (this-> block_pos_id [(data_id::__main)] [( (this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) ) * (this-> block_inner_length) ) + __block_ipos_id]) );
        }
    public :
        dynamic_buffer( )
        {

        }

        ~dynamic_buffer( )
        {
            // free memory
        }

        void
        (dbuff_init (int unsigned(__amount_of_sectors ), int unsigned(__blocks_per_sector ), int unsigned(__block_inner_length ) ) )
        {
            if ( (this-> is_dbuff_init (true) ) == true) return;

            if (__amount_of_sectors < 1) return;
            if (__blocks_per_sector < 1) return;
            if (__block_inner_length < 1) return;

            (this-> total_block_count) = (__amount_of_sectors * __blocks_per_sector);
            (this-> total_block_icount) = ( (this-> total_block_count) * __block_inner_length);
            (this-> amount_of_sectors) = __amount_of_sectors;
            (this-> blocks_per_sector) = __blocks_per_sector;
            (this-> block_inner_length) = __block_inner_length;

            (this-> sector_smarker [(data_id::__main)]) = new bool [__amount_of_sectors];
            (this-> block_smarker [(data_id::__main)]) = new bool [(this-> total_block_count)];
            (this-> block_ismarker [(data_id::__main)]) = new bool [(this-> total_block_icount)];

            (this-> sector_pos_id [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> block_pos_id [(data_id::__main)]) = new int unsigned [(this-> total_block_count)];
            (this-> block_ipos_id [(data_id::__main)]) = new int unsigned [(this-> total_block_icount)];

            for (int unsigned(sector_pos_id ) = 0; sector_pos_id != __amount_of_sectors; sector_pos_id ++)
            {
                (this-> set_sector_arr_pos (sector_pos_id, sector_pos_id) );

                (this-> set_sector_smarker (state_marker::__free__, sector_pos_id) );

                for (int unsigned(block_pos_id ) = 0; block_pos_id != __blocks_per_sector; block_pos_id ++)
                {
                    (this-> set_block_arr_pos (sector_pos_id, block_pos_id, block_pos_id) );

                    (this-> set_block_smarker (state_marker::__free__, sector_pos_id, block_pos_id) );

                    for (int unsigned(block_ipos_id ) = 0; block_ipos_id != __block_inner_length; block_ipos_id ++)
                    {
                        (this-> set_block_iarr_pos (sector_pos_id, block_pos_id, block_ipos_id, block_ipos_id) );

                        (this-> set_block_ismarker (state_marker::__free__, sector_pos_id, block_pos_id, block_ipos_id) );
                    }
                }
            }

            (this-> sector_free_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> sector_used_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];

            (this-> block_free_c [(data_id::__main)]) = new int unsigned [(this-> total_block_count)];
            (this-> block_used_c [(data_id::__main)]) = new int unsigned [(this-> total_block_count)];

            for (int unsigned(sector_pos_id ) = 0; sector_pos_id != __amount_of_sectors; sector_pos_id ++)
            {
                (this-> sector_free_c [(data_id::__main)] [sector_pos_id]) = (__blocks_per_sector - 1);
                (this-> sector_used_c [(data_id::__main)] [sector_pos_id]) = 0;
            }

            for (int unsigned(block_pos_id ) = 0; block_pos_id != (this-> total_block_count); block_pos_id ++)
            {
                (this-> block_free_c [(data_id::__main)] [block_pos_id]) = (__block_inner_length - 1);
                (this-> block_used_c [(data_id::__main)] [block_pos_id]) = 0;
            }

            (this-> dbuff_iblocks [(data_id::__main)]) = new __dbuff_type [(this-> total_block_icount)];

            (this-> toggle_dbuff_init( ) );
        }

    private :
        void
        (toggle_dbuff_init( ) )
        {
            (this-> has_dbuff_init ) = (this-> has_dbuff_init ) == true? false : true;
        }

        bool
        (is_dbuff_init (bool(__is_type ) ) )
        {
            return ( (this-> has_dbuff_init ) == __is_type? true : false);
        }

        bool
        (sector_pos_id_incheck (int unsigned(__sector_pos_id ) ) )
        {
            return (__sector_pos_id >= (this-> amount_of_sectors)? false : true);
        }

        bool
        (block_pos_id_incheck (int unsigned(__block_pos_id ) ) )
        {
            return (__block_pos_id >= (this-> blocks_per_sector)? false : true);
        }

        bool
        (iblock_pos_id_incheck (int unsigned(__block_ipos_id ) ) )
        {
            return (__block_ipos_id >= (this-> block_inner_length)? false : true);
        }
    public :
        void
        (add_to_dbuff (__dbuff_type(* __block_data ), int unsigned(__dbuff_unit_id ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ), bool(__auto_sector_selc ), bool(__auto_block_selc ), bool(__auto_iblock_selc ) ) )
        {
            if (! (this-> sector_pos_id_incheck (__sector_pos_id) ) )
                return;

            if (! (this-> block_pos_id_incheck (__block_pos_id) ) )
                return;

            if (__dbuff_unit_id == (unit_id::__iblock) )
                if (! (this-> iblock_pos_id_incheck (__block_ipos_id) ) ) return;

            if (__auto_sector_selc == true) goto auto_sector_selc;

                if ( (this-> is_sector_smarker (state_marker::__used__, __sector_pos_id) ) == true) return;

                (this-> sector_position [1]) = __sector_pos_id;

            goto skip_auto_sector_selc;

            auto_sector_selc :

                for (int unsigned(sector_pos_id ) = 0; sector_pos_id != (this-> amount_of_sectors); sector_pos_id ++ )
                {
                    if ( (this-> is_sector_smarker (state_marker::__free__, sector_pos_id) ) == true)
                    {
                        (this-> sector_position [1]) = sector_pos_id; break;
                    }

                    if (sector_pos_id == (this-> amount_of_sectors) - 1) return;
                }

            skip_auto_sector_selc :

            if (__auto_block_selc == true) goto auto_block_selc;

                if ( (this-> is_block_smarker (state_marker::__used__, (this-> sector_position [1]), __block_pos_id) ) == true) return;

                (this-> block_position [1]) = __block_pos_id;

            goto skip_auto_block_selc;

            auto_block_selc :

                for (int unsigned(block_pos_id ) = 0; block_pos_id != (this-> blocks_per_sector); block_pos_id ++ )
                {
                    if ( (this-> is_block_smarker (state_marker::__free__, (this-> sector_position [1]), block_pos_id) ) == true)
                    {
                        (this-> block_position [1]) = block_pos_id; break;
                    }

                    if (block_pos_id == (this-> blocks_per_sector) - 1) return;
                }

            skip_auto_block_selc :

            if (__auto_iblock_selc == true) goto auto_iblock_selc;

            if (__dbuff_unit_id != (unit_id::__iblock) ) goto skip_iblock_selc;

                if ( (this-> is_block_ismarker (state_marker::__used__, (this-> sector_position [1]), (this-> block_position [1]), __block_ipos_id) ) == true) return;

                (this-> block_iposition [1]) = __block_ipos_id;

            goto skip_auto_iblock_selc;

            auto_iblock_selc :

                for (int unsigned(block_ipos_id ) = 0; block_ipos_id != (this-> block_inner_length); block_ipos_id ++)
                {
                    if ( (this-> is_block_ismarker (state_marker::__free__, (this-> sector_position [1]), (this-> block_position [1]), block_ipos_id) ) == true)
                    {
                        (this-> block_iposition [1]) = block_ipos_id; break;
                    }

                    if (block_ipos_id == (this-> block_inner_length) - 1) return;
                }

            skip_auto_iblock_selc :

            skip_iblock_selc :

            switch (__dbuff_unit_id)
            {
                case (unit_id::__block) :
                    if ( (this-> get_sector_free_c ( (this-> sector_position [1]) ) ) == 0)
                        (this-> set_sector_smarker (state_marker::__used__, (this-> sector_position [1]) ) );

                    // this is not finished

                    (this-> update_sector_used_c ( (this-> sector_position [1]) ) );
                    (this-> update_sector_free_c ( (this-> sector_position [1]) ) );
                break;

                case (unit_id::__iblock) :
                    if ( (this-> get_block_free_c ( (this-> sector_position [1]), (this-> block_position [1]) ) ) == 0)
                        (this-> set_block_smarker (state_marker::__used__, (this-> sector_position [1]), (this-> block_position [1]) ) );

                    (this-> set_dbuff_iblock(__block_data, (this-> sector_position [1]), (this-> block_position [1]), (this-> block_iposition [1])));

                    (this-> set_block_ismarker(state_marker::__used__, (this-> sector_position [1]), (this-> block_position [1]), (this-> block_iposition [1])));

                    (this-> update_block_used_c ( (this-> sector_position [1]), (this-> block_position [1]) ) );
                    (this-> update_block_free_c ( (this-> sector_position [1]), (this-> block_position [1]) ) );
                break;
                default : return;
            }
        }

    private :
        void
        (update_sector_used_c (int unsigned(__sector_pos_id ) ) )
        {
            if ( (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) != (this-> blocks_per_sector) )
                (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) ++;
        }

        void
        (update_block_used_c (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            if ( (this-> block_used_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) != (this-> block_inner_length) )
                (this-> block_used_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) ++;
        }

        void
        (set_block_used_c (int unsigned(__block_used_c ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            (this-> block_used_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) = __block_used_c;
        }

        void
        (update_sector_free_c (int unsigned(__sector_pos_id ) ) )
        {
            if ( (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) != 0)
                (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) --;
        }

        void
        (update_block_free_c (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            if ( (this-> block_free_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) != 0)
                (this-> block_free_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) --;
        }

        void
        (set_block_free_c (int unsigned(__block_free_c ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            (this-> block_free_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) = __block_free_c;
        }

    public :
        int unsigned
        (get_sector_used_c (int unsigned(__sector_pos_id ) ) )
        {
            return ( (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) );
        }

        int unsigned
        (get_sector_free_c (int unsigned(__sector_pos_id ) ) )
        {
            return ( (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) );
        }

        int unsigned
        (get_block_used_c (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            return ( (this-> block_used_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) );
        }

        int unsigned
        (get_block_free_c (int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            return ( (this-> block_free_c [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) );
        }

        __dbuff_type
        (* get_from_dbuff (int unsigned(dbuff_unit_id ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ), bool(__auto_sector_selc ), bool(__auto_block_selc ), bool(__auto_iblock_selc ), bool(__return_nonused ) ) )
        {
            if (!(this-> sector_pos_id_incheck(__sector_pos_id))) return (nullptr);
            if (!(this-> block_pos_id_incheck(__block_pos_id))) return (nullptr);

            if (dbuff_unit_id == (unit_id::__iblock) )
                if (!(this-> iblock_pos_id_incheck(__block_ipos_id))) return (nullptr);

            if (__auto_sector_selc == true) goto auto_sector_selc;

                (this-> sector_position [0]) = __sector_pos_id;

            goto skip_auto_sector_selc;

            // still working on auto sb
            auto_sector_selc :

                // auto sector selc

            skip_auto_sector_selc : /*skip*/

            if (__auto_block_selc == true) goto auto_block_selc;

                (this-> block_position [0]) = __block_pos_id;

            goto skip_auto_block_selc;

            auto_block_selc :

                // auto block selc

            skip_auto_block_selc : /*skip*/

            if (__auto_iblock_selc == true) goto auto_iblock_selc;

                (this-> block_iposition [0]) = __block_ipos_id;

            goto skip_auto_iblock_selc;

            auto_iblock_selc :

                // auto iblock selc

            skip_auto_iblock_selc :

            switch (dbuff_unit_id)
            {
                case (unit_id::__block) :
                    if ((this-> is_block_smarker(state_marker::__free__, (this-> sector_position [0]), (this-> block_position [0]))) == true && __return_nonused == false) return (nullptr);
                    return ((this-> get_dbuff_block((this-> sector_position [0]), (this-> block_position [0]))));
                break;
                case (unit_id::__iblock) :
                    if ((this-> is_block_ismarker(state_marker::__free__, (this-> sector_position [0]), (this-> block_position [0]), (this-> block_iposition [0]))) == true && __return_nonused == false) return (nullptr);
                    return ((this-> get_dbuff_iblock((this-> sector_position [0]), (this-> block_position [0]), (this-> block_iposition [0]))));
                break;
                default : return (nullptr);
            }
        }

        void
        (del_from_dbuffer (int unsigned(__dbuff_unit_id ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            switch (__dbuff_unit_id)
            {
                case (unit_id::__sector) :
                    (this-> del_dbuff_sector (__sector_pos_id) );
                break;
                case (unit_id::__block) :
                    (this-> del_dbuff_block (__sector_pos_id, __block_pos_id) );
                break;
                case (unit_id::__iblock) :
                    (this-> del_dbuff_iblock (__sector_pos_id, __block_pos_id, __block_ipos_id) );
                break;
                default : return;
            }
        }

    private :
        void
        (set_sector_smarker (bool(__sector_state ), int unsigned(__sector_pos_id ) ) )
        {
            (this-> sector_smarker [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) = __sector_state;
        }

        void
        (set_block_smarker (bool(__block_state ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            (this-> block_smarker [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) = __block_state;
        }

        void
        (set_block_ismarker (bool(__block_istate ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            (this-> block_ismarker [(data_id::__main)] [(this-> get_block_iarr_pos (__sector_pos_id, __block_pos_id, __block_ipos_id) )]) = __block_istate;
        }
    public :
        bool
        (is_sector_smarker (bool(__is_type ), int unsigned(__sector_pos_id ) ) )
        {
            return ( (this-> sector_smarker [(data_id::__main)] [(this-> get_sector_arr_pos(__sector_pos_id) )]) == __is_type? true : false);
        }

        bool
        (is_block_smarker (bool(__is_type ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            return ( (this-> block_smarker [(data_id::__main)] [(this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) )]) == __is_type? true : false);
        }

        bool
        (is_block_ismarker (bool(__is_type ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            return ( (this-> block_ismarker [(data_id::__main)] [(this-> get_block_iarr_pos (__sector_pos_id, __block_pos_id, __block_ipos_id) )]) == __is_type? true : false);
        }
    private :
/*
        void
        (set_dbuff_sector (__dbuff_type (* * __sector_data ), int unsigned (__sector_pos_id ) ) )
        {
            for (int unsigned(block_pos_id) = 0; block_pos_id != (this-> blocks_per_sector); block_pos_id ++)
                (this-> set_dbuff_block((__sector_data [block_pos_id]), __sector_pos_id, block_pos_id));
        }
*/
        void
        (set_dbuff_block (__dbuff_type (* __block_data ), int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            for (int unsigned(block_ipos_id ) = 0; block_ipos_id != (this-> block_inner_length); block_ipos_id ++)
                (this-> set_dbuff_iblock ( (__block_data [block_ipos_id]), __sector_pos_id, __block_pos_id, block_ipos_id) );
        }

        void
        (set_dbuff_iblock (__dbuff_type (* __block_idata ), int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            (this-> dbuff_iblocks [(data_id::__main)] [(this-> get_block_iarr_pos (__sector_pos_id, __block_pos_id, __block_ipos_id) )]) = (* __block_idata);
        }

        __dbuff_type
        (* get_dbuff_block (int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            return nullptr;
            // still need to finish
        }

        __dbuff_type
        (* get_dbuff_iblock (int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            return (& (this-> dbuff_iblocks [(data_id::__main)] [(this-> get_block_iarr_pos (__sector_pos_id, __block_pos_id, __block_ipos_id) )]) );
        }

        void
        (del_dbuff_sector (int unsigned (__sector_pos_id ) ) )
        {
            (this-> set_sector_smarker (state_marker::__free__, __sector_pos_id) );

            for (int unsigned (block_pos_id ) = 0; block_pos_id != (this-> blocks_per_sector); block_pos_id ++)
                (this-> del_dbuff_block (__sector_pos_id, block_pos_id) );
        }

        void
        (del_dbuff_block (int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ) ) )
        {
            (this-> set_block_used_c (0, __sector_pos_id, __block_pos_id) );

            (this-> set_block_free_c ((this-> block_inner_length - 1), __sector_pos_id, __block_pos_id) );

            (this-> set_block_smarker (state_marker::__free__, __sector_pos_id, __block_pos_id) );

            for (int unsigned (block_ipos_id ) = 0; block_ipos_id != (this-> block_inner_length); block_ipos_id ++)
                (this-> del_dbuff_iblock (__sector_pos_id, __block_pos_id, block_ipos_id) );
        }

        void
        (del_dbuff_iblock (int unsigned (__sector_pos_id ), int unsigned(__block_pos_id ), int unsigned(__block_ipos_id ) ) )
        {
            (this-> set_block_ismarker (state_marker::__free__, __sector_pos_id, __block_pos_id, __block_ipos_id) );
        }

    private :
        enum unit_id : const int unsigned
        {
            __sector = 0,
            __block = 1,
            __iblock = 2
        } ;

        enum data_id : const int unsigned
        {
            __main = 0,
            __swap = 1
        } ;


        /* __free/__used where conflicting with something in the 101 corelibs. */
        enum state_marker : const bool
        {
            __used__ = true,
            __free__ = false
        } ;

        int unsigned(total_block_count ) = 0;
        int unsigned(total_block_icount ) = 0;

        int unsigned(amount_of_sectors ) = 0;

        int unsigned(blocks_per_sector ) = 0;
        int unsigned(block_inner_length ) = 0;

        int unsigned
        (* sector_position ) = new int unsigned [2];
        int unsigned
        (* block_position ) = new int unsigned [2];
        int unsigned
        (* block_iposition ) = new int unsigned [2];

        int unsigned
        (* * sector_free_c ) = new int unsigned * [2];
        int unsigned
        (* * sector_used_c ) = new int unsigned * [2];
        int unsigned
        (* * block_free_c ) = new int unsigned * [2];
        int unsigned
        (* * block_used_c ) = new int unsigned * [2];

        int unsigned
        (* * sector_pos_id ) = new int unsigned * [2];
        int unsigned
        (* * block_pos_id ) = new int unsigned * [2];
        int unsigned
        (* * block_ipos_id ) = new int unsigned * [2];

        bool
        (* * sector_smarker ) = new bool * [2];
        bool
        (* * block_smarker ) = new bool * [2];
        bool
        (* * block_ismarker ) = new bool * [2];

        bool(has_dbuff_init ) = false;

        __dbuff_type
        (* * dbuff_iblocks ) = new __dbuff_type * [2];
} ;
    typedef dynamic_buffer <int> dbint_t;
}

# endif /*__dynamic__buffer__hpp__*/
