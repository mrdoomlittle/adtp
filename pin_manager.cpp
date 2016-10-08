# include "pin_manager.hpp"

/* Created and Designed by MrDoomLittle
* Github URL: https://github.com/mrdoomlittle
* Email Addr: doctordoomlittle@gmail.com
* For Current Infomation about This Project
* See the File Called: ( INFOMATION )
*/

namespace tmp
{
pin_manager::pin_manager(int unsigned(__interface_count))
{
    bool temp = false; // this will be replaced later its just a quick fix

    (this-> digit_dati_pcount).darr_init(1, __interface_count);
    (this-> digit_dato_pcount).darr_init(1, __interface_count);
    for(int unsigned x = 0; x != __interface_count; x ++)
    {
        int unsigned c = 2;
        (this-> digit_dati_pcount).set_darr_ilayer(&c, x, 0);
        (this-> digit_dato_pcount).set_darr_ilayer(&c, x, 0);
    }

    (this-> digit_mio_clock_pid).darr_init(1, __interface_count);
    (this-> digit_dati_clock_pid).darr_init(1, __interface_count);
    (this-> digit_dato_clock_pid).darr_init(1, __interface_count);
    (this-> digit_dati_latch_pid).darr_init(1, __interface_count);
    (this-> digit_dato_latch_pid).darr_init(1, __interface_count);

    (this-> mio_clock_pid_sstate).darr_init(1, __interface_count);
    (this-> dati_clock_pid_sstate).darr_init(1, __interface_count);
    (this-> dato_clock_pid_sstate).darr_init(1, __interface_count);
    (this-> dati_latch_pid_sstate).darr_init(1, __interface_count);
    (this-> dato_latch_pid_sstate).darr_init(1, __interface_count);

    (this-> mio_clock_ppos_count).darr_init(1, __interface_count);
    (this-> dati_clock_ppos_count).darr_init(1, __interface_count);
    (this-> dato_clock_ppos_count).darr_init(1, __interface_count);

    (this-> mio_clock_pneg_count).darr_init(1, __interface_count);
    (this-> dati_clock_pneg_count).darr_init(1, __interface_count);
    (this-> dato_clock_pneg_count).darr_init(1, __interface_count);

    (this-> mio_clock_pstate).darr_init(1, __interface_count);
    (this-> dati_clock_pstate).darr_init(1, __interface_count);
    (this-> dato_clock_pstate).darr_init(1, __interface_count);
    (this-> dati_latch_pstate).darr_init(1, __interface_count);
    (this-> dato_latch_pstate).darr_init(1, __interface_count);
    int low = (tmp_config::digit_pin_low_state);

    for (int unsigned(y ) = 0; y != __interface_count; y ++)
    {
        (this-> mio_clock_pstate).set_darr_ilayer(&low, y, 0);
        (this-> dati_clock_pstate).set_darr_ilayer(&low, y, 0);
        (this-> dato_clock_pstate).set_darr_ilayer(&low, y, 0);
        (this-> dati_latch_pstate).set_darr_ilayer(&low, y, 0);
        (this-> dato_latch_pstate).set_darr_ilayer(&low, y, 0);
    }

    (this-> mio_clock_pmode).darr_init(1, __interface_count);
    (this-> dati_clock_pmode).darr_init(1, __interface_count);
    (this-> dato_clock_pmode).darr_init(1, __interface_count);
    (this-> dati_latch_pmode).darr_init(1, __interface_count);
    (this-> dato_latch_pmode).darr_init(1, __interface_count);
    for (int unsigned(y ) = 0; y != __interface_count; y ++)
    {
        (this-> mio_clock_pmode).set_darr_ilayer(&low, y, 0);
        (this-> dati_clock_pmode).set_darr_ilayer(&low, y, 0);
        (this-> dato_clock_pmode).set_darr_ilayer(&low, y, 0);
        (this-> dati_latch_pmode).set_darr_ilayer(&low, y, 0);
        (this-> dato_latch_pmode).set_darr_ilayer(&low, y, 0);
    }

    for (int unsigned(y ) = 0; y != __interface_count; y ++)
    {
        (this-> dati_pid_sstate_list).darr_init(*(this-> digit_dati_pcount).get_darr_ilayer(y, 0), __interface_count);
        (this-> dati_pstate_list).darr_init(*(this-> digit_dati_pcount).get_darr_ilayer(y, 0), __interface_count);
        (this-> dati_pmode_list).darr_init(*(this-> digit_dati_pcount).get_darr_ilayer(y, 0), __interface_count);

        (this-> digit_dati_pid_list).darr_init(*(this-> digit_dati_pcount).get_darr_ilayer(y, 0), __interface_count);
    }

    for (int unsigned(y ) = 0; y != __interface_count; y ++)
        for (int unsigned(x ) = 0; x != *(this-> digit_dati_pcount).get_darr_ilayer(y, 0); x ++)
            (this-> dati_pid_sstate_list).set_darr_ilayer(&temp, y, x);

    for (int unsigned(y ) = 0; y != __interface_count; y ++)
    {
        (this-> dato_pid_sstate_list).darr_init(*(this-> digit_dato_pcount).get_darr_ilayer(y, 0), __interface_count);
        (this-> dato_pstate_list).darr_init(*(this-> digit_dato_pcount).get_darr_ilayer(y, 0), __interface_count);
        (this-> dato_pmode_list).darr_init(*(this-> digit_dato_pcount).get_darr_ilayer(y, 0), __interface_count);

        (this-> digit_dato_pid_list).darr_init(*(this-> digit_dato_pcount).get_darr_ilayer(y, 0), __interface_count);
    }

    for (int unsigned(y ) = 0; y != __interface_count; y ++)
        for (int unsigned(x ) = 0; x != *(this-> digit_dato_pcount).get_darr_ilayer(y, 0); x ++)
            (this-> dato_pid_sstate_list).set_darr_ilayer(&temp, y, x);

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
(pin_manager::set_mio_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id)))
{
    (this-> mio_clock_ppos_count).set_darr_ilayer(&__clock_ppos_count, __interface_id, 0);
}
void
(pin_manager::set_dati_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id)))
{
    (this-> dati_clock_ppos_count).set_darr_ilayer(&__clock_ppos_count, __interface_id, 0);
}
void
(pin_manager::set_dato_clock_ppos_count(int unsigned(__clock_ppos_count), int unsigned(__interface_id)))
{
    (this-> dato_clock_ppos_count).set_darr_ilayer(&__clock_ppos_count, __interface_id, 0);
}

