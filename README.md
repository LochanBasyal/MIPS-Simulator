# MIPS-Simulator
The goal of this project is to understand how MIPS datapath is designed and performed. To achieve this, you will write a cycle-accurate instruction-level simulator that supports a subset of the MIPS ISA. This instruction-level simulator will model the behavior of each instruction and will allow the user to run MIPS programs and see their outputs.
/*
LAB Project 
Author: Lochan Basyal 
Cite: Template provided in the Canvas

Brief Explanation of my project, implementation of MIPS instruction
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
executefetch executesystemcall: exit[Lab 2.zip](https://github.com/LochanBasyal/MIPS-Simulator/files/8741079/Lab.2.zip)

Simulator halted

MIPS-SIM> q       
Bye.
lochanbasyal@lbasyal Lab 2 % 
