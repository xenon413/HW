/**
 * ADC access
 */
#include <avr/io.h>

.section .text

.global init_adc

/**
 * Initialize the ADC system
 */
init_adc:
    push   r16

    ldi   r16, (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
    sts   ADCSRA, r16

    pop r16
    ret

/**
 * Read an ADC channel
 * r24 contains the ADC channel to read
 * r24 contains the return value LSB
 * r25 contains the return value MSB
 */
.global read_adc

read_adc:
   push   r16

   ldi  r16, (1<<REFS0)     ; +5 board voltage reference
   andi r24, 0x0F
   or   r16, r24            ; include channel
   sts  ADMUX, r16

   lds  r16, ADCSRA         ; enable ADC
   ori  r16, (1<<ADSC)
   sts  ADCSRA, r16

.adc_wait:
   lds  r16, ADCSRA         ; wait for conversion complete
   sbrc r16, ADSC           ; skip next instruction if clear
   rjmp .adc_wait

   lds  r24,ADCL            ; return low value
   lds  r25,ADCH            ; return high value

   pop   r16
   ret
