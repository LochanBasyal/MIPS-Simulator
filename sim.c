/*
LAB Assignment 
Author: Lochan Basyal 
Cite: Template provided in the Canvas

Brief Explanation of my assignment, implementation of MIPS instruction
Instructions need to be execute:

R-type: add, addu, sub, and
I-type: addi, addiu
J-type: J

In order to implement these instructions, I used the provided template sim.c
In order to generate the Hexadecimal text file, I used MARS simulator software. I wrote the following 
instructions to display the result of 20.

.asm file 
____________________________________________________________________________________________
.data

.text

addi $t1 , $zero,10   # $t1 = 0 +10 = 10
addiu $t2, $zero, 10  #10
addu $t0, $t1, $t2  #20
add $t3,$t0, $t1  #20+10=30 #add $4, $9, $0
sub $t4,$t3,$t2 #30-10 = 20
j result        # Here in this section, I put Jump instruction to implement, this instruction jump towards result: with skipping 2 lines of codes. 
and $a0, $t4, $t0 # 20&20 =20
and $a0, $t4, $t0 # 20&20 =20
result:
and $a0, $t4, $t0 # 20&20 = 20 answer must be 20

addi $v0 ,$zero ,1 #tell the computer we are going to print an integer
syscall

addi $v0 ,$zero ,10  #program ends
syscall
____________________________________________________________________________________________

Then the simulation software will generate following hexadecimal text file:

lb1.txt file
_____________________________________________________________________________________________
2009000a
240a000a
012a4021
01095820
016a6022
08100008
01882024
01882024
01882024
20020001
0000000c
2002000a
0000000c
_______________________________________________________________________________________________
This code will generate an output of 20.
In order to run this code, I used the following commands.

Here, I presented the output of vscode terminal:
________________________________________________________________________________________________
lochanbasyal@lbasyal Lab 2 % make
gcc -g -O2 shell.c sim.c -o sim
lochanbasyal@lbasyal Lab 2 % ./sim lb1.txt
MIP Simulator

Read 13 words from program into memory.
MIPS-SIM> g
Simulating...
fetch addi instruction 
executefetch addi instruction 
executefetch executeaddu instruction 
fetch executeadd instruction 
fetch executesub instruction 
fetch executefetch executeand instruction 
fetch executeand instruction 
fetch executeand instruction 
fetch addi instruction 
executefetch execute
 print the number:   20 
 fetch addi instruction 
executefetch executesystemcall: exit
Simulator halted

MIPS-SIM> q       
Bye.
lochanbasyal@lbasyal Lab 2 % 
_________________________________________________________________________________________________

Below is my actual sim.c code to implement the subset of MIPS instructions:
_________________________________________________________________________________________________
*/

#include <stdio.h>
#include "shell.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>



uint8_t op;
uint32_t instruction;
uint32_t addr_rs, addr_rt, addr_rd, addr_j;
uint32_t rs, rt, rd;      //to save the register value
uint8_t func;
uint16_t itemp;         //for save immidiate number

  //please take a look at https://inst.eecs.berkeley.edu/~cs61c/resources/MIPS_Green_Sheet.pdf
  //				 or
  //  https://web.cse.ohio-state.edu/~crawfis.3/cse675-02/Slides/MIPS%20Instruction%20Set.pdf

void fetch()
{
	printf("fetch ");
	instruction = mem_read_32(CURRENT_STATE.PC); //the instruction 
	NEXT_STATE.PC = CURRENT_STATE.PC + 4;
	//for add instruction
	/*
	Instruction = 0x 01202020 // add $4, $9, $0
	0000 0001 0010 0000 0010 0000 0010 0000
	000000   01001   00000    00100    00000    100000
	0 			9      0        4        0        32 (these value are in decimal)
												0x 20 (hex equivelent)
												So, If the function of instruction is 20 Hex then this instruction is add (R-type)

	opcode    rs       rt       rd     shamt    funct
	31-26     25-21   20-16    15-11    10=06    5-0
	R(d) = R(s) + R(rt)
	R(4) = R(9) + R(0)
	add $a0 ,$t1, $zero
	*/

}

