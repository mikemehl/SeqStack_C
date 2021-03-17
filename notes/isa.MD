# SeqStack ISA

All values are 16.16 bit fixed point.

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
* 100 - Port Out
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