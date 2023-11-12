/* 禁止使用struct alignment，使得结构体内部元素紧密靠在一起 */
#pragma pack(push, 1)
typedef struct {
    unsigned int vector; /* 32b */
    unsigned int err_code; /* 32b */
    unsigned int eip; /* 32b */
    unsigned short cs; /* 16b */
    unsigned int eflags; /* 32b */
} isr_param;
#pragma pack(pop)


void _asm_isr0();
void interrupt_handler(isr_param* param);