int unsigned
(pin_manager::get_mio_clock_ppos_count(int unsigned(__interface_id)))
{
    return(*(this-> mio_clock_ppos_count).get_darr_ilayer(__interface_id, 0));
}
int unsigned
(pin_manager::get_dati_clock_ppos_count(int unsigned(__interface_id)))
{
    return(*(this-> dati_clock_ppos_count).get_darr_ilayer(__interface_id, 0));
}
int unsigned
(pin_manager::get_dato_clock_ppos_count(int unsigned(__interface_id)))
{
    return(*(this-> dato_clock_ppos_count).get_darr_ilayer(__interface_id, 0));
}

void
(pin_manager::set_mio_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id)))
{
    (this-> mio_clock_pneg_count).set_darr_ilayer(&__clock_pneg_count, __interface_id, 0);
}
void
(pin_manager::set_dati_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id)))
{
    (this-> dati_clock_pneg_count).set_darr_ilayer(&__clock_pneg_count, __interface_id, 0);
}
void
(pin_manager::set_dato_clock_pneg_count(int unsigned(__clock_pneg_count), int unsigned(__interface_id)))
{
    (this-> dato_clock_pneg_count).set_darr_ilayer(&__clock_pneg_count, __interface_id, 0);
}

int unsigned
(pin_manager::get_mio_clock_pneg_count(int unsigned(__interface_id)))
{
    return(*(this-> mio_clock_pneg_count).get_darr_ilayer(__interface_id, 0));
}
int unsigned
(pin_manager::get_dati_clock_pneg_count(int unsigned(__interface_id)))
{
    return(*(this-> dati_clock_pneg_count).get_darr_ilayer(__interface_id, 0));
}
int unsigned
(pin_manager::get_dato_clock_pneg_count(int unsigned(__interface_id)))
{
    return(*(this-> dato_clock_pneg_count).get_darr_ilayer(__interface_id, 0));
}

