# include "pin_manager.hpp"

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

namespace tmp
{
pin_manager::pin_manager()
{
    bool temp = false; // this will be replaced later its just a quick fix
    (this-> dati_pid_sstate_list).darr_init((this-> digit_dati_pcount), 1);
    (this-> dati_pstate_list).darr_init((this-> digit_dati_pcount), 1);
    (this-> dati_pmode_list).darr_init((this-> digit_dati_pcount), 1);

    (this-> digit_dati_pid_list).darr_init((this-> digit_dati_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_dati_pcount); x ++)
        (this-> dati_pid_sstate_list).set_darr_ilayer(&temp, 0, x);

    (this-> dato_pid_sstate_list).darr_init((this-> digit_dato_pcount), 1);
    (this-> dato_pstate_list).darr_init((this-> digit_dato_pcount), 1);
    (this-> dato_pmode_list).darr_init((this-> digit_dato_pcount), 1);

    (this-> digit_dato_pid_list).darr_init((this-> digit_dato_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_dato_pcount); x ++)
        (this-> dato_pid_sstate_list).set_darr_ilayer(&temp, 0, x);
    }

bool
(pin_manager::is_pid_irange (uint8_t(__digit_pid ) ) )
{
    return(true);
}

bool
(pin_manager::is_pstate_icheck (uint8_t(__digit_pstate ) ) )
{
    return(true);
}

bool
(pin_manager::is_pmode_icheck (uint8_t(__digit_pmode ) ) )
{
    return(true);
}
void
(pin_manager::set_mio_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> mio_clock_ppos_count) = __clock_ppos_count;
}
void
(pin_manager::set_dati_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> dati_clock_ppos_count) = __clock_ppos_count;
}
void
(pin_manager::set_dato_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> dato_clock_ppos_count) = __clock_ppos_count;
}

int unsigned
(pin_manager::get_mio_clock_ppos_count())
{
    return((this-> mio_clock_ppos_count));
}
int unsigned
(pin_manager::get_dati_clock_ppos_count())
{
    return((this-> dati_clock_ppos_count));
}
int unsigned
(pin_manager::get_dato_clock_ppos_count())
{
    return((this-> dato_clock_ppos_count));
}

void
(pin_manager::set_mio_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> mio_clock_pneg_count) = __clock_pneg_count;
}
void
(pin_manager::set_dati_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> dati_clock_pneg_count) = __clock_pneg_count;
}
void
(pin_manager::set_dato_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> dato_clock_pneg_count) = __clock_pneg_count;
}

int unsigned
(pin_manager::get_mio_clock_pneg_count())
{
    return((this-> mio_clock_pneg_count));
}
int unsigned
(pin_manager::get_dati_clock_pneg_count())
{
    return((this-> dati_clock_pneg_count));
}
int unsigned
(pin_manager::get_dato_clock_pneg_count())
{
    return((this-> dato_clock_pneg_count));
}

void
(pin_manager::set_mio_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_mio_clock_pid_sstate (true) );

    (this-> digit_mio_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dati_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dati_clock_pid_sstate (true) );

    (this-> digit_dati_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dato_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dato_clock_pid_sstate (true) );

    (this-> digit_dato_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dati_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dati_latch_pid_sstate (true) );

    (this-> digit_dati_latch_pid ) = __digit_pid;
}
void
(pin_manager::set_dato_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dato_latch_pid_sstate (true) );

    (this-> digit_dato_latch_pid ) = __digit_pid;
}

uint8_t
(pin_manager::get_mio_clock_pid( ) )
{
    return ( (this-> digit_mio_clock_pid) );
}
uint8_t
(pin_manager::get_dati_clock_pid( ) )
{
    return ( (this-> digit_dati_clock_pid) );
}
uint8_t
(pin_manager::get_dato_clock_pid( ) )
{
    return ( (this-> digit_dato_clock_pid) );
}
uint8_t
(pin_manager::get_dati_latch_pid( ) )
{
    return ( (this-> digit_dati_latch_pid) );
}
uint8_t
(pin_manager::get_dato_latch_pid( ) )
{
    return ( (this-> digit_dato_latch_pid) );
}

