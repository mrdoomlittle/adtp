# include "pin_manager.hpp"

/* Created and Designed by mrdoomlittle
* Github: https://github.com/mrdoomlittle
* Email: doctordoomlittle@gmail.com
*/

namespace itmp
{
pin_manager::pin_manager()
{
    bool temp = false; // this will be replaced later its just a quick fix
    (this-> infi_pid_sstate_list).darr_init((this-> digit_infi_pcount), 1);
    (this-> infi_pstate_list).darr_init((this-> digit_infi_pcount), 1);
    (this-> infi_pmode_list).darr_init((this-> digit_infi_pcount), 1);

    (this-> digit_infi_pid_list).darr_init((this-> digit_infi_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_infi_pcount); x ++)
        (this-> infi_pid_sstate_list).set_darr_ilayer(&temp, 0, x);

    (this-> info_pid_sstate_list).darr_init((this-> digit_info_pcount), 1);
    (this-> info_pstate_list).darr_init((this-> digit_info_pcount), 1);
    (this-> info_pmode_list).darr_init((this-> digit_info_pcount), 1);

    (this-> digit_info_pid_list).darr_init((this-> digit_info_pcount), 1);

    for (int unsigned(x ) = 0; x != (this-> digit_info_pcount); x ++)
        (this-> info_pid_sstate_list).set_darr_ilayer(&temp, 0, x);
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
(pin_manager::set_infi_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> infi_clock_ppos_count) = __clock_ppos_count;
}
void
(pin_manager::set_info_clock_ppos_count(int unsigned(__clock_ppos_count)))
{
    (this-> info_clock_ppos_count) = __clock_ppos_count;
}

int unsigned
(pin_manager::get_mio_clock_ppos_count())
{
    return((this-> mio_clock_ppos_count));
}
int unsigned
(pin_manager::get_infi_clock_ppos_count())
{
    return((this-> infi_clock_ppos_count));
}
int unsigned
(pin_manager::get_info_clock_ppos_count())
{
    return((this-> info_clock_ppos_count));
}

void
(pin_manager::set_mio_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_mio_clock_pid_sstate (true) );

    (this-> digit_mio_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_infi_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_infi_clock_pid_sstate (true) );

    (this-> digit_infi_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_info_clock_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_info_clock_pid_sstate (true) );

    (this-> digit_info_clock_pid ) = __digit_pid;
}
void
(pin_manager::set_infi_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_infi_latch_pid_sstate (true) );

    (this-> digit_infi_latch_pid ) = __digit_pid;
}
void
(pin_manager::set_info_latch_pid (uint8_t(__digit_pid ) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_info_latch_pid_sstate (true) );

    (this-> digit_info_latch_pid ) = __digit_pid;
}

uint8_t
(pin_manager::get_mio_clock_pid( ) )
{
    return ( (this-> digit_mio_clock_pid) );
}
uint8_t
(pin_manager::get_infi_clock_pid( ) )
{
    return ( (this-> digit_infi_clock_pid) );
}
uint8_t
(pin_manager::get_info_clock_pid( ) )
{
    return ( (this-> digit_info_clock_pid) );
}
uint8_t
(pin_manager::get_infi_latch_pid( ) )
{
    return ( (this-> digit_infi_latch_pid) );
}
uint8_t
(pin_manager::get_info_latch_pid( ) )
{
    return ( (this-> digit_info_latch_pid) );
}

void
(pin_manager::uset_mio_clock_pid( ) )
{
    (this-> set_mio_clock_pid_sstate (false) );
}
void
(pin_manager::uset_infi_clock_pid( ) )
{
    (this-> set_infi_clock_pid_sstate (false) );
}
void
(pin_manager::uset_info_clock_pid( ) )
{
    (this-> set_info_clock_pid_sstate (false) );
}
void
(pin_manager::uset_infi_latch_pid( ) )
{
    (this-> set_infi_latch_pid_sstate (false) );
}
void
(pin_manager::uset_info_latch_pid( ) )
{
    (this-> set_info_latch_pid_sstate (false) );
}

void
(pin_manager::set_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> mio_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_infi_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> infi_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_info_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> info_clock_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_infi_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> infi_latch_pid_sstate ) = __pid_sstate;
}
void
(pin_manager::set_info_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    (this-> info_latch_pid_sstate ) = __pid_sstate;
}

bool
(pin_manager::get_mio_clock_pid_sstate( ) )
{
    return ( (this-> mio_clock_pid_sstate) );
}
bool
(pin_manager::get_infi_clock_pid_sstate( ) )
{
    return ( (this-> infi_clock_pid_sstate) );
}
bool
(pin_manager::get_info_clock_pid_sstate( ) )
{
    return ( (this-> info_clock_pid_sstate) );
}
bool
(pin_manager::get_infi_latch_pid_sstate( ) )
{
    return ( (this-> infi_latch_pid_sstate) );
}
bool
(pin_manager::get_info_latch_pid_sstate( ) )
{
    return ( (this-> info_latch_pid_sstate) );
}

