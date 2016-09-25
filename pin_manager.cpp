# include "pin_manager.hpp"

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

namespace dtmp
{
pin_manager::pin_manager()
{
    bool temp = false; // this will be replaced later its just a quick fix
    (this-> dtai_pid_sstate_list).darr_init((this-> digit_dtai_pcount), 1);
    (this-> dtai_pstate_list).darr_init((this-> digit_dtai_pcount), 1);
    (this-> dtai_pmode_list).darr_init((this-> digit_dtai_pcount), 1);

    (this-> digit_dtai_pid_list).darr_init((this-> digit_dtai_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_dtai_pcount); x ++)
        (this-> dtai_pid_sstate_list).set_darr_ilayer(&temp, 0, x);

    (this-> dtao_pid_sstate_list).darr_init((this-> digit_dtao_pcount), 1);
    (this-> dtao_pstate_list).darr_init((this-> digit_dtao_pcount), 1);
    (this-> dtao_pmode_list).darr_init((this-> digit_dtao_pcount), 1);

    (this-> digit_dtao_pid_list).darr_init((this-> digit_dtao_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_dtao_pcount); x ++)
        (this-> dtao_pid_sstate_list).set_darr_ilayer(&temp, 0, x);
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
(pin_manager::set_dtai_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> dtai_clock_ppos_count) = __clock_ppos_count;
}
void
(pin_manager::set_dtao_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> dtao_clock_ppos_count) = __clock_ppos_count;
}

int unsigned
(pin_manager::get_mio_clock_ppos_count())
{
    return((this-> mio_clock_ppos_count));
}
int unsigned
(pin_manager::get_dtai_clock_ppos_count())
{
    return((this-> dtai_clock_ppos_count));
}
int unsigned
(pin_manager::get_dtao_clock_ppos_count())
{
    return((this-> dtao_clock_ppos_count));
}

void
(pin_manager::set_mio_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> mio_clock_pneg_count) = __clock_pneg_count;
}
void
(pin_manager::set_dtai_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> dtai_clock_pneg_count) = __clock_pneg_count;
}
void
(pin_manager::set_dtao_clock_pneg_count(int unsigned(__clock_pneg_count)))
{
    (this-> dtao_clock_pneg_count) = __clock_pneg_count;
}

int unsigned
(pin_manager::get_mio_clock_pneg_count())
{
    return((this-> mio_clock_pneg_count));
}
int unsigned
(pin_manager::get_dtai_clock_pneg_count())
{
    return((this-> dtai_clock_pneg_count));
}
int unsigned
(pin_manager::get_dtao_clock_pneg_count())
{
    return((this-> dtao_clock_pneg_count));
}

void
(pin_manager::set_mio_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_mio_clock_pid_sstate (true) );

    (this-> digit_mio_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dtai_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dtai_clock_pid_sstate (true) );

    (this-> digit_dtai_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dtao_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dtao_clock_pid_sstate (true) );

    (this-> digit_dtao_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_dtai_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dtai_latch_pid_sstate (true) );

    (this-> digit_dtai_latch_pid ) = __digit_pid;
}
void
(pin_manager::set_dtao_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dtao_latch_pid_sstate (true) );

    (this-> digit_dtao_latch_pid ) = __digit_pid;
}

uint8_t
(pin_manager::get_mio_clock_pid( ) )
{
    return ( (this-> digit_mio_clock_pid) );
}
uint8_t
(pin_manager::get_dtai_clock_pid( ) )
{
    return ( (this-> digit_dtai_clock_pid) );
}
uint8_t
(pin_manager::get_dtao_clock_pid( ) )
{
    return ( (this-> digit_dtao_clock_pid) );
}
uint8_t
(pin_manager::get_dtai_latch_pid( ) )
{
    return ( (this-> digit_dtai_latch_pid) );
}
uint8_t
(pin_manager::get_dtao_latch_pid( ) )
{
    return ( (this-> digit_dtao_latch_pid) );
}

void
(pin_manager::uset_mio_clock_pid( ) )
{
    (this-> set_mio_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dtai_clock_pid( ) )
{
    (this-> set_dtai_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dtao_clock_pid( ) )
{
    (this-> set_dtao_clock_pid_sstate (false) );
}
void
(pin_manager::uset_dtai_latch_pid( ) )
{
    (this-> set_dtai_latch_pid_sstate (false) );
}
void
(pin_manager::uset_dtao_latch_pid( ) )
{
    (this-> set_dtao_latch_pid_sstate (false) );
}

void
(pin_manager::set_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> mio_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dtai_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dtai_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dtao_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dtao_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dtai_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dtai_latch_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_dtao_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> dtao_latch_pid_sstate ) = __pid_sstate;
}

bool
(pin_manager::get_mio_clock_pid_sstate( ) )
{
    return ( (this-> mio_clock_pid_sstate) );
}
bool
(pin_manager::get_dtai_clock_pid_sstate( ) )
{
    return ( (this-> dtai_clock_pid_sstate) );
}
bool
(pin_manager::get_dtao_clock_pid_sstate( ) )
{
    return ( (this-> dtao_clock_pid_sstate) );
}
bool
(pin_manager::get_dtai_latch_pid_sstate( ) )
{
    return ( (this-> dtai_latch_pid_sstate) );
}
bool
(pin_manager::get_dtao_latch_pid_sstate( ) )
{
    return ( (this-> dtao_latch_pid_sstate) );
}

bool
(pin_manager::is_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_mio_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dtai_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dtai_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dtao_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dtao_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dtai_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dtai_latch_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dtao_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_dtao_latch_pid_sstate( )) == __pid_sstate? true : false);
}

