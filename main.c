# include "io.h"

void set_pmode(uint8_t __pmode, uint8_t __pid) {

}

void set_pstate(uint8_t __pstate, uint8_t __pid) {
	if (__pid == TMP_DATO_PID)
		printf("pin state: %d, pin id: %d\n", __pstate, __pid);
}

bool g[8] = {0, 1, 0, 0, 0, 1, 0, 0};
#define amount 232873;
uint_t count = 0, c = 0, am = amount;
uint8_t bin[8] = {0, 1, 0, 0, 0, 0, 0, 0};
uint8_t get_pstate(uint8_t __pid) {
if (__pid == TMP_ICLK_PID) {
	if (am == 0) {
	uint_t o = g[count];
	if (count == 7)
		count = 0;
	else count ++;

	am = amount;
	return o;
	} else {
		am --;
		return g[count];
	}
} else {
	if (__pid != TMP_OCLK_PID){
		uint8_t out = bin[c];
		if (c == 7)
			c = 0;
		else c ++;
		printf("pin id: %d, ret %d\n", __pid, out);
		return out;
	}
}
return 0;
}

int main(void) {
	struct io __io;

	__io.set_pmode_fptr = &set_pmode;
	__io.set_pstate_fptr = &set_pstate;
	__io.get_pstate_fptr = &get_pstate;
	__io.already_inited = false;

	init(&__io, 2, 2);
	uint8_t x[2] = {1, 2};

	send(&__io, io_buff(x, 2));
}