void
(pin_manager::uset_mio_clock_pid( ) )
{
    (this-> set_mio_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dati_clock_pid( ) )
{
    (this-> set_dati_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dato_clock_pid( ) )
{
    (this-> set_dato_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dati_latch_pid( ) )
{
    (this-> set_dati_latch_pid_sstate (false) );
}
void
(pin_manager::uset_dato_latch_pid( ) )
{
    (this-> set_dato_latch_pid_sstate (false) );
}

void
(pin_manager::set_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> mio_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dati_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dati_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dato_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dato_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dati_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dati_latch_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dato_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dato_latch_pid_sstate ) = __pid_sstate;
}

bool
(pin_manager::get_mio_clock_pid_sstate( ) )
{
    return ( (this-> mio_clock_pid_sstate) );
}
bool
(pin_manager::get_dati_clock_pid_sstate( ) )
{
    return ( (this-> dati_clock_pid_sstate) );
}
bool
(pin_manager::get_dato_clock_pid_sstate( ) )
{
    return ( (this-> dato_clock_pid_sstate) );
}
bool
(pin_manager::get_dati_latch_pid_sstate( ) )
{
    return ( (this-> dati_latch_pid_sstate) );
}
bool
(pin_manager::get_dato_latch_pid_sstate( ) )
{
    return ( (this-> dato_latch_pid_sstate) );
}

bool
(pin_manager::is_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_mio_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dati_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dati_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dato_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dati_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dati_latch_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dato_latch_pid_sstate( )) == __pid_sstate? true : false);
}

void
(pin_manager::update_dati_clock_pstate(int(__dati_clock_pstate)))
{
    (this-> dati_clock_pstate) = __dati_clock_pstate;
}
void
(pin_manager::update_dato_clock_pstate(int(__dato_clock_pstate)))
{
    (this-> dato_clock_pstate) = __dato_clock_pstate;
}
void
(pin_manager::update_dati_latch_pstate(int(__dati_latch_pstate)))
{
    (this-> dati_latch_pstate) = __dati_latch_pstate;
}
void
(pin_manager::update_dato_latch_pstate(int(__dato_latch_pstate)))
{
    (this-> dato_latch_pstate) = __dato_latch_pstate;
}

int
(pin_manager::get_dati_clock_pstate( ) )
{
    return ((this-> dati_clock_pstate));
}
int
(pin_manager::get_dato_clock_pstate( ) )
{
    return((this-> dato_clock_pstate));
}
int
(pin_manager::get_dati_latch_pstate( ) )
{
    return((this-> dati_latch_pstate));
}
int
(pin_manager::get_dato_latch_pstate( ) )
{
    return((this-> dato_latch_pstate));
}

int
(pin_manager::get_dati_clock_pmode( ) )
{
    return((this-> dati_clock_pmode));
}
int
(pin_manager::get_dato_clock_pmode( ) )
{
    return((this-> dato_clock_pmode));
}
int
(pin_manager::get_dati_latch_pmode( ) )
{
    return((this-> dati_latch_pmode));
}
int
(pin_manager::get_dato_latch_pmode( ) )
{
    return((this-> dato_latch_pmode));
}

void
(pin_manager::set_dati_pid(uint8_t(__digit_pid), int unsigned(__dati_pid_pos)))
{
    (this-> set_dati_pid_sstate(true, __dati_pid_pos));

    (this-> digit_dati_pid_list).set_darr_ilayer(&__digit_pid, 0, __dati_pid_pos);
}
void
(pin_manager::set_dato_pid(uint8_t(__digit_pid), int unsigned(__dato_pid_pos)))
{
    (this-> set_dato_pid_sstate(true, __dato_pid_pos));

    (this-> digit_dato_pid_list).set_darr_ilayer(&__digit_pid, 0, __dato_pid_pos);
}

uint8_t
(pin_manager::get_dati_pid(int unsigned(__dati_pid_pos)))
{
    return (*(this-> digit_dati_pid_list).get_darr_ilayer(0, __dati_pid_pos));
}
uint8_t
(pin_manager::get_dato_pid(int unsigned(__dato_pid_pos)))
{
    return (*(this-> digit_dato_pid_list).get_darr_ilayer(0, __dato_pid_pos));
}

void
(pin_manager::uset_dati_pid(int unsigned(__dati_pid_pos)))
{
    (this-> set_dati_pid_sstate(false, __dati_pid_pos));
}
void
(pin_manager::uset_dato_pid(int unsigned(__dato_pid_pos)))
{
    (this-> set_dato_pid_sstate(false, __dato_pid_pos));
}

void
(pin_manager::set_dati_pid_sstate(bool(__pid_sstate ), int unsigned(__dati_pid_pos)))
{
    (this-> dati_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __dati_pid_pos);
}
void
(pin_manager::set_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos)))
{
    (this-> dato_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __dato_pid_pos);
}

bool
(pin_manager::get_dati_pid_sstate(int unsigned(__dati_pid_pos)))
{
    return (*(this-> dati_pid_sstate_list).get_darr_ilayer(0, __dati_pid_pos));
}
bool
(pin_manager::get_dato_pid_sstate(int unsigned(__dato_pid_pos)))
{
    return (*(this-> dato_pid_sstate_list).get_darr_ilayer(0, __dato_pid_pos));
}

bool
(pin_manager::is_dati_pid_sstate(bool(__pid_sstate ) ,int unsigned(__dati_pid_pos)))
{
    return ( (this-> get_dati_pid_sstate(__dati_pid_pos)) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos)))
{
    return ( (this-> get_dato_pid_sstate(__dato_pid_pos)) == __pid_sstate? true : false);
} }
