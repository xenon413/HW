/** 
 *  This file contains the setup and loop functions.
 */
 #include <avr/io.h>
 
.extern   delay

.section .text

.global setup
.global loop

/**
 * setup function
 */
setup:
    call    init_rnd

    ; set the appropriate data pins to output
    sbi     _SFR_IO_ADDR(DDRD), PIN0
    sbi     _SFR_IO_ADDR(DDRD), PIN1
    sbi     _SFR_IO_ADDR(DDRD), PIN2
    sbi     _SFR_IO_ADDR(DDRD), PIN3
    sbi     _SFR_IO_ADDR(DDRD), PIN4
    sbi     _SFR_IO_ADDR(DDRD), PIN5

    ret

/**
 * loop function
 */
loop:
    ldi     r22, 250 ; (250 millis)
    ldi     r23, 0x00
    ldi     r24, 0x00 ; 0
    ldi     r25, 0x00 ; 0
    call    delay

    call    rnd

    andi    r24, 0x3f
    out     _SFR_IO_ADDR(PORTD), r24
    
    ret
