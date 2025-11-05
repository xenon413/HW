/**
    This file contains the main() function.
*/
#include <avr/io.h>
#include "pitches.h"

;.extern   init
.extern   delay
.extern   w_tone
.extern   w_noTone

.section .text

.global setup
.global loop

.equ    RBPIN10,10
/**
 * setup function
 */
setup:
    lds   r16, MCUCR
    cbr   r16, PUD
    sts   MCUCR, r16 

    ;pin4
    cbi   _SFR_IO_ADDR(DDRD), PIN4
    sbi   _SFR_IO_ADDR(PORTD), PIN4

    ;pin3
    cbi   _SFR_IO_ADDR(DDRD), PIN3
    sbi   _SFR_IO_ADDR(PORTD), PIN3

    ;pin2
    cbi   _SFR_IO_ADDR(DDRD), PIN2
    sbi   _SFR_IO_ADDR(PORTD), PIN2

    sbi   _SFR_IO_ADDR(DDRB), PIN2
    ret   

/**
 * loop function
 */
loop:

    ldi     r22, 0x0f ; 500
    ldi     r23, 0x00
    ldi     r24, 0x00
    ldi     r25, 0x00
    call    delay

    sbic    _SFR_IO_ADDR(PIND), PIN4
    rjmp    button2

    ldi     r24, RBPIN10
    ldi     r22, lo8(NOTE_C4)
    ldi     r23, hi8(NOTE_C4)
    call    w_tone
    rjmp    done

button2:
    sbic    _SFR_IO_ADDR(PIND), PIN3
    rjmp    button3

    ldi     r24, RBPIN10
    ldi     r22, lo8(NOTE_D4)
    ldi     r23, hi8(NOTE_D4)
    call    w_tone
    rjmp    done

button3:
    sbic    _SFR_IO_ADDR(PIND), PIN2
    rjmp    notone

    ldi     r24, RBPIN10
    ldi     r22, lo8(NOTE_E4)
    ldi     r23, hi8(NOTE_E4)
    call    w_tone
    rjmp    done

notone:

    ldi     r24, RBPIN10
    call    w_noTone

done:
  ret