void
(pin_manager::update_dtai_clock_pstate(int(__dtai_clock_pstate)))
{
    (this-> dtai_clock_pstate) = __dtai_clock_pstate;
}
void
(pin_manager::update_dtao_clock_pstate(int(__dtao_clock_pstate)))
{
    (this-> dtao_clock_pstate) = __dtao_clock_pstate;
}
void
(pin_manager::update_dtai_latch_pstate(int(__dtai_latch_pstate)))
{
    (this-> dtai_latch_pstate) = __dtai_latch_pstate;
}
void
(pin_manager::update_dtao_latch_pstate(int(__dtao_latch_pstate)))
{
    (this-> dtao_latch_pstate) = __dtao_latch_pstate;
}

int
(pin_manager::get_dtai_clock_pstate( ) )
{
    return ((this-> dtai_clock_pstate));
}
int
(pin_manager::get_dtao_clock_pstate( ) )
{
    return((this-> dtao_clock_pstate));
}
int
(pin_manager::get_dtai_latch_pstate( ) )
{
    return((this-> dtai_latch_pstate));
}
int
(pin_manager::get_dtao_latch_pstate( ) )
{
    return((this-> dtao_latch_pstate));
}

int
(pin_manager::get_dtai_clock_pmode( ) )
{
    return((this-> dtai_clock_pmode));
}
int
(pin_manager::get_dtao_clock_pmode( ) )
{
    return((this-> dtao_clock_pmode));
}
int
(pin_manager::get_dtai_latch_pmode( ) )
{
    return((this-> dtai_latch_pmode));
}
int
(pin_manager::get_dtao_latch_pmode( ) )
{
    return((this-> dtao_latch_pmode));
}

void
(pin_manager::set_dtai_pid(uint8_t(__digit_pid), int unsigned(__dtai_pid_pos)))
{
    (this-> set_dtai_pid_sstate(true, __dtai_pid_pos));

    (this-> digit_dtai_pid_list).set_darr_ilayer(&__digit_pid, 0, __dtai_pid_pos);
}
void
(pin_manager::set_dtao_pid(uint8_t(__digit_pid), int unsigned(__dtao_pid_pos)))
{
    (this-> set_dtao_pid_sstate(true, __dtao_pid_pos));

    (this-> digit_dtao_pid_list).set_darr_ilayer(&__digit_pid, 0, __dtao_pid_pos);
}

uint8_t
(pin_manager::get_dtai_pid(int unsigned(__dtai_pid_pos)))
{
    return (*(this-> digit_dtai_pid_list).get_darr_ilayer(0, __dtai_pid_pos));
}
uint8_t
(pin_manager::get_dtao_pid(int unsigned(__dtao_pid_pos)))
{
    return (*(this-> digit_dtao_pid_list).get_darr_ilayer(0, __dtao_pid_pos));
}

void
(pin_manager::uset_dtai_pid(int unsigned(__dtai_pid_pos)))
{
    (this-> set_dtai_pid_sstate(false, __dtai_pid_pos));
}
void
(pin_manager::uset_dtao_pid(int unsigned(__dtao_pid_pos)))
{
    (this-> set_dtao_pid_sstate(false, __dtao_pid_pos));
}

void
(pin_manager::set_dtai_pid_sstate(bool(__pid_sstate ), int unsigned(__dtai_pid_pos)))
{
    (this-> dtai_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __dtai_pid_pos);
}
void
(pin_manager::set_dtao_pid_sstate(bool(__pid_sstate ), int unsigned(__dtao_pid_pos)))
{
    (this-> dtao_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __dtao_pid_pos);
}

bool
(pin_manager::get_dtai_pid_sstate(int unsigned(__dtai_pid_pos)))
{
    return (*(this-> dtai_pid_sstate_list).get_darr_ilayer(0, __dtai_pid_pos));
}
bool
(pin_manager::get_dtao_pid_sstate(int unsigned(__dtao_pid_pos)))
{
    return (*(this-> dtao_pid_sstate_list).get_darr_ilayer(0, __dtao_pid_pos));
}

bool
(pin_manager::is_dtai_pid_sstate(bool(__pid_sstate ) ,int unsigned(__dtai_pid_pos)))
{
    return ( (this-> get_dtai_pid_sstate(__dtai_pid_pos)) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dtao_pid_sstate(bool(__pid_sstate ), int unsigned(__dtao_pid_pos)))
{
    return ( (this-> get_dtao_pid_sstate(__dtao_pid_pos)) == __pid_sstate? true : false);
} }
