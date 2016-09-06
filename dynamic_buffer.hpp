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
        void (set_sector_id(int unsigned(__sector_tid), int unsigned(__sector_rid)))
        {
            (this-> sector_id [(data_id::__main)] [__sector_tid]) = __sector_rid; }

        int unsigned (get_sector_id(int unsigned(__sector_tid)))
        {
            return ((this-> sector_id [(data_id::__main)] [__sector_tid])); }

        void (set_block_id(int unsigned(__block_tid), int unsigned(__block_rid)))
        {
            (this-> block_id [(data_id::__main)] [__block_tid]) = __block_rid; }

        int unsigned (get_block_id(int unsigned(__block_tid)))
        {
            return ((this-> block_id [(data_id::__main)] [__block_tid])); }

        void (dbuff_init(int unsigned(__amount_of_sectors), int unsigned(__blocks_per_sector)))
        {
            if ((this-> is_dbuff_init(true)) == true) return;

            if (__amount_of_sectors < 1) return;
            if (__blocks_per_sector < 1) return;

            (this-> amount_of_sectors) = __amount_of_sectors;
            (this-> blocks_per_sector) = __blocks_per_sector;

            (this-> sector_smarker [(data_id::__main)]) = new bool [__amount_of_sectors];
            (this-> block_smarker [(data_id::__main)]) = new bool [(__amount_of_sectors * __blocks_per_sector)];

            (this-> sector_id [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> block_id [(data_id::__main)]) = new int unsigned [(__amount_of_sectors * __blocks_per_sector)];

            for (int unsigned(sector_pos ) = 0; sector_pos != __amount_of_sectors; sector_pos ++)
            {
                (this-> set_sector_mark(sector_not_used, sector_pos));
                (this-> set_sector_id(sector_pos, sector_pos));
                for (int unsigned(block_pos ) = 0; block_pos != __blocks_per_sector; block_pos ++)
                {
                    (this-> set_block_mark(block_not_used, sector_pos, block_pos));
                    (this-> set_block_id((((sector_pos) * (__blocks_per_sector)) + block_pos),
                    (((sector_pos) * (__blocks_per_sector)) + block_pos))); 
                }
            }

            (this-> sector_free_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];
            (this-> sector_used_c [(data_id::__main)]) = new int unsigned [__amount_of_sectors];

            for (int unsigned(sector_pos ) = 0; sector_pos != __amount_of_sectors; sector_pos ++)
                (this-> sector_free_c [(data_id::__main)] [sector_pos]) = (__blocks_per_sector - 1);

            (this-> dbuff_blocks [(data_id::__main)]) = new __dbuff_type [(__amount_of_sectors * __blocks_per_sector)]; 

            (this-> toggle_dbuff_init());
        }

        void (toggle_dbuff_init())
        {
            (this-> has_dbuff_init) = (this-> has_dbuff_init) == true? false : true;
        }

        bool(is_dbuff_init(bool(__is_type)))
        {
            return((this-> has_dbuff_init) == __is_type? true: false);
        }

        void (add_to_dbuff(__dbuff_type (__block_data), int unsigned(__sector_pos), int unsigned(__block_pos), bool(__auto_sector), bool(__auto_block) ) )
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return;
            if (__block_pos >= (this-> blocks_per_sector)) return;

            if (__auto_sector == true) goto auto_sector;
            (this-> sector_position [1]) = __sector_pos;
          
            goto skip_auto_sector;
            auto_sector :

            for (int unsigned(sector_pos ) = 0; sector_pos != (this-> amount_of_sectors); sector_pos ++ )
            {
                if ((this-> is_sector_mark(sector_not_used, (this-> get_sector_id(sector_pos)))) == true)
                {
                    (this-> sector_position [1]) = sector_pos;
                    break;
                }
            }            
 
            skip_auto_sector :
            if (__auto_block == true) goto auto_block;
            (this-> block_position [1]) = __block_pos;
 
            goto skip_auto_block;
            auto_block :

            for (int unsigned(block_pos ) = 0; block_pos != (this-> blocks_per_sector); block_pos ++ )
            {
                if ((this-> is_block_mark(block_not_used, (this-> sector_position [1]), (this-> get_block_id(block_pos)))) == true)
                {
                    (this-> block_position [1]) = block_pos;
                    break;
                }                
            }

            skip_auto_block :

            if ((this-> is_sector_mark(sector_is_in_use, (this-> sector_position [1]))) == true) return;
            if ((this-> is_block_mark(block_is_in_use, (this-> sector_position [1]), (this-> block_position [1]))) == true) return;

            if ((this-> sector_used_c [(data_id::__main)] [(this-> sector_position [1])]) != (this-> blocks_per_sector) - 1)
                (this-> sector_used_c [(data_id::__main)] [(this-> sector_position [1])]) ++;

            if ((this-> sector_free_c [(data_id::__main)] [(this-> sector_position [1])]) == 0)
            {
                (this-> set_sector_mark(sector_is_in_use, (this-> sector_position [1])));
            }
            else (this-> sector_free_c [(data_id::__main)] [(this-> sector_position [1])]) --; 
          
            (this-> set_block_mark(block_is_in_use, (this-> sector_position [1]), (this-> block_position [1])));
 
            for (int unsigned x = 0; x != amount_of_sectors; x++)
                std::cout << "FREE: " << (this-> sector_free_c [(data_id::__main)] [x]) << ", USED: " << (this-> sector_used_c [(data_id::__main)] [x]) << ", SID: " << x  << std::endl;

            for (int unsigned x = 0; x != ((this-> amount_of_sectors) * (this-> blocks_per_sector)); x++)
                std::cout << "|" << block_smarker[0][x];
            std::cout << std::endl;
            return;
        }

        __dbuff_type (get_from_dbuff(int unsigned(__sector_pos), int unsigned(__block_pos), bool(__auto_sector), bool(__auto_block)))
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return 0;
            if (__block_pos >= (this-> blocks_per_sector)) return 0;

            if (__auto_sector == true) goto auto_sector;

            goto skip_auto_sector;
            auto_sector :

            skip_auto_sector :
            if (__auto_block == true) goto auto_block;
            
            return ((this-> dbuff_blocks [(data_id::__main)] [((__sector_pos * (this-> amount_of_sectors)) + __block_pos)]));

            return 0;
            auto_block :
            return 0 ;
        }

        void (set_sector_mark(bool(__sector_state), int unsigned(__sector_pos)))
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return;

            (this-> sector_smarker [(data_id::__main)] [(this-> get_sector_id(__sector_pos))]) = __sector_state;
        }

        void (set_block_mark(bool(__block_state), int unsigned(__sector_pos), int unsigned(__block_pos)))
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return;
            if (__block_pos >= (this-> blocks_per_sector)) return;

            (this-> block_smarker [(data_id::__main)] [(this-> get_block_id(((__sector_pos) * (this-> blocks_per_sector)) + __block_pos))]) = __block_state;
        }

        bool (is_sector_mark(bool(__is_type), int unsigned(__sector_pos)))
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return false;

            return ((this-> sector_smarker [(data_id::__main)] [(this-> get_sector_id(__sector_pos))]) == __is_type? true : false);
        }

        bool (is_block_mark(bool(__is_type), int unsigned(__sector_pos), int unsigned(__block_pos)))
        {
            if (__sector_pos >= (this-> amount_of_sectors)) return false;
            if (__block_pos >= (this-> blocks_per_sector)) return false;
          
            return ((this-> block_smarker [(data_id::__main)] [(this-> get_block_id(((__sector_pos) * (this-> blocks_per_sector)) + __block_pos))]) == __is_type? true : false);
        }

    private :
    enum unit_id { __sector, __block } ;
    enum data_id { __main = 0, __swap = 1 } ;

    int unsigned(amount_of_sectors) = 0;
    int unsigned(blocks_per_sector) = 0;
    int unsigned(* sector_position) = new int unsigned [2];
    int unsigned(* block_position) = new int unsigned [2];
    int unsigned(* * sector_free_c) = new int unsigned * [2];
    int unsigned(* * sector_used_c) = new int unsigned * [2];
    int unsigned(* * sector_id) = new int unsigned * [2];
    int unsigned(* * block_id) = new int unsigned * [2];
    bool(* * sector_smarker) = new bool * [2];
    bool(* * block_smarker) = new bool * [2];
    bool(has_dbuff_init) = false;

    // sector count = block amount / sector count = amout of blocks per sector
    __dbuff_type(* * dbuff_blocks) = new __dbuff_type * [2];
} ;
typedef dynamic_buffer <int> dbint_t;
}
# endif /*__dynamic__buffer__hpp__*/
