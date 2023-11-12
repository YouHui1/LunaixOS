#include <lunaix/tty/tty.h>
#include <lunaix/arch/gdt.h>
#include <libc/string.h>
#include <lunaix/arch/idt.h>
// #include <lunaix/interrupts/types.h>
// #include <lunaix/interrupts/interrupts.h>

void _kernel_init()
{
    // TODO
    _init_gdt();
    _init_idt();
}

void _kernel_main(void* info_table)
{
    // remove the warning
    (void)info_table;
    // TODO
    // tty_set_theme(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    // tty_put_str("First Line. Test the line\n");
    // tty_set_theme(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    // tty_put_str("Second Line.\n");
    // char str[100];
    // memset(str, 'k', sizeof(str) - 1);
    // str[99] = '\n';
    // tty_set_theme(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
    // tty_put_str(str);
    tty_set_theme(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_WHITE);
    tty_put_str("clear\n");

    // return 1 / 0;
    __asm__("int $0");
}
