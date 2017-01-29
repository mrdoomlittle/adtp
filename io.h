# ifndef __io__h
# define __io__h

# ifdef __cplusplus
extern "C"
{
# endif

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# ifdef F_CPU
	# include <util/delay.h>
# endif

# define true 1
# define false 0

# ifdef ARC64
	typedef uint64_t uint_t;
	typedef int64_t int_t;
# elif ARC32
	typedef uint32_t uint_t;
    typedef int32_t int_t;
# elif ARC16
	typedef uint16_t uint_t;
    typedef int16_t int_t;
# elif ARC8
	typedef uint8_t uint_t;
    typedef int8_t int_t;
# else
	typedef int unsigned uint_t;
    typedef int int_t;
# endif

/* how many times should it read the input.
* NOTE: this will set the bit to the most common
* pin state. depending on how many times it dectets
* a high or low state.
*/
# define TMP_IRRANGE 16

/* input and output clock pin ids.
*/
# define TMP_ICLK_PID 2
# define TMP_OCLK_PID 3

/* input and output data pin ids.
*/
# define TMP_DATI_PID 4
# define TMP_DATO_PID 5

/* ready to send & ready to receive pin ids.
*/
# define TMP_RSEND_PID 6
# define TMP_RRECV_PID 7

/* read and write holdup in clock cycles/ticks
*/
# define TMP_RHOLDUP_CC 0
# define TMP_WHOLDUP_CC 0

/* how long should it wait untill
* to shifts along to the next bit.
*/
# define TMP_SRWAIT_MS 0.5

/* if this pin if set high then it will skip
* the init wait stage.
*/
# define TMP_SINIT_PID 8

# ifndef __cplusplus
	# define DIGITAL_HIGH 1
	# define DIGITAL_LOW 0
# endif

# define DIGITAL_OUT 0x1
# define DIGITAL_IN 0x0

# ifndef __cplusplus
	typedef uint8_t bool;
# endif

struct packet
{
	uint8_t src_port[2], dest_port[2];
	uint8_t reserved_data[2];
} _packet_t;

typedef struct buff {
	uint8_t * ptr_to_data;
	size_t amount_of_bytes;
} io_buff_t;

extern io_buff_t * io_buff(uint8_t *, size_t);

struct io
{
	/* because the io buffers are initialized dynamicly, this forces us
	* to have to store the buffer lengths hear.
	*/
	uint_t ibuff_length, obuff_length;

	/* any incomming and outgoing data will be sotred
	* hear temporarily untill job is complete/finished.
	*/
	uint8_t * dati_buff, * dato_buff;
	int_t ibuff_point, obuff_point;

	uint_t cc_till_read, cc_till_write;
	bool is_iclk_ready, is_oclk_ready;

	bool reading_idat, writing_odat;
	uint_t idat_bpoint, odat_bpoint;
	bool already_inited;

	/* pointers to the functions that control the Atmega328 pins.
	*/
	void (* set_pmode_fptr) (uint8_t, uint8_t);
	void (* set_pstate_fptr) (uint8_t, uint8_t);
	uint8_t (* get_pstate_fptr) (uint8_t);
};

extern void clean_ibuff(struct io *);
extern void clean_ibuff(struct io *);

extern void send(struct io *, io_buff_t *);
extern void recv(struct io *, io_buff_t *);

extern uint8_t * get_from_ibuff(struct io *, size_t);
extern void add_to_obuff(struct io *, uint8_t *, size_t);

extern bool is_iclk_pstate(struct io *, uint8_t);
extern bool is_oclk_pstate(struct io *, uint8_t);

extern uint8_t init(struct io *, uint_t, uint_t);
extern uint8_t tick(struct io *);

# ifdef __cplusplus
}
# endif
# endif /*__io_h*/
