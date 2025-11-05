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
    ldi     r16,0xff
    sts     .state, r16
    sbi     _SFR_IO_ADDR(DDRB), PIN5
    sbi     _SFR_IO_ADDR(DDRB), PIN4
    ret

/**
 * loop function
 */
loop:
    ldi     r24, 0x00 ; 0
    call    read_adc
    ;ldi     r22, 0xe8 ; 1 second (1000 millis)
    ;ldi     r23, 0x03
    ldi     r24, 0x00 ; 0
    ldi     r25, 0x00 ; 0
    call    delay

    lds      r16, .state
    com     r16
    breq    .ledoff
    sbi     _SFR_IO_ADDR(PORTB), PIN5
    cbi     _SFR_IO_ADDR(PORTB), PIN4
    rjmp    .leddone

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
 
