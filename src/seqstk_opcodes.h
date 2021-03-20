#ifndef _SEQSTK_OPCODES_H_
#define _SEQSTK_OPCODES_H_

extern const uint8_t OP_GROUP_MASK;
extern const uint8_t OP_MASK;
extern const uint8_t ADDR_MASK;

typedef enum SeqStkOp
{
   PUSH_IMM = 0b11111111 
} SeqStkOp;

typedef enum SeqStkOpGroup
{
   OP_GROUP_STACK = 0b11100000 
} SeqStkOpGroup;

typedef enum SeqStkAddrMode
{
   ADDR_IMM = 0b00000011 
} SeqStkAddrMode;

#endif