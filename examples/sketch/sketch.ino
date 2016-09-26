# include <io_service.h>

void
(set_digit_pin_mode (uint8_t(__digit_pid ), uint8_t(__digit_pmode ) ) )
{
    pinMode (__digit_pid, __digit_pmode);
}

void
(set_digit_pin_state (uint8_t(__digit_pid ), uint8_t(__digit_pstate ) ) )
{
    digitalWrite (__digit_pid, __digit_pstate);
}

int
(get_digit_pin_state (uint8_t(__digit_pid ) ) )
{
    return (digitalRead (__digit_pid) );
}

# define LED_INDICATOR true

# if LED_INDICATOR == true

bool(indicator_led_state ) = false;

void
(toggle_iled_state ( ) )
{
    indicator_led_state = (indicator_led_state == false? true : false);
}

# endif

void
(external_mlinit (tmp::io_service(* __io_service ) ) )
{

}

void
(external_mltick (tmp::io_service(* __io_service ) ) )
{
# if LED_INDICATOR == true
    pinMode (13, OUTPUT);

    if (indicator_led_state == true)
        digitalWrite (13, HIGH);
    else
        digitalWrite (13, LOW);

    toggle_iled_state( );
# endif

    if (serialEventRun) serialEventRun( );
}

void
(setup( ) )
{
    tmp::io_service io;

    io.service_init
    (
        & set_digit_pin_mode,
        & set_digit_pin_state,
        & get_digit_pin_state,
        & external_mlinit,
        & external_mltick
    );
}

void
(loop( ) )
{
// ignore this function as it will not be called
// untill the io_service main loop it exited
}
