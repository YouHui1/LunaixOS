#include "multiboot.h"

.section .multiboot
    .long MB_MAGIC
    .long MB_ALIGNED_4K_MEM_MAP
    .long CHECKSUM(MB_ALIGNED_4K_MEM_MAP)

.section .bss
    /* According to System V ABI,
     * the stack must be aligned at 16 bytes boundary
     */
    .align 16
    stack_bottom:
        /* 填入16KB（千字节）（存疑） */
        .skip 16384, 0
    stack_top:

.section .text
    .globl start_
    .type start_, @function  /* Optional, this just give the
                              * linker more knowledge about the label
                              */
    start_:
        movl $stack_top, %esp
        /*
            TODO: kernel init
                1. Load GDT
                2. Load IDT
                3. Enable paging
        */
        call _kernel_init

        subl $0x6, %esp

        movl $_gdt, 2(%esp)
        movw _gdt_limit, %ax /* 不能直接把立即数放入栈中 */
        movw %ax, (%esp)
        lgdt (%esp)

        movl $_idt, 2(%esp)
        movw _idt_limit, %ax /* 不能直接把立即数放入栈中 */
        movw %ax, (%esp)
        lidt (%esp)

        addl $0x6, %esp

        /* index 3-15位，处于第4位，因此为0x10 */
        movw $0x10, %cx
        movw %cx, %es
        movw %cx, %ds
        movw %cx, %fs
        movw %cx, %gs
        movw %cx, %ss

        /* index 3-15位，处于第3位，因此为0x8 */
        pushw $0x08 /* push new CS value */
        pushl $_after_gdt /* push label */
        retf

    _after_gdt:
        pushl %ebx
        call _kernel_main

        cli
    j_:
        hlt
        jmp j_
