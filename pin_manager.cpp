# include "pin_manager.hpp"
namespace itmp
{
    pin_manager::pin_manager()
    {
        bool temp = false; // this will be replaced later its just a quick fix
        (this-> infi_pid_sstate_list).darr_init((this-> digit_infi_pcount), 1);
        (this-> digit_infi_pid_list).darr_init((this-> digit_infi_pcount), 1);

        for (int unsigned(x ) = 0; x != (this-> digit_infi_pcount); x ++)
            (this-> infi_pid_sstate_list).set_darr_ilayer(&temp, 0, x);

        (this-> info_pid_sstate_list).darr_init((this-> digit_info_pcount), 1);
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

    }

    bool
    (pin_manager::is_pmode_icheck (uint8_t(__digit_pmode ) ) )
    {

    }

    void
    (pin_manager::set_clock_pid (uint8_t(__digit_pid ) ) )
    {
        if (!(this-> is_pid_irange (__digit_pid) ) ) return;

        (this-> set_clock_pid_sstate (true) );

        (this-> digit_clock_pid ) = __digit_pid;
    }

    uint8_t
    (pin_manager::get_clock_pid( ) )
    {
        return ( (this-> digit_clock_pid) );
    }

    void
    (pin_manager::uset_clock_pid( ) )
    {
        (this-> set_clock_pid_sstate (false) );
    }

    void
    (pin_manager::set_clock_pid_sstate (bool(__pid_sstate ) ) )
    {
        (this-> clock_pid_sstate ) = __pid_sstate;
    }

    bool
    (pin_manager::get_clock_pid_sstate( ) )
    {
        return ( (this-> clock_pid_sstate) );
    }

    bool
    (pin_manager::is_clock_pid_sstate (bool(__pid_sstate ) ) )
    {
        return ( (this-> get_clock_pid_sstate( )) == __pid_sstate? true : false);
    }

    void
    (pin_manager::set_latch_pid (uint8_t(__digit_pid ) ) )
    {
        if (!(this-> is_pid_irange (__digit_pid) ) ) return;

        (this-> set_latch_pid_sstate (true) );

        (this-> digit_latch_pid ) = __digit_pid;
    }

    uint8_t
    (pin_manager::get_latch_pid( ) )
    {
        return ( (this-> digit_latch_pid) );
    }

    void
    (pin_manager::uset_latch_pid( ) )
    {
        (this-> set_latch_pid_sstate (false) );
    }

    void
    (pin_manager::set_latch_pid_sstate (bool(__pid_sstate ) ) )
    {
        (this-> latch_pid_sstate ) = __pid_sstate;
    }

    bool
    (pin_manager::get_latch_pid_sstate( ) )
    {
        return ( (this-> latch_pid_sstate) );
    }

    bool
    (pin_manager::is_latch_pid_sstate (bool(__pid_sstate ) ) )
    {
        return ( (this-> get_latch_pid_sstate( )) == __pid_sstate? true : false);
    }

    void
    (pin_manager::set_infi_pid(uint8_t(__digit_pid), int unsigned(__infi_pid_pos)))
    {
        (this-> set_infi_pid_sstate(true, __infi_pid_pos));

        (this-> digit_infi_pid_list).set_darr_ilayer(&__digit_pid, 0, __infi_pid_pos);
    }

    uint8_t
    (pin_manager::get_infi_pid(int unsigned(__infi_pid_pos)))
    {
        return (*(this-> digit_infi_pid_list).get_darr_ilayer(0, __infi_pid_pos));
    }

    void
    (pin_manager::uset_infi_pid(int unsigned(__infi_pid_pos)))
    {
        (this-> set_infi_pid_sstate(false, __infi_pid_pos));
    }

    void
    (pin_manager::set_infi_pid_sstate(bool(__pid_sstate ), int unsigned(__infi_pid_pos)))
    {
        (this-> infi_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __infi_pid_pos);
    }

    bool
    (pin_manager::get_infi_pid_sstate(int unsigned(__infi_pid_pos)))
    {
        return (*(this-> infi_pid_sstate_list).get_darr_ilayer(0, __infi_pid_pos));
    }

    bool
    (pin_manager::is_infi_pid_sstate(bool(__pid_sstate ) ,int unsigned(__infi_pid_pos)))
    {
        return ( (this-> get_infi_pid_sstate(__infi_pid_pos)) == __pid_sstate? true : false);
    }

    void
    (pin_manager::set_info_pid(uint8_t(__digit_pid), int unsigned(__info_pid_pos)))
    {
        (this-> set_info_pid_sstate(true, __info_pid_pos));

        (this-> digit_info_pid_list).set_darr_ilayer(&__digit_pid, 0, __info_pid_pos);
    }

    uint8_t
    (pin_manager::get_info_pid(int unsigned(__info_pid_pos)))
    {
        return (*(this-> digit_info_pid_list).get_darr_ilayer(0, __info_pid_pos));
    }

    void
    (pin_manager::uset_info_pid(int unsigned(__info_pid_pos)))
    {
        (this-> set_info_pid_sstate(false, __info_pid_pos));
    }

    void
    (pin_manager::set_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)))
    {
        (this-> info_pid_sstate_list).set_darr_ilayer(&__pid_sstate, 0, __info_pid_pos);
    }

    bool
    (pin_manager::get_info_pid_sstate(int unsigned(__info_pid_pos)))
    {
        return (*(this-> info_pid_sstate_list).get_darr_ilayer(0, __info_pid_pos));
    }

    bool
    (pin_manager::is_info_pid_sstate(bool(__pid_sstate ), int unsigned(__info_pid_pos)))
    {
        return ( (this-> get_info_pid_sstate(__info_pid_pos)) == __pid_sstate? true : false);
    }
}