bool
(pin_manager::is_mio_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_mio_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_infi_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_infi_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_info_clock_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_info_clock_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_infi_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_infi_latch_pid_sstate( )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_info_latch_pid_sstate (bool(__pid_sstate ) ) )
{
    return ( (this-> get_info_latch_pid_sstate( )) == __pid_sstate? true : false);
}

void
(pin_manager::update_infi_clock_pstate(int(__infi_clock_pstate)))
{
    (this-> infi_clock_pstate) = __infi_clock_pstate;
}
void
(pin_manager::update_info_clock_pstate(int(__info_clock_pstate)))
{
    (this-> info_clock_pstate) = __info_clock_pstate;
}
void
(pin_manager::update_infi_latch_pstate(int(__infi_latch_pstate)))
{
    (this-> infi_latch_pstate) = __infi_latch_pstate;
}
void
(pin_manager::update_info_latch_pstate(int(__info_latch_pstate)))
{
    (this-> info_latch_pstate) = __info_latch_pstate;
}

int
(pin_manager::get_infi_clock_pstate( ) )
{
    return ((this-> infi_clock_pstate));
}
int
(pin_manager::get_info_clock_pstate( ) )
{
    return((this-> info_clock_pstate));
}
int
(pin_manager::get_infi_latch_pstate( ) )
{
    return((this-> infi_latch_pstate));
}
int
(pin_manager::get_info_latch_pstate( ) )
{
    return((this-> info_latch_pstate));
}

int
(pin_manager::get_infi_clock_pmode( ) )
{
    return((this-> infi_clock_pmode));
}
int
(pin_manager::get_info_clock_pmode( ) )
{
    return((this-> info_clock_pmode));
}
int
(pin_manager::get_infi_latch_pmode( ) )
{
    return((this-> infi_latch_pmode));
}
int
(pin_manager::get_info_latch_pmode( ) )
{
    return((this-> info_latch_pmode));
}

void
(pin_manager::set_infi_pid(uint8_t(__digit_pid), int unsigned(__infi_pid_pos)))
{
    (this-> set_infi_pid_sstate(true, __infi_pid_pos));

    (this-> digit_infi_pid_list).set_darr_ilayer(&__digit_pid, 0, __infi_pid_pos);
}
void
(pin_manager::set_info_pid(uint8_t(__digit_pid), int unsigned(__info_pid_pos)))
{
    (this-> set_info_pid_sstate(true, __info_pid_pos));

    (this-> digit_info_pid_list).set_darr_ilayer(&__digit_pid, 0, __info_pid_pos);
}

uint8_t
(pin_manager::get_infi_pid(int unsigned(__infi_pid_pos)))
{
    return (*(this-> digit_infi_pid_list).get_darr_ilayer(0, __infi_pid_pos));
}
uint8_t
(pin_manager::get_info_pid(int unsigned(__info_pid_pos)))
{
    return (*(this-> digit_info_pid_list).get_darr_ilayer(0, __info_pid_pos));
}

void
(pin_manager::uset_infi_pid(int unsigned(__infi_pid_pos)))
{
    (this-> set_infi_pid_sstate(false, __infi_pid_pos));
}
void
(pin_manager::uset_info_pid(int unsigned(__info_pid_pos)))
{
    (this-> set_info_pid_sstate(false, __info_pid_pos));
}

void
(pin_manager::set_infi_pid_sstate(bool(__pid_sstate ), int unsigned(__infi_pid_pos)))
{
    (this-> infi_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __infi_pid_pos);
}
void
(pin_manager::set_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)))
{
    (this-> info_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __info_pid_pos);
}

bool
(pin_manager::get_infi_pid_sstate(int unsigned(__infi_pid_pos)))
{
    return (*(this-> infi_pid_sstate_list).get_darr_ilayer(0, __infi_pid_pos));
}
bool
(pin_manager::get_info_pid_sstate(int unsigned(__info_pid_pos)))
{
    return (*(this-> info_pid_sstate_list).get_darr_ilayer(0, __info_pid_pos));
}

bool
(pin_manager::is_infi_pid_sstate(bool(__pid_sstate ) ,int unsigned(__infi_pid_pos)))
{
    return ( (this-> get_infi_pid_sstate(__infi_pid_pos)) == __pid_sstate? true : false);
}
bool
(pin_manager::is_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)))
{
    return ( (this-> get_info_pid_sstate(__info_pid_pos)) == __pid_sstate? true : false);
} }
