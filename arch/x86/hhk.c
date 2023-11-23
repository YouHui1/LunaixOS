#include <arch/x86/boot/multiboot.h>
#include <arch/x86/idt.h>
#include <lunaix/mm/page.h>
#include <lunaix/constants.h>

#define PT_ADDR(ptd, pt_index)                       ((ptd_t*)ptd + (pt_index + 1) * 1024)
#define SET_PDE(ptd, pde_index, pde)                 *((ptd_t*)ptd + pde_index) = pde
#define SET_PTE(ptd, pt_index, pte_index, pte)       *(PT_ADDR(ptd, pt_index) + pte_index) = pte
#define sym_val(sym)                                 (uintptr_t)(&sym)

#define KERNEL_PAGE_COUNT           ((sym_val(__kernel_end) - sym_val(__kernel_start) + 0x1000 - 1) >> 12)
#define HHK_PAGE_COUNT              ((sym_val(__init_hhk_end) - 0x100000 + 0x1000 - 1) >> 12)

// user table #1
#define PG_TABLE_IDENTITY 0

// user table #2-4
// hence the max size of kernel is 8MiB
#define PG_TABLE_KERNEL 1

// user table #5
#define PG_TABLE_STACK 4

// Provided by linker (see linker.ld)
extern uint8_t __kernel_start;
extern uint8_t __kernel_end;
extern uint8_t __init_hhk_end;
extern uint8_t _k_stack;