void
(pin_manager::set_mio_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_mio_clock_pid_sstate (true, __interface_id) );

    (this-> digit_mio_clock_pid ).set_darr_ilayer(&__digit_pid, __interface_id, 0);
}
void
(pin_manager::set_dati_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dati_clock_pid_sstate (true, __interface_id) );

    (this-> digit_dati_clock_pid ).set_darr_ilayer(&__digit_pid, __interface_id, 0);
}
void
(pin_manager::set_dato_clock_pid (uint8_t(__digit_pid ), int unsigned(__interface_id) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dato_clock_pid_sstate (true, __interface_id) );

    (this-> digit_dato_clock_pid ).set_darr_ilayer(&__digit_pid, __interface_id, 0);
}
void
(pin_manager::set_dati_latch_pid (uint8_t(__digit_pid ), int unsigned(__interface_id) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dati_latch_pid_sstate (true, __interface_id) );

    (this-> digit_dati_latch_pid ).set_darr_ilayer(&__digit_pid, __interface_id, 0);
}
void
(pin_manager::set_dato_latch_pid (uint8_t(__digit_pid ), int unsigned(__interface_id) ) )
{
    if (!(this-> is_pid_irange (__digit_pid) ) ) return;

    (this-> set_dato_latch_pid_sstate (true, __interface_id) );

    (this-> digit_dato_latch_pid ).set_darr_ilayer(&__digit_pid, __interface_id, 0);
}

uint8_t
(pin_manager::get_mio_clock_pid(int unsigned(__interface_id) ) )
{
    return (* (this-> digit_mio_clock_pid).get_darr_ilayer(__interface_id, 0) );
}
uint8_t
(pin_manager::get_dati_clock_pid(int unsigned(__interface_id) ) )
{
    return (* (this-> digit_dati_clock_pid).get_darr_ilayer(__interface_id, 0) );
}
uint8_t
(pin_manager::get_dato_clock_pid(int unsigned(__interface_id) ) )
{
    return (* (this-> digit_dato_clock_pid).get_darr_ilayer(__interface_id, 0) );
}
uint8_t
(pin_manager::get_dati_latch_pid(int unsigned(__interface_id) ) )
{
    return (* (this-> digit_dati_latch_pid).get_darr_ilayer(__interface_id, 0) );
}
uint8_t
(pin_manager::get_dato_latch_pid(int unsigned(__interface_id) ) )
{
    return (* (this-> digit_dato_latch_pid).get_darr_ilayer(__interface_id, 0) );
}

void
(pin_manager::uset_mio_clock_pid(int unsigned(__interface_id ) ) )
{
    (this-> set_mio_clock_pid_sstate (false, __interface_id) );
}
void
(pin_manager::uset_dati_clock_pid(int unsigned(__interface_id ) ) )
{
    (this-> set_dati_clock_pid_sstate (false, __interface_id) );
}
void
(pin_manager::uset_dato_clock_pid(int unsigned(__interface_id ) ) )
{
    (this-> set_dato_clock_pid_sstate (false, __interface_id) );
}
void
(pin_manager::uset_dati_latch_pid(int unsigned(__interface_id ) ) )
{
    (this-> set_dati_latch_pid_sstate (false, __interface_id) );
}
void
(pin_manager::uset_dato_latch_pid(int unsigned(__interface_id ) ) )
{
    (this-> set_dato_latch_pid_sstate (false, __interface_id) );
}

