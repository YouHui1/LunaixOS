#include <libc/string.h>
#include <lunaix/tty/tty.h>
#include <lunaix/constants.h>
#include <stdint.h>

#define TTY_WIDTH 80
#define TTY_HEIGHT 25

vga_attribute* tty_vga_buffer = (vga_attribute*)VGA_BUFFER_PADDR;

vga_attribute theme_color = VGA_COLOR_BLACK;

uint32_t tty_x = 0;
uint16_t tty_y = 0;

void tty_init(void* vga_buf) {
    tty_vga_buffer = (vga_attribute*)vga_buf;
    tty_clear();
}

void tty_set_buffer(void* vga_buf) {
    tty_vga_buffer = (vga_attribute*)vga_buf;
}

void tty_set_theme(vga_attribute fg, vga_attribute bg) {
    theme_color = (bg << 4 | fg) << 8;
}

void tty_put_char(char chr) {
    switch (chr) {
        case '\t':
            tty_x += 4;
            break;
        case '\n':
            tty_y++;
        case '\r':
            tty_x = 0;
            break;
        default:
            *(tty_vga_buffer + tty_x + tty_y * TTY_WIDTH) = (theme_color | chr);
            tty_x++;
            break;
    }

    if (tty_x >= TTY_WIDTH) {
        tty_x = 0;
        tty_y++;
    }
    if (tty_y >= TTY_HEIGHT) {
        tty_scroll_up();
    }
}

void tty_put_str(char* str) {
    while (*str != '\0') {
        tty_put_char(*str);
        str++;
    }
}

void tty_scroll_up() {
    size_t last_line = TTY_WIDTH * (TTY_HEIGHT - 1);
    memcpy(tty_vga_buffer, tty_vga_buffer + TTY_WIDTH, last_line);
    for (size_t i = 0; i < TTY_WIDTH; i++) {
        *(tty_vga_buffer + i + last_line) = theme_color;
    }

    tty_y = tty_y == 0 ? 0 : tty_y - 1;
}

void tty_clear() {
    for (uint32_t i = 0; i < TTY_WIDTH * TTY_HEIGHT; i++) {
        *(tty_vga_buffer + i) = theme_color;
    }
    tty_x = 0;
    tty_y = 0;
}