void decode()
{
	//printf("decode ");
	op = instruction >> 26; //find the 31-26 bit
  /*
  Suppose the instruction code is 0x 01202020
  000000   01001   00000    00100    00000    100000 (Binary Equivalent)
  shifting right				        	000000

  */

  //  printf("the op: %x ",op);
	// if op==0, it is R type
	// this is for test
	if (op == 0) {

		addr_rs = (instruction >> 21) & 0x1f;
		addr_rt = (instruction >> 16) & 0x1f;
		addr_rd = (instruction >> 11) & 0x1f;
		rs = CURRENT_STATE.REGS[addr_rs];   //2^5=32
		rt = CURRENT_STATE.REGS[addr_rt];
		//  rd=CURRENT_STATE.REGS[addr_rd];
		func = instruction & 0x3f;

	}
	if(op == 2)   //J-type , This op code is for Jump Instruction
	{
		addr_j = instruction & 0x3FFFFFF;
		uint32_t old = CURRENT_STATE.PC; // get the old pc
		old = old & 0xF0000000;
		//Now get the address and shift by 2 bits
		uint32_t address1 = (addr_j<<2);
		// adding the both addresses old and address1
		addr_j = old | address1;
	}


// I -type Instruction 
	if (op == 8) {          //addi:001000       
		printf("addi instruction \n");
		addr_rs = (instruction >> 21) & 0x1f;
		addr_rt = (instruction >> 16) & 0x1f;
		rs = CURRENT_STATE.REGS[addr_rs];   //2^5=32
		itemp = instruction & 0x0000ffff;

		if (itemp > 32767) {    //2^15-1=32767 is the largest number
			itemp = ~itemp + 1;
			rt = rs - itemp;
		}
		else {
			rt = rs + itemp;
		}
		NEXT_STATE.REGS[addr_rt] = rt; // It is fine if you just execute here instead of executing in execute() function. 
	}
     // I -type, addiu instruction (decode operation)
		if (op == 9) {              
		printf("addi instruction \n");
		addr_rs = (instruction >> 21) & 0x1f;
		addr_rt = (instruction >> 16) & 0x1f;
		rs = CURRENT_STATE.REGS[addr_rs];   //2^5=32
		itemp = instruction & 0x0000ffff;
		if (itemp > 65535) {  // max value of uint16_t can be calculated ((2^15)*2)-1 =65535)
			itemp = ~itemp + 1;
			rt = rs - itemp;
		}
		else {
			rt = rs + itemp;
		}
		}
		NEXT_STATE.REGS[addr_rt] = rt;
}
void execute()
{
	printf("execute");
	
	if (op == 0) {    // R-type Instruction 
		switch (func) {
		case 32:      //add:100000
			printf("add instruction \n");
			rd = 0;
			//      if(rt>2147483647)
			rd = rt + rs;
			NEXT_STATE.REGS[addr_rd] = rd;
			break;
		case 34:  // R-type sub Instruction
		 	printf("sub instruction \n");
			rd = 0;
			rd = rs - rt;
			NEXT_STATE.REGS[addr_rd] = rd;
			break;
		case 33:  // R-type addu Instruction
		 	printf("addu instruction \n");
			rd = 0;
			rd = rs + rt;
			NEXT_STATE.REGS[addr_rd] = rd;
			break;
		case 36:
			printf("and instruction \n");
			rd = 0;
			rd = rs & rt;
			NEXT_STATE.REGS[addr_rd] = rd;
			break;

		case 12:   //system call:001100
			if (CURRENT_STATE.REGS[2] == 10) {  //v0==10 then exit
				printf("systemcall: exit\n");
				RUN_BIT = FALSE;
			}
			if (CURRENT_STATE.REGS[2] == 1) {   //v0==1: print int
				rt = CURRENT_STATE.REGS[4];   //a0 is 4th register
				printf("\n print the number:   %d \n ", rt);

			}
			break;
		default:
			break;
		}
	// J-type Jump Instruction
		if(op == 2) {
			NEXT_STATE.PC = addr_j;
		}
	}
// Execute function completed
// Here, in the above execution function, I-type instruction, addi and addiu 
// are implemented under decode function as like in the template provided in the
// canvas.


}
void process_instruction()
{
	/* execute one instruction here. You should use CURRENT_STATE and modify
	 * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
	 * access memory. */
	fetch();
	decode();
	execute();

}