void
(pin_manager::set_mio_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    (this-> mio_clock_pid_sstate ).set_darr_ilayer(&__pid_sstate, __interface_id, 0);
}
void
(pin_manager::set_dati_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    (this-> dati_clock_pid_sstate ).set_darr_ilayer(&__pid_sstate, __interface_id, 0);
}
void
(pin_manager::set_dato_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    (this-> dato_clock_pid_sstate ).set_darr_ilayer(&__pid_sstate, __interface_id, 0);
}
void
(pin_manager::set_dati_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    (this-> dati_latch_pid_sstate ).set_darr_ilayer(&__pid_sstate, __interface_id, 0);
}
void
(pin_manager::set_dato_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    (this-> dato_latch_pid_sstate ).set_darr_ilayer(&__pid_sstate, __interface_id, 0);
}

bool
(pin_manager::get_mio_clock_pid_sstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> mio_clock_pid_sstate).get_darr_ilayer(__interface_id, 0) );
}
bool
(pin_manager::get_dati_clock_pid_sstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> dati_clock_pid_sstate).get_darr_ilayer(__interface_id, 0) );
}
bool
(pin_manager::get_dato_clock_pid_sstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> dato_clock_pid_sstate).get_darr_ilayer(__interface_id, 0) );
}
bool
(pin_manager::get_dati_latch_pid_sstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> dati_latch_pid_sstate).get_darr_ilayer(__interface_id, 0) );
}
bool
(pin_manager::get_dato_latch_pid_sstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> dato_latch_pid_sstate).get_darr_ilayer(__interface_id, 0) );
}

