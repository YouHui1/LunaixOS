ENTRY(start_)

/*
    FUTURE: Use dynamic linker to separate kernel and boot code
    A bit of messy here.
    We will pull our higher half kernel out of this shit
      and load it separately once we have our dynamic linker ready.
*/

SECTIONS {
    . = 0x100000;

    .text BLOCK(4K) : {
        * (.multiboot)
        * (.text)
    }

    .bss BLOCK(4K) : {
        * (COMMON)
        * (.bss)
    }

    .data BLOCK(4k) : {
        * (.data)
    }

    .rodata BLOCK(4K) : {
        * (.rodata)
    }
}
