# ifndef __pin__manager__hpp__
# define __pin__manager__hpp__
# include "itmp_config.hpp"

# ifdef ARDUINO
    # include <stdint.h>
# else
    # include <boost/cstdint.hpp>
# endif

namespace itmp { class pin_manager
{
    private :
        uint8_t(digit_clock_pin_id ) = def_digit_clock_pin_id;
        int unsigned
        (* clock_pin_power_state ) = new int unsigned [2];

        uint8_t(digit_latch_pin_id ) = def_digit_latch_pin_id;
        int unsigned
        (* latch_pin_power_state ) = new int unsigned [2];

        int unsigned(digit_i_pin_count ) = def_digit_i_pin_count;
        uint8_t
        (* digit_i_pin_ids) = new uint8_t [(digit_i_pin_count)];
        int unsigned
        (* i_pin_power_state ) = new int unsigned [(digit_i_pin_count)][2];

        int unsigned(digit_o_pin_count ) = def_digit_o_pin_count;
        uint8_t
        (* digit_o_pin_ids) = new uint8_t [(digit_o_pin_count)];
        int unsigned
        (* o_pin_power_state ) = new int unsigned [(digit_o_pin_count)][2];

    public :
        pin_manager( );
        ~pin_manager( );

    private :
        bool (is_pin_id_inrange (uint8_t(__pin_id ), int unsigned(__min ), int unsigned(__max ), bool(__automatic_range ) ) );
        bool (is_pin_state_incheck (uint8_t(__digit_pin_state ) ) );
        bool (is_pin_mode_incheck (uint8_t(__digit_pin_mode ) ) );

        void (set_clock_pin_state (uint8_t(__clock_pin_state ) ) );
        uint8_t (get_clock_pin_state( ) );
        bool (is_clock_pin_state (uint8_t(__clock_pin_state ) ) ); 

        uint8_t(clock_pin_state ) = digit_pin_low_state;

        void (set_latch_pin_state (uint8_t(__latch_pin_state ) ) );
        uint8_t (get_latch_pin_state ( ) );
        bool (is_latch_pin_state (uint8_t(__latch_pin_state ) ) );

        uint8_t(latch_pin_state ) = digit_pin_low_state;

        void (set_o_pin_state (uint8_t(__o_pin_id ), uint8_t (__o_pin_state ) ) );
        uint8_t (get_o_pin_state (uint8_t(__o_pin_id ) ) );
        bool (is_o_pin_state (uint8_t(__o_pin_id), uint8_t (__o_pin_state ) ) );

        uint8_t(* i_pin_state ) = nullptr;

        void (set_i_pin_state (uint8_t(__i_pin_id ), uint8_t (__i_pin_state ) ) );
        uint8_t (get_i_pin_state (uint8_t(__i_pin_id ) ) );
        bool (is_i_pin_state (uint8_t(__i_pin_id ), uint8_t (__i_pin_state ) ) );

        uint8_t(* o_pin_state ) = nullptr; 
} ; }

# endif /*__pin__manager__hpp__*/
