.global delay

.section .text

msg:    .asciz "test test \n"

.global setup
.global loop

setup:
    call    init_serial
    call    init_pwm11

    ldi     zh, hi8(msg)
    ldi     zl, lo8(msg)

.output:
    lpm     r24, z+
    cpi     r24, 0x00
    breq    .exit_setup
    call    tx
    rjmp    .output

.exit_setup:
    ret


loop:
    call    rx_check
    cpi     r24, 0x00
    breq    .exit_loop

    call    rx

    subi    r24, 0x30
    cpi     r24, 0x00
    brmi    .exit_loop

    cpi     r24, 0x09
    brsh    .exit_loop

    mul     r24, 25

    mov     r24, r0

    call    set_pwm11
.exit_loop:
    ret