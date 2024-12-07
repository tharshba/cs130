#include <stdint.h>

// Struct for R-type instructions
// You don't really need to worry about how these work
// but if you're curious, this is a single 32 bit unsigned int but
// each of these "variables" use the number of bits specified by
// the number after the colon, and the first "variable" is at the
// least significant bits (bits 0-6). This basically just makes the
// shifting easier.
typedef struct
{
	uint32_t opcode : 7;
	uint32_t rd     : 5;
	uint32_t funct3 : 3;
	uint32_t rs1    : 5;
	uint32_t rs2    : 5;
	uint32_t funct7 : 7;
}
rtype_t;

// Struct for I-type instructions
typedef struct
{
	uint32_t opcode :  7;
	uint32_t rd     :  5;
	uint32_t funct3 :  3;
	uint32_t rs1    :  5;
	uint32_t imm    : 12;
}
itype_t;

// Struct for S-type instructions
typedef struct
{
	uint32_t opcode : 7;
	uint32_t imm1   : 5;
	uint32_t funct3 : 3;
	uint32_t rs1    : 5;
	uint32_t rs2    : 5;
	uint32_t imm2   : 7;
}
stype_t;

// Struct for B-type instructions
typedef struct
{
	uint32_t opcode : 7;
	uint32_t imm3   : 1;
	uint32_t imm1   : 4;
	uint32_t funct3 : 3;
	uint32_t rs1    : 5;
	uint32_t rs2    : 5;
	uint32_t imm2   : 6;
	uint32_t imm4   : 1;
}
btype_t;

// Struct for U-type instructions
typedef struct
{
	uint32_t opcode :  7;
	uint32_t rd     :  5;
	uint32_t imm    : 20;
}
utype_t;

// Struct for J-type instructions
typedef struct
{
	uint32_t opcode :  7;
	uint32_t rd     :  5;
	uint32_t imm3   :  8;
	uint32_t imm2   :  1;
	uint32_t imm1   : 10;
	uint32_t imm4   :  1;
}
jtype_t;

// This contains the data for a single instruction, but you can "cast"
// it as any of these fields. It basically just makes the casting easier.
// If you like, you can think of it as containing all of these structs,
// and they all always have the same value.
typedef union
{
	rtype_t R;
	itype_t I;
	stype_t S;
	btype_t B;
	utype_t U;
	jtype_t J;
}
inst_t;

const char* reg[32] = {
"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11",
"x12", "x13", "x14", "x15", "x16", "x17", "x18", "x19", "x20", "x21", "x22",
"x23", "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"};

const char* abi[32] = {
"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1",
"a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8",
"s9", "s10", "s11", "t3", "t4", "t5", "t6"};
