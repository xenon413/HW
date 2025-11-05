/**
 * Manage pwn 2A (pin D11)
 */
#include <avr/io.h>

.section .text

/**
 * Initialize pwm 2A (pin D11)
 */
.global init_pwm11

init_pwm11:
    push r16

    sbi  _SFR_IO_ADDR(DDRB), PIN3 ;set port b pin 3 for output

    ldi r16, 0x00
    sts OCR2A, r16

    ldi r16, (1 << COM2A1 | 1 << WGM21 | 1 << WGM20) ; non-inverting mode, Fast PWM
    sts TCCR2A, r16

    ldi r16, (1 << CS22 | 1 << CS21)               ;set prescaler/divider
    sts TCCR2B, r16

    pop r16
    ret

/**
 * set the pwm 2A (pin D11)
 * r24 contains the function argument
 */
.global set_pwm11

set_pwm11:
    sts OCR2A, r24
    ret
