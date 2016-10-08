# ifndef __data__packet__hpp__
# define __data__packet__hpp__
# include "tmp_config.hpp"
# include "bitset.hpp"
# include "bitset_list.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/
// still working on this
namespace tmp { class data_packet
{
    public :
        data_packet()
        {
            (this-> dati_dpheader).bitset_init((tmp_config::def_dati_bitset_length), (this-> dpheader_dati_bitsetc));
            (this-> dati_dpacket).bitset_init((tmp_config::def_dati_bitset_length), 0);

            (this-> dato_dpheader).bitset_init((tmp_config::def_dato_bitset_length), (this-> dpheader_dato_bitsetc));
            (this-> dato_dpacket).bitset_init((tmp_config::def_dati_bitset_length), 0);
        }

        void(set_dati_dpacket_size(int unsigned(__dpacket_size)))
        {


            (this-> dati_dpacket_size) = __dpacket_size;
        }

        int unsigned(get_dati_dpacket_size())
        {
            return((this-> dati_dpacket_size));
        }

        void(set_dato_dpacket_size(int unsigned(__dpacket_size)))
        {

        }

        void(add_bitset_to_dpheader(int unsigned(__bitset_t), uint8_t(* __bitset)))
        {
            switch(__bitset_t)
            {
                case(this-> __dati_bitset):
                    if ((this-> dati_dpheader_pos) == (this-> dpheader_dati_bitsetc))
                        (this-> dati_dpheader_pos) = 0;

                    (this-> dati_dpheader).set_bitset(__bitset, 1, 0, (this-> dati_dpheader_pos));

                    (this-> dati_dpheader_pos) ++;
                    break;
                case(this-> __dato_bitset):
                    if ((this-> dati_dpheader_pos) == (this-> dpheader_dato_bitsetc))
                        (this-> dato_dpheader_pos) = 0;

                    (this-> dato_dpheader).set_bitset(__bitset, 1, 0, (this-> dato_dpheader_pos));

                    (this-> dato_dpheader_pos) ++;
                    break;
            }
        }

        void(add_bitset_to_dpacket(int unsigned(__bitset_t), uint8_t(* __bitset)))
        {

        }

        bool(is_dpheader_complete(int unsigned(__bitset_t)))
        {
            switch(__bitset_t)
            {
                case(this-> __dati_bitset):
                    return((this-> dati_dpheader_pos) == (this-> dpheader_dati_bitsetc)? true : false);
                    //break;
                case(this-> __dato_bitset):
                    return((this-> dati_dpheader_pos) == (this-> dpheader_dato_bitsetc)? true : false);
                    //break;
                default : return false;
            }
        }

        bool(is_dpacket_complete())
        {
            return 0;
        }

        int unsigned(get_dpacket_info(int unsigned(__inf_type)))
        {
            switch(__inf_type)
            {
                case(this-> __dpacket_header_size):
                    return((this-> dpacket_header_size));
                case(this-> __dpheader_dati_bitsetc):
                    return((this-> dpheader_dati_bitsetc));
                case(this-> __dpheader_dato_bitsetc):
                    return((this-> dpheader_dato_bitsetc));
                case(this-> __dati_dpacket_size):
                    return(this-> dati_dpacket_size);
                case(this-> __dato_dpacket_size):
                    return(this-> dato_dpacket_size);
                case(this-> __dati_dpheader_pos):
                    return(this-> dati_dpheader_pos);
                case(this-> __dati_dpacket_pos):
                    return(this-> dati_dpacket_pos);
                case(this-> __dato_dpheader_pos):
                    return(this-> dato_dpheader_pos);
                case(this-> __dato_dpacket_pos):
                    return(this-> dato_dpacket_pos);
                default : return 0;
            }
        }

        bitset_list <uint8_t>(* get_dpheader_ptr(int unsigned(__dat_type)))
        {
            switch(__dat_type)
            {
                case 0: return(&(this-> dati_dpheader));
                case 1: return(&(this-> dato_dpheader));

                default : return nullptr;
            }
        }

        bitset_list <uint8_t>(* get_dpacket_ptr(int unsigned(__dat_type)))
        {
            switch(__dat_type)
            {
                case 0: return(&(this-> dati_dpacket));
                case 1: return(&(this-> dato_dpacket));

                default : return nullptr;
            }
        }

    private :

        enum : int unsigned const
        {
            __dati_bitset,
            __dato_bitset
        };

        enum : int unsigned const
        {
            __dpacket_header_size,
            __dpheader_dati_bitsetc,
            __dpheader_dato_bitsetc,
            __dati_dpacket_size,
            __dato_dpacket_size,
            __dati_dpheader_pos,
            __dati_dpacket_pos,
            __dato_dpheader_pos,
            __dato_dpacket_pos
        };

        int unsigned(dpacket_header_size) = (tmp_config::dpacket_header_size);
        int unsigned(dpheader_dati_bitsetc) = ((tmp_config::dpacket_header_size) / (tmp_config::def_dati_bitset_length));
        int unsigned(dpheader_dato_bitsetc) = ((tmp_config::dpacket_header_size) / (tmp_config::def_dato_bitset_length));
        int unsigned(dati_dpacket_size) = 0;
        int unsigned(dato_dpacket_size) = 0;
        int unsigned(dati_dpheader_pos) = 0;
        int unsigned(dati_dpacket_pos) = 0;

        int unsigned(dato_dpheader_pos) = 0;
        int unsigned(dato_dpacket_pos) = 0;
        bitset_list <uint8_t> dati_dpheader;
        bitset_list <uint8_t> dati_dpacket;

        bitset_list <uint8_t> dato_dpheader;
        bitset_list <uint8_t> dato_dpacket;

} ; }


# endif /*__data__packet__hpp__*/
