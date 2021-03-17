# SeqStack ISA

Memory is 2^16 - 1 bytes, byte addressable.

All values are two's complement 16.16 bit fixed point.

Instructions are a byte each.

The 3 most significant bits determine the operation type, and how to interpret the rest of the instruction.

Operations:
* 111 - Stack Manipulation
  * Push
  * Pop
  * Drop
  * Dup
  * Rot
  * MovToRts
  * MovFromRts
* 110 - Arithmetic
  * Add
  * Sub
  * Mul
  * Div
* 101 - Bit Manipulation
  * Shl
  * Shr
  * Rol
  * Ror
  * And
  * Or
  * Xor
  * Not
* 100 - Port Ops
  * PortPush
  * PortPop
  * PortClear
* 011 - Control Flow
  * JMP
  * CALL
  * RET
  * BEQ
  * BNEQ
  * BGT
  * BLT
* 010 - Interrupt
  * SETI - set interrupt (one for each port??)
* 001 - Misc.
  * NOP
  * BRK - stop

Adressing Modes:
* 11 - Immediate (Read value from next 2-4 bytes in memory)
* 10 - Index (Read value from next 2 bytes in memory, treat as memory address, use stack top as offset from that address)
* 01 - Stack based (Read value from top of stack)
