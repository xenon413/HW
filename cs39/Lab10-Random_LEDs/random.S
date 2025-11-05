/**
 * 16 bit random number generator, Linear-feedback shift register
 *
	static unsigned int lfsr = 0xACE1;
	static unsigned int bit;

	uint16_t _fx_rand()
	{
	    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	    return lfsr = (lfsr >> 1) | (bit << 15);
	}
 */
#include <avr/io.h>

.section .text

.global init_rnd

.equ RANDOMSEED, 0xACE1

/*
 * initialize random number generator
 */
init_rnd:
	  push r16

	  ldi	r16, 0x00
	  sts bit,r16
	  sts bit+1,r16

	  ldi	r16, lo8(RANDOMSEED)
	  sts lfsr,r16
	  ldi	r16, hi8(RANDOMSEED)
	  sts lfsr+1,r16

	  pop r16
	  ret

.global rnd

/*
 * Return the next 16 bit psuedo random number
 * r24 - low byte
 * r25 - high byte
 */
rnd:
	  push r16
	  push r17

	  lds	r16, lfsr		; (lfsr >> 0)
	  lds	r17, lfsr+1

	  lds	r24, lfsr		; (lfsr >> 2)
	  lds	r25, lfsr+1
    lsr r25
    ror r24
    lsr r25
    ror r24

    ; ^ XOR
    eor r16, r24
    eor r17, r25

    ; (lfsr >> 3)
    lds r24, lfsr
    lds r25, lfsr+1
    lsr r25
    ror r24
    lsr r25
    ror r24
    lsr r25
    ror r24

    ; ^ XOR
    eor r16, r24
    eor r17, r25

    ; (lfsr >> 5)
    lds r24, lfsr
    lds r25, lfsr+1
    lsr r25
    ror r24
    lsr r25
    ror r24
    lsr r25
    ror r24
    lsr r25
    ror r24
    lsr r25
    ror r24

    ; ^ XOR
    eor r16, r24
    eor r17, r25
    ; AND 0x0001 and save to variable bit
    andi r16, 0x01
    andi r17, 0x00
    sts bit, r16
    sts bit+1, r17

    ; (lfsr >> 1)
    lds r24, lfsr
    lds r25, lfsr+1
    lsr r25
    ror r24

    ; OR (bit << 15)
    lds r22, bit
    lds r23, bit+1
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23
    lsl r22
    rol r23

    or r24, r23
    or r25, r22

    ; save result to variable lfsr
	  sts	lfsr, r24
	  sts	lfsr+1, r25

	  pop	r17
	  pop	r16
	  ret

.section .data

lfsr:	.space 2
bit:	.space 2
