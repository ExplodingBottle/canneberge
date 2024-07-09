MEMORY {
  FLASH (rx) : ORIGIN = 0x90010000, LENGTH = 3936K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 252K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
_stor_end = ORIGIN(FLASH) + LENGTH(FLASH);

SECTIONS {
  .header ORIGIN(FLASH) : {
    KEEP(*(.header))
  } >FLASH

  .isr_vector_table : {
    KEEP(*(.isr_vector_table))
  } >FLASH

  .text : {
    . = ALIGN(4);
    *(.text)
  } >FLASH

  .rodata : {
    . = ALIGN(4);
    *(.rodata)
  } >FLASH

  .data : {
    . = ALIGN(4);
    _datasf = LOADADDR(.data);
    _datas = .;
   *(.data SORT(.data.*))
    _datae = .;
  } >RAM AT> FLASH

  .bss : {
    _bsss = .;
    *(.bss SORT(.bss.*))
    _bsse = .;
  } > RAM

  . = ALIGN(4);
  _end = .;
}
