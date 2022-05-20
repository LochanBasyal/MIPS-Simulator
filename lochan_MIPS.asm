.data

.text

addi $t1 , $zero,10   # $t1 = 0 +10 = 10
addiu $t2, $zero, 10  #10
addu $t0, $t1, $t2  #20
add $t3,$t0, $t1  #20+10=30 #add $4, $9, $0
sub $t4,$t3,$t2 #30-10 = 20
j result
and $a0, $t4, $t0 # 20&20 =20
and $a0, $t4, $t0 # 20&20 =20
result:
and $a0, $t4, $t0 # 20&20 =20

addi $v0 ,$zero ,1 #tell the computer we are going to print an integer
syscall

addi $v0 ,$zero ,10  #program ends
syscall
