.macro isr_template vector, no_error_code=1
    /* 引用vector参数，到时候值替换到vector(?)这里 */
    .globl _asm_isr\vector
    .type _asm_isr\vector, @function
    _asm_isr\vector:
        /* 检测是否有error code，保证栈的一致性 */
        .if \no_error_code
            pushl $0x0
        .endif
        /* 需要知道是哪个中断 */
        pushl $\vector
        jmp interrupt_wrapper
.endm

.section .text
    isr_template 0

    interrupt_wrapper:

        /* 保存旧的esp值 */
        mov %esp, %eax
        /* 保证16位对齐，将末四位清零 */
        andl $0xfffffff0, %esp
        subl $16, %esp
        /* 把旧的esp值推到新的栈顶 */
        movl %eax, (%esp)
        call interrupt_handler
        /* 执行完毕后栈顶没有变化，pop eax会恢复到那个旧的esp值 */
        pop %eax
        /* 重置esp值，指向旧栈顶 */
        movl %eax, %esp
        /* 手动弹出error code(32 Bits) + vector number(32 Bits) */
        addl $8, %esp

        iret
