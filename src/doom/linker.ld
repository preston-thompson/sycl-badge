ENTRY(_start)

MEMORY
{
  flash(rx!w)       : ORIGIN = 0x10000000, LENGTH = 2048K
  romfs(rx!w)       : ORIGIN = 0x10080000, LENGTH = 1280K
  cart_xip(rx!w)    : ORIGIN = 0x101C0000, LENGTH = 256K
  ram(rxw)          : ORIGIN = 0x20000000, LENGTH = 512K
  scratch_x(rxw)    : ORIGIN = 0x20080000, LENGTH = 4K
  scratch_y(rxw)    : ORIGIN = 0x20081000, LENGTH = 4K
}

__romfs_region_start__ = ORIGIN(romfs);
__romfs_region_end__ = ORIGIN(romfs) + LENGTH(romfs);
__cart_xip_start__ = ORIGIN(cart_xip);
__cart_xip_end__ = ORIGIN(cart_xip) + LENGTH(cart_xip);
__cart_xip_size__ = LENGTH(cart_xip);

SECTIONS
{
  .flash_start :
  {
    . = ALIGN(4);
    KEEP(*(microzig_flash_start))
    KEEP(*(.vectors .vectors.*))
    . = ALIGN(4);
    __bootmeta_start__ = .;
    KEEP(*(.bootmeta))
    __bootmeta_end__ = .;
  } > flash

  .text :
  {
    . = ALIGN(4);
    *(.text*)
    *(.rodata*)
  } > flash

  __ram_text_load__ = LOADADDR(.ram_text);
  .ram_text :
  {
    . = ALIGN(4);
    __ram_text_start__ = .;
    *(.ram_text*)
    . = ALIGN(4);
    __ram_text_end__ = .;
  } > ram AT> flash

  __data_start_flash__ = LOADADDR(.data);
  microzig_data_load_start = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    __data_start__ = .;
    microzig_data_start = .;
    *(.time_critical*)
    *(.data)
    *(.data*)
    __data_end__ = .;
    microzig_data_end = .;
  } > ram AT> flash

  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    microzig_bss_start = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    microzig_bss_end = .;
  } > ram

  .heap (NOLOAD):
  {
    __end__ = .;
    end = __end__;
    KEEP(*(.heap*))
  } > ram

  .process_ram (NOLOAD) :
  {
    . = ALIGN(8);
    __process_ram_start__ = .;
    *(.process_ram*)
    . = ALIGN(8);
    __process_ram_end__ = .;
  } > ram

  .scratch_x (NOLOAD):
  {
    . = ALIGN(8);
    __scratch_x_start__ = .;
    *(.scratch_x*)
    . = ALIGN(8);
    . = . + 2K;
    __irq_stack_top__ = .;
    . = ORIGIN(scratch_x) + LENGTH(scratch_x);
    __scratch_x_end__ = .;
  } > scratch_x

  .scratch_y (NOLOAD):
  {
    . = ALIGN(8);
    __scratch_y_start__ = .;
    *(.scratch_y*)
    . = ALIGN(8);
    . = ORIGIN(scratch_y) + LENGTH(scratch_y);
    __scratch_y_end__ = .;
  } > scratch_y

  __kernel_ram_start__ = ORIGIN(ram);
  __kernel_ram_end__ = ORIGIN(ram) + LENGTH(ram);
  __process_ram_start__ = ORIGIN(ram);
  __process_ram_end__ = ORIGIN(ram) + LENGTH(ram);
  __scratch_x_region_start__ = ORIGIN(scratch_x);
  __scratch_x_region_end__ = ORIGIN(scratch_x) + LENGTH(scratch_x);
  __scratch_y_region_start__ = ORIGIN(scratch_y);
  __scratch_y_region_end__ = ORIGIN(scratch_y) + LENGTH(scratch_y);

  __stack_top__ = ORIGIN(scratch_y) + LENGTH(scratch_y);
  __stack_limit__ = ORIGIN(scratch_y);
  __irq_stack_limit__ = ORIGIN(scratch_x) + 2K;
  __heap_limit__ = __stack_limit__;

  PROVIDE(__stack = __stack_top__);

  ASSERT(__data_start_flash__ <= ORIGIN(flash) + LENGTH(flash), "ERROR: Doom firmware exceeds flash")
  ASSERT(__bss_end__ <= ORIGIN(ram) + LENGTH(ram), "ERROR: Doom firmware RAM overflow")
  ASSERT((__stack_top__ & 0x7) == 0, "ERROR: Stack pointer not 8-byte aligned")
  ASSERT((__irq_stack_top__ & 0x7) == 0, "ERROR: IRQ stack pointer not 8-byte aligned")
}
