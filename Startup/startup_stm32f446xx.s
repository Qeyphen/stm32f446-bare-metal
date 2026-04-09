.syntax unified
    .cpu cortex-m4
    .fpu softvfp
    .thumb

    .global g_pfnVectors
    .global Default_Handler

    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object

g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   0
    .word   0
    .word   0
    .word   0
    .word   Default_Handler
    .word   Default_Handler
    .word   0
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   TIM2_IRQHandler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler
    .word   Default_Handler

    .section .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function

Reset_Handler:
    ldr     r0, =_sbss
    ldr     r1, =_ebss
    movs    r2, #0
bss_loop:
    cmp     r0, r1
    bge     bss_done
    str     r2, [r0], #4
    b       bss_loop
bss_done:
    ldr     r0, =_sdata
    ldr     r1, =_edata
    ldr     r2, =_sidata
data_loop:
    cmp     r0, r1
    bge     main_call
    ldr     r3, [r2], #4
    str     r3, [r0], #4
    b       data_loop
main_call:
    bl      main
    bx      lr

    .section .text.Default_Handler
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    b       Default_Handler

    .weak   TIM2_IRQHandler
    .thumb_set TIM2_IRQHandler, Default_Handler