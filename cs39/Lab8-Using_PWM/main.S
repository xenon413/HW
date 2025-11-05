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
    call    init_adc
    call    init_pwm11
    ret

/**
 * loop function
 */
loop:
    ldi     r22, 0x0F ;(15 millis)
    ldi     r23, 0x00
    ldi     r24, 0x00 ; 0
    ldi     r25, 0x00 ; 0
    call    delay

    ldi     r24, 0x00
    call    read_adc

    lsr     r25
    ror     r24
    lsr     r25
    ror     r24

    call    set_pwm11
    ret

.ledoff:
    cbi     _SFR_IO_ADDR(PORTB), PIN5
    sbi     _SFR_IO_ADDR(PORTB), PIN4

.leddone:
    sts      .state, r16
    ret

/**
 * Variables
 */
 .section .data

.state:  .space  1
 