bool
(pin_manager::is_mio_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    return ( (this-> get_mio_clock_pid_sstate(__interface_id )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dati_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    return ( (this-> get_dati_clock_pid_sstate(__interface_id )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_clock_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    return ( (this-> get_dato_clock_pid_sstate(__interface_id )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dati_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    return ( (this-> get_dati_latch_pid_sstate(__interface_id )) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_latch_pid_sstate (bool(__pid_sstate ), int unsigned(__interface_id ) ) )
{
    return ( (this-> get_dato_latch_pid_sstate(__interface_id )) == __pid_sstate? true : false);
}

void
(pin_manager::update_dati_clock_pstate(int(__dati_clock_pstate), int unsigned(__interface_id )))
{
    (this-> dati_clock_pstate).set_darr_ilayer(&__dati_clock_pstate, __interface_id, 0);
}
void
(pin_manager::update_dato_clock_pstate(int(__dato_clock_pstate), int unsigned(__interface_id )))
{
    (this-> dato_clock_pstate).set_darr_ilayer(&__dato_clock_pstate, __interface_id, 0);
}
void
(pin_manager::update_dati_latch_pstate(int(__dati_latch_pstate), int unsigned(__interface_id )))
{
    (this-> dati_latch_pstate).set_darr_ilayer(&__dati_latch_pstate, __interface_id, 0);
}
void
(pin_manager::update_dato_latch_pstate(int(__dato_latch_pstate), int unsigned(__interface_id )))
{
    (this-> dato_latch_pstate).set_darr_ilayer(&__dato_latch_pstate, __interface_id, 0);
}

int
(pin_manager::get_dati_clock_pstate(int unsigned(__interface_id ) ) )
{
    return (* (this-> dati_clock_pstate).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dato_clock_pstate(int unsigned(__interface_id ) ) )
{
    return(* (this-> dato_clock_pstate).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dati_latch_pstate(int unsigned(__interface_id ) ) )
{
    return(* (this-> dati_latch_pstate).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dato_latch_pstate(int unsigned(__interface_id ) ) )
{
    return(* (this-> dato_latch_pstate).get_darr_ilayer(__interface_id, 0));
}

int
(pin_manager::get_dati_clock_pmode(int unsigned(__interface_id ) ) )
{
    return(* (this-> dati_clock_pmode).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dato_clock_pmode(int unsigned(__interface_id ) ) )
{
    return(* (this-> dato_clock_pmode).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dati_latch_pmode(int unsigned(__interface_id ) ) )
{
    return(* (this-> dati_latch_pmode).get_darr_ilayer(__interface_id, 0));
}
int
(pin_manager::get_dato_latch_pmode(int unsigned(__interface_id ) ) )
{
    return(* (this-> dato_latch_pmode).get_darr_ilayer(__interface_id, 0));
}

void
(pin_manager::set_dati_pid(uint8_t(__digit_pid), int unsigned(__dati_pid_pos), int unsigned(__interface_id ) ) )
{
    (this-> set_dati_pid_sstate(true, __dati_pid_pos, __interface_id));

    (this-> digit_dati_pid_list).set_darr_ilayer(&__digit_pid, __interface_id, __dati_pid_pos);
}
void
(pin_manager::set_dato_pid(uint8_t(__digit_pid), int unsigned(__dato_pid_pos), int unsigned(__interface_id ) ) )
{
    (this-> set_dato_pid_sstate(true, __dato_pid_pos, __interface_id));

    (this-> digit_dato_pid_list).set_darr_ilayer(&__digit_pid, __interface_id, __dato_pid_pos);
}

uint8_t
(pin_manager::get_dati_pid(int unsigned(__dati_pid_pos), int unsigned(__interface_id)))
{
    return (*(this-> digit_dati_pid_list).get_darr_ilayer(__interface_id, __dati_pid_pos));
}
uint8_t
(pin_manager::get_dato_pid(int unsigned(__dato_pid_pos), int unsigned(__interface_id)))
{
    return (*(this-> digit_dato_pid_list).get_darr_ilayer(__interface_id, __dato_pid_pos));
}

void
(pin_manager::uset_dati_pid(int unsigned(__dati_pid_pos), int unsigned(__interface_id)))
{
    (this-> set_dati_pid_sstate(false, __dati_pid_pos, __interface_id));
}
void
(pin_manager::uset_dato_pid(int unsigned(__dato_pid_pos), int unsigned(__interface_id)))
{
    (this-> set_dato_pid_sstate(false, __dato_pid_pos, __interface_id));
}

void
(pin_manager::set_dati_pid_sstate(bool(__pid_sstate ), int unsigned(__dati_pid_pos), int unsigned(__interface_id)))
{
    (this-> dati_pid_sstate_list).set_darr_ilayer(&__pid_sstate, __interface_id, __dati_pid_pos);
}
void
(pin_manager::set_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos), int unsigned(__interface_id)))
{
    (this-> dato_pid_sstate_list).set_darr_ilayer(&__pid_sstate, __interface_id, __dato_pid_pos);
}

bool
(pin_manager::get_dati_pid_sstate(int unsigned(__dati_pid_pos), int unsigned(__interface_id)))
{
    return (*(this-> dati_pid_sstate_list).get_darr_ilayer(__interface_id, __dati_pid_pos));
}
bool
(pin_manager::get_dato_pid_sstate(int unsigned(__dato_pid_pos), int unsigned(__interface_id)))
{
    return (*(this-> dato_pid_sstate_list).get_darr_ilayer(__interface_id, __dato_pid_pos));
}

bool
(pin_manager::is_dati_pid_sstate(bool(__pid_sstate ) ,int unsigned(__dati_pid_pos), int unsigned(__interface_id)))
{
    return ( (this-> get_dati_pid_sstate(__dati_pid_pos, __interface_id)) == __pid_sstate? true : false);
}
bool
(pin_manager::is_dato_pid_sstate(bool(__pid_sstate ), int unsigned(__dato_pid_pos), int unsigned(__interface_id)))
{
    return ( (this-> get_dato_pid_sstate(__dato_pid_pos, __interface_id)) == __pid_sstate? true : false);
} }
