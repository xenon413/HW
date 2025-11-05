/* This file uses the serial IO of the AVR core and the
 * Atmega328p controller on the Arduino Uno board.
 */

#include <avr/io.h>

.section .text

/**
 * Initialize the serial IO
 */
.global init_serial

init_serial:
	push	  r17
	push  	r16

	ldi   	r17, 0    ; Set baud rate 9600
	ldi  	  r16, 103
	sts  	  UBRR0H, r17
	sts  	  UBRR0L, r16
 
	ldi  	  r16, (1<<RXEN0)|(1<<TXEN0)    ; Enable receiver and transmitter
	sts  	  UCSR0B,r16
  
	ldi  	  r16, (1<<UCSZ01)|(1<<UCSZ00)  ; Set frame format 8 bit data, 1 stop bit
	sts  	  UCSR0C,r16

	pop   	r16
	pop   	r17
 	ret

/**
 * Output a character
 * r24 contains the character to send
 */
.global tx

tx:
   push     r16

.bfwait:                    ; Wait for empty transmit buffer
   lds      r16, UCSR0A     ; Load into r16 from SRAM UCSR0A
   sbrs     r16, UDRE0      ; Skip next instruction If Bit Register is set
   rjmp     .bfwait

   sts      UDR0, r24       ; Put data (r24) into buffer, sends the data

   pop      r16
   ret

/**
 * Check if an input character is available
 * r24 contains zero if false and not zero if true
 */
.global rx_check

rx_check:
	lds		  r24, UCSR0A
	andi	  r24, (1<<RXC0)
	ret

/**
 * Input a character
 * r24 contains the input character
 */
.global rx

rx:
  	push	  r16

.rxwait:                    ; Wait for full receive buffer
	  lds		  r16, UCSR0A
	  sbrs	  r16, RXC0
	  rjmp 	  .rxwait

   	lds 	  r24, UDR0       ; Get and return received data from buffer

 	  pop     r16
   	ret
