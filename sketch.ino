# include "adtp/io_service.hpp"

void (set_digit_pin_mode (uint8_t(__pin_id ), uint8_t(__pin_mode ) ) )
{
    pinMode (__pin_id, __pin_mode);
}

void (set_digit_pin_state (uint8_t(__pin_id ), uint8_t(__pin_state ) ) )
{
    digitalWrite (__pin_id, __pin_state);
}

int (get_digit_pin_state (uint8_t(__pin_id ) ) )
{
    return (digitalRead (__pin_id) );
}

# define LED_INDICATOR true

# if LED_INDICATOR == true

bool(indicator_led_state ) = false;

void (toggle_iled_state ( ) )
{
    indicator_led_state = (indicator_led_state == false? true : false);
}

# endif

void (external_mlinit (adtp::io_service(* _this ) ) )
{

}

void (external_mltick (adtp::io_service(* _this ) ) )
{
# if LED_INDICATOR == true
    pinMode (13, OUTPUT);

    if (indicator_led_state == true)
        digitalWrite (13, HIGH);
    else
        digitalWrite (13, LOW);

    toggle_iled_state( );
# endif
}

void (setup( ) )
{
    adtp::io_service io_service (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & external_mlinit,
        & external_mltick
    );
}

void (loop( ) )
{
// ignore this function as it will not be called
// untill the io_service main loop it exited
}
