#include <avr/io.h>
.extern   delay
.section .text

.global setup
.global loop

#define DIR_A 	5
#define DIR_B 	4

.global main

setup:
    call	init_pwm11

    sbi   _SFR_IO_ADDR(DDRB), PIN5
    sbi   _SFR_IO_ADDR(DDRB), PIN4

    ret

loop:
; drive forward for 1 second
    sbi     _SFR_IO_ADDR(PINB), PIN5
    cbi     _SFR_IO_ADDR(PINB), PIN4
    ldi     r24, 0xFF
    call    set_pwm11

; brake for 1 second
    ldi     r22, 0xE8
    ldi     r23, 0x03
    ldi     r24, 0
    ldi     r25, 0
    call    delay

; drive backward for 1 second
    cbi     _SFR_IO_ADDR(PINB), PIN5
    sbi     _SFR_IO_ADDR(PINB), PIN4
    ldi     r24, 0xFF
    call    set_pwm11
; brake for 1 second
    ldi     r22, 0xE8
    ldi     r23, 0x03
    ldi     r24, 0
    ldi     r25, 0
    call    delay
    ret
