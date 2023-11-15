#include <libc/string.h>

char* strcpy(char* dst, const char* src) {
    char c;
    unsigned int i = 0;
    while ((c = src[i])) {
        dst[i] = c;
        ++i;
    }
    dst[i] = '\0';
    return dst;
}
