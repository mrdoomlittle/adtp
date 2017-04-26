# TMP
#### Connection:
##### __NODE 0
TMP_RX_OC_PID -> TMP_RX_IC_PID of NODE 1
TMP_TX_OC_PID -> TMP_TX_IC_PID of NODE 1
TMP_TX_PID -> TMP_RX_PID of NODE 1
#### __NODE 1
TMP_RX_OC_PID -> TMP_RX_IC_PID of NODE 0
TMP_TX_OC_PID -> TMP_TX_IC_PID of NODE 0
TMP_TX_PID -> TMP_RX_PID of NODE 0
#### Example:
```
# define TMP_RX_IC_PID 2
# define TMP_RX_OC_PID 3

# define TMP_TX_IC_PID 4
# define TMP_TX_OC_PID 5

# define TMP_RX_PID 6
# define TMP_TX_PID 7

# include "/*tmp_io.h*/"
# include <stdint.h>
void set_pin_mode(uint8_t __pmode, uint8_t __pid) {
/* set pin mode of microcontroller */
}

void set_pin_state(uint8_t __pstate, uint8_t __pid) {
/* set pin state of microcontroller */
}

uint8_t get_pin_state(uint_t __pid) {
/* get pin state of microcontroller */
}

int main(void) {
    struct tmp_io_t tmp_io = {
        .rx_pid = TMP_RX_PID,
        .tx_pid = TMP_TX_PID,
        .rx_ci_pid = TMP_RX_IC_PID,
        .tx_ci_pid = TMP_TX_IC_PID,
        .rx_co_pid = TMP_RX_OC_PID,
        .tx_co_pid = TMP_TX_OC_PID
    };

    tmp_init(&tmp_io, &set_pin_mode, &set_pin_state, &get_pin_state);
    uint8_t data[6];
    /*
    * tmp_send(&tmp_io, tmp_io_buff(data, 6)); -> send 6 bytes to ?
    * tmp_recv(&tmp_io, tmp_io_buff(data, 6)); -> recv 6 bytes from ?
    */
}
```

