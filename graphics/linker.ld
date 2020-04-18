/* Based on the linker found here: */
/* https://stackoverflow.com/questions/27669275/undefined-reference-to-in-os-kernel-linking */

OUTPUT_FORMAT("elf32-i386");
ENTRY(boot_start);

BOOTLOADER_BASE  = 0x7c00;
BOOTLOADER_RELOC = 0x600;
SECTOR_SIZE      = 512;
KERNEL_BASE      = BOOTLOADER_RELOC + SECTOR_SIZE;


SECTIONS
{
    __boot_reloc_addr = BOOTLOADER_RELOC;
    __boot_base_addr  = BOOTLOADER_BASE;
    __sector_sizew    = SECTOR_SIZE>>1;

    . = BOOTLOADER_RELOC;

    /* Code and data in boot.o placed between 0x7c00 and 0x7e00 */
    .boot : SUBALIGN(0) {
        boot.o(.text*)
        boot.o(.rodata*)
        boot.o(.data)
    }

    . = BOOTLOADER_RELOC + 0x200 - 2;
    /* Boot signature at 510th byte from beginning of bootloader's base */
    .sig : {
        SHORT(0xaa55);
    }

    KERNEL_ADJ = KERNEL_BASE - .;
    . = KERNEL_BASE;

    __disk_load_start = .;
    __disk_load_seg   = (__disk_load_start) >> 4;

    /* Kernel code and data */
    .kernel : AT(ADDR(.kernel) - KERNEL_ADJ) SUBALIGN(4) {
        *(.text*)
        *(.rodata*)
        *(.data)
    }
    __disk_load_end = .;
    __disk_load_num_sectors = (__disk_load_end - __disk_load_start + (SECTOR_SIZE - 1)) / SECTOR_SIZE;

    .kernel.bss : SUBALIGN(4) {
        __bss_start = .;
        *(COMMON);
        *(.bss)
        . = ALIGN(4);
        __bss_end = .;
    }
    __bss_sizew = SIZEOF(.kernel.bss)>>1;

    /* Remove unnecessary sections */
    /DISCARD/ : {
        *(.eh_frame);
        *(.comment);
    }
}