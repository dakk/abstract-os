SECTIONS
{
	. = 0x100000;

	.text ALIGN(4096) :
	{
		*(.text*)
		*(.gnu.linkonce.t*)
	}

	.rodata ALIGN(4096) :
	{
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}
	
	.data ALIGN(4096) :
	{
		start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;
	
		*(.data*)
		*(.gnu.linkonce.d*)
	}

	.bss ALIGN(4096) :
	{
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
	}
	
	 /DISCARD/ :
	 {
		*(.comment)
		*(.eh_frame) /* You should discard this unless you're implementing runtime support for C++ exceptions. */
	 }
}
/*
ENTRY (loader)

SECTIONS{
    . = 0x00100000;

.setup : {
*(.setup)
}

. += 0xC0000000;

    .text : AT(ADDR(.text) - 0xC0000000) {
        *(.text)
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xC0000000) {
        *(.rodata)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) {
start_ctors = .;
*(.ctor*)
end_ctors = .;
start_dtors = .;
*(.dtor*)
end_dtors = .;
        *(.data)
    }

    .bss : AT(ADDR(.bss) - 0xC0000000) {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }

end = .; _end = .; __end = .;
}

*/

/*
ENTRY(start)
SECTIONS
{

    .text 0x100000 :
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
        start_ctors = .;
        *(.ctors)
        end_ctors = .;
        

        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
        . = ALIGN(4096);
    }

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }

    end = .; _end = .; __end = .;
}*/
