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
    public :
        int unsigned
        (get_iblock_pos(std::uint8_t(__unit_id), int unsigned(_il) = 0, bool(sp) = false))
        {
            int unsigned tmp = 0;
            switch(__unit_id)
            {
                case
                (unit_id::__sector):
                    for (int unsigned(x ) = 0; x != (this-> amount_of_sectors); x ++)
                    {
                        if (sp == true && x == _il) break;
                        tmp += ((this-> sector_length [(data_id::__main)][x])* (this-> get_iblock_pos(1, 0, false)));
                    }
                    break;
                case
                (unit_id::__block):
                    for (int unsigned(x ) = 0; x != (this-> blocks_per_sector); x ++)
                    {
                        if (sp == true && x == _il) break;
                        tmp += (this-> block_length [(data_id::__main)][x]);
                    }
                    break;
            }
            return tmp;
        }

        int unsigned
        (get_iblock_count(std::uint8_t(__unit_id), int unsigned(__sector_pos_id), int unsigned(__block_pos_id)))
        {
            int unsigned tmp = 0, ll = 0;
            switch(__unit_id)
            {
                case
                (unit_id::__sector):
                    for (int unsigned(x ) = 0; x != (this-> sector_length [(data_id::__main)][__sector_pos_id]); x ++)
                    {
                        tmp += (this-> get_iblock_count(1, __sector_pos_id, x));
                    }

                    break;
                case
                (unit_id::__block):
                    for (int unsigned(x ) = 0; x != __sector_pos_id; x ++)
                    {
                        ll += (this-> sector_length [(data_id::__main)][x]);
                    }
                    for (int unsigned(x ) = 0; x != 6; x ++)
                    {
                        std::cout << (this-> block_length [(data_id::__main)][x]) << std::endl;
                    }

                    tmp = (this-> block_length [(data_id::__main)][ll + __block_pos_id]);

                    break;
            }
            return tmp;
        }

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

            (this-> block_ipos_id [(data_id::__main)] [( (this-> get_block_arr_pos (__sector_pos_id, __block_pos_id) ) * (this-> block_inner_length) ) + __block_ipos_id]) =
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
        dynamic_buffer(int unsigned(__amount_of_sectors ) = 0, int unsigned(__blocks_per_sector) = 0, int unsigned(__block_inner_length ) = 0)
        {
            if (__amount_of_sectors != 0 || __blocks_per_sector != 0 || __block_inner_length != 0)
                (this-> dbuff_init(__amount_of_sectors, __blocks_per_sector, __block_inner_length));
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

            (this-> sector_smarker [(data_id::__main)]) = new std::uint8_t [__amount_of_sectors];
            (this-> block_smarker [(data_id::__main)]) = new std::uint8_t [(this-> total_block_count)];
            (this-> block_ismarker [(data_id::__main)]) = new std::uint8_t [(this-> total_block_icount)];

            (this-> sector_pos_id [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> block_pos_id [(data_id::__main)]) = new int unsigned [(this-> total_block_count)];
            (this-> block_ipos_id [(data_id::__main)]) = new int unsigned [(this-> total_block_icount)];

            (this-> sector_length [(data_id::__main)]) = new int unsigned[__amount_of_sectors];
            (this-> block_length [(data_id::__main)]) = new int unsigned[total_block_count];

            for (int unsigned(sector_pos_id ) = 0; sector_pos_id != __amount_of_sectors; sector_pos_id ++)
            {
                (this-> sector_length [(data_id::__main)][sector_pos_id]) = __blocks_per_sector;

                (this-> set_sector_arr_pos (sector_pos_id, sector_pos_id) );

                (this-> set_sector_smarker (state_marker::__free__, sector_pos_id) );

                for (int unsigned(block_pos_id ) = 0; block_pos_id != __blocks_per_sector; block_pos_id ++)
                {
                    (this-> block_length [(data_id::__main)][(sector_pos_id * __blocks_per_sector) + block_pos_id]) = __block_inner_length;

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
        (add_to_dbuff (__dbuff_type(* __block_data ), int unsigned(__dbuff_unit_id ), int unsigned(__sector_pos_id ), int unsigned(__block_pos_id ),
        int unsigned(__block_ipos_id ), bool(__auto_sector_selc ), bool(__auto_block_selc ), bool(__auto_iblock_selc ) ) )
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
            int unsigned used_c = 0;
            int unsigned free_c = 0;
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


                    // this is a temp fix as i havent made the code to do this
                    for (int unsigned o = 0; o != (this-> blocks_per_sector); o++)
                    {
                        if (this-> is_block_smarker(true, (this-> sector_position [1]), o) == true) used_c++;
                        if (this-> is_block_smarker(false, (this-> sector_position [1]), o) == true) free_c++;
                    }

                    (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )]) = used_c;
                    (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )]) = free_c;

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
        (get_sector_used_c (int unsigned(__sector_pos_id )) )
        {
            return ( (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos (__sector_pos_id) )]) );
        }

        int unsigned
        (get_sector_free_c (int unsigned(__sector_pos_id )) )
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

        void
        (resize_dbuff(int unsigned(__resize_t ), int unsigned(__sector_pos_id ), int unsigned(__size_of_sector), int unsigned(__block_pos_id ),
        int unsigned(__size_of_block), int unsigned(__block_ipos_id ), int unsigned(__amount_of_iblocks)))
        {
            int unsigned(iblocks_to_add ) = 0;
            int unsigned blocks_to_add = 0;
            int unsigned oo = 0, ok = 0, ssi = 0;
            int unsigned bcount = 0, oj = 0;
            int unsigned be = 0, kk = 0, tmt = 0, lol = 0;
            switch(__resize_t)
            {
                case
                (unit_id::__sector):
                    blocks_to_add = __size_of_sector - (this-> sector_length[(data_id::__main)][__sector_pos_id]);

                    for (int unsigned(x ) = 0; x != (this-> sector_length[(data_id::__main)][__sector_pos_id]); x ++) {
                        oo += (this-> block_length [(data_id::__main)][x]);
                    }

                    // NOTE: block_inner_length is the default amount of iblock inside 1 block
                    iblocks_to_add = (__size_of_sector * block_inner_length) - oo;// amount of iblocks in sector;

                    std::cout << iblocks_to_add << std::endl;

                    (this-> dbuff_iblocks[(data_id::__swap)]) = new __dbuff_type [(this-> get_iblock_pos(0, 0, false))];

                    for (int unsigned(x ) = 0; x != (this-> get_iblock_pos(0, 0, false)); x ++) {
                        (this-> dbuff_iblocks [(data_id::__swap)] [x]) = (this-> dbuff_iblocks [(data_id::__main)] [x]);
                    }

                    std::free((this-> dbuff_iblocks [(data_id::__main)]));

                    (this-> dbuff_iblocks[(data_id::__main)]) = new __dbuff_type [(this-> get_iblock_pos(0, 0, false)) + iblocks_to_add];
                    // this works fine
                    for (int unsigned(x ) = 0; x != (this-> get_iblock_pos(0, 0, false)); x ++)
                    {
                        if (x >= (this-> get_iblock_pos(0, __sector_pos_id, true)) )
                            (this-> dbuff_iblocks [(data_id::__main)] [x+iblocks_to_add]) = (this-> dbuff_iblocks [(data_id::__swap)] [x]);
                        else
                            (this-> dbuff_iblocks [(data_id::__main)] [x]) = (this-> dbuff_iblocks [(data_id::__swap)] [x]);
                    }

                    std::free((this-> dbuff_iblocks [(data_id::__swap)]));

                    be = (this-> sector_length[(data_id::__main)][__sector_pos_id]);

                    (this-> sector_length[(data_id::__main)][__sector_pos_id]) = __size_of_sector;

                    for (int unsigned(x) = 0; x != (this-> amount_of_sectors); x ++)
                    {
                        bcount += this-> sector_length[0][x];
                    }


                    oj = (bcount - (__size_of_sector - be)); //??????????

                    for (int unsigned(x ) = 0; x != (bcount - (__size_of_sector - be)); x ++)
                    {
                        tmt+= this-> block_length[0][x];
                    }

                    (this-> block_length[(data_id::__swap)]) = new int unsigned[oj];

                    (this-> block_pos_id[(data_id::__swap)]) = new int unsigned [oj];
                    (this-> block_ipos_id[(data_id::__swap)]) = new int unsigned [tmt];
                    (this-> block_smarker[(data_id::__swap)]) = new std::uint8_t [oj];
                    (this-> block_ismarker[(data_id::__swap)]) = new std::uint8_t [tmt];

                    for (int unsigned(x ) = 0; x != (bcount - (__size_of_sector - be)); x ++)
                    {
                        (this-> block_length [(data_id::__swap)] [x]) = (this-> block_length [(data_id::__main)] [x]);
                        std::cout << "------------------->" << (this-> block_pos_id[(data_id::__main)] [x]) << std::endl;
                        (this-> block_pos_id[(data_id::__swap)] [x]) = (this-> block_pos_id[(data_id::__main)] [x]);

                        (this-> block_smarker[(data_id::__swap)] [x]) = (this-> block_smarker[(data_id::__main)] [x]);

                    }

                    for (int unsigned(x ) = 0; x != tmt; x ++)
                    {
                        (this-> block_ipos_id[(data_id::__swap)] [x]) = (this-> block_ipos_id[(data_id::__main)] [x]);
                        (this-> block_ismarker[(data_id::__swap)] [x]) = (this-> block_ismarker[(data_id::__main)] [x]);
                    }

                    std::free((this-> block_length [(data_id::__main)]));

                    std::free((this-> block_pos_id [(data_id::__main)]));
                    std::free((this-> block_ipos_id [(data_id::__main)]));
                    std::free((this-> block_smarker [(data_id::__main)]));
                    std::free((this-> block_ismarker [(data_id::__main)]));

                    (this-> block_length[(data_id::__main)]) = new int unsigned[bcount];
                    (this-> block_pos_id [(data_id::__main)]) = new int unsigned [bcount];
                    (this-> block_smarker [(data_id::__main)]) = new std::uint8_t [bcount];


                    for (int unsigned(x) = 0; x != __sector_pos_id; x ++)
                    {
                        kk += this-> sector_length[0][x];
                    }


                    for (int unsigned(x ) = 0; x != (bcount - (__size_of_sector - be)); x ++)
                    {

                        if (x >= kk)
                        {
                            (this-> block_length [(data_id::__main)] [x+kk]) = (this-> block_length [(data_id::__swap)] [x]);
                            (this-> block_pos_id[(data_id::__main)] [x+kk]) = (this-> block_pos_id[(data_id::__swap)] [x]);

                            (this-> block_smarker[(data_id::__main)] [x+kk]) = (this-> block_smarker[(data_id::__swap)] [x]);
                        }
                        else
                        {
                            (this-> block_length [(data_id::__main)] [x]) = (this-> block_length [(data_id::__swap)] [x]);
                            (this-> block_pos_id[(data_id::__main)] [x]) = (this-> block_pos_id[(data_id::__swap)] [x]);
                            (this-> block_smarker[(data_id::__main)] [x]) = (this-> block_smarker[(data_id::__swap)] [x]);

                        }

                    }

                    for (int unsigned(x ) = kk; x != bcount; x ++)
                    {
                        std::cout << "A" << std::endl;
                        (this-> block_length [(data_id::__main)] [x]) = (this-> block_inner_length);
                        (this-> block_smarker[(data_id::__main)] [x]) = 0;
                        //(this-> block_ismarker[(data_id::__main)] [x]) = 0;
                    }



                    for (int unsigned(x ) = 0; x != (this-> sector_length [(data_id::__main)] [__sector_pos_id]); x ++)
                    {
                        lol += (this-> block_length [(data_id::__main)] [x]);
                    }
                    ok = (get_iblock_pos(0, __sector_pos_id, true) + lol) - ((this-> block_inner_length) * blocks_to_add);
                    lol -= ((this-> block_inner_length) * blocks_to_add);

                    for (int unsigned y = 0; y != (this-> amount_of_sectors); y ++)
                        for (int unsigned x = 0; x != (this-> sector_length [(data_id::__main)] [y]); x ++)
                            ssi += (this-> block_length [(data_id::__main)] [x]);

                    (this-> block_ipos_id [(data_id::__main)]) = new int unsigned [tmt];
                    (this-> block_ismarker [(data_id::__main)]) = new std::uint8_t [tmt];

                    for (int unsigned(x ) = 0; x != tmt; x ++)
                    {
                        if (x >= ok)
                        {
                            (this-> block_ipos_id [(data_id::__main)][x+lol]) = (this-> block_ipos_id [(data_id::__swap)][x]);
                            (this-> block_ismarker [(data_id::__main)][x+lol]) = (this-> block_ismarker [(data_id::__swap)][x]);
                            (this-> block_ismarker [(data_id::__main)][x]) = state_marker::__free__;
                        }
                        else
                        {
                            (this-> block_ipos_id [(data_id::__main)][x]) = (this-> block_ipos_id [(data_id::__swap)][x]);
                            (this-> block_ismarker [(data_id::__main)][x]) = (this-> block_ismarker [(data_id::__swap)][x]);
                        }
                    }

                    for (int unsigned(x ) = 0; x != bcount; x ++)
                    {
                        std::cout << x << std::endl;
                        (this-> block_pos_id[(data_id::__main)] [x]) = x;
                    }

                    for (int unsigned(x ) = 0; x != ssi; x ++)
                    {
                        std::cout << x << std::endl;
                        (this-> block_ipos_id[(data_id::__main)] [x]) = x;
                    }




                    break;
                case
                (unit_id::__block):

                    break;
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

            // quick fix
            (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )]) = 0;
            (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )]) = 0;

            for (int unsigned o = 0; o != (this-> blocks_per_sector); o++)
            {
                if (this-> is_block_smarker(true, __sector_pos_id, o) == true) (this-> sector_used_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )])++;
                if (this-> is_block_smarker(false, __sector_pos_id, o) == true) (this-> sector_free_c [(data_id::__main)] [(this-> get_sector_arr_pos ((this-> sector_position [1])) )])++;
            }

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
public:
        int unsigned(total_block_count ) = 0;
        int unsigned(total_block_icount ) = 0;

        int unsigned(amount_of_sectors ) = 0;

        int unsigned(blocks_per_sector ) = 0;
        int unsigned(block_inner_length ) = 0;


        // this need renaming
        int unsigned
        (* * sector_length) = new int unsigned *[2];

        int unsigned
        (* *block_length) = new int unsigned* [2];

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

        std::uint8_t
        (* * sector_smarker ) = new std::uint8_t * [2];
        std::uint8_t
        (* * block_smarker ) = new std::uint8_t * [2];
        std::uint8_t
        (* * block_ismarker ) = new std::uint8_t * [2];

        bool(has_dbuff_init ) = false;

    public:
        __dbuff_type
        (* * dbuff_iblocks ) = new __dbuff_type * [2];
} ; }

# endif /*__dynamic__buffer__hpp__*/
