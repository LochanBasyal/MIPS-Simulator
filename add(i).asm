.data


.text
addi $t1 , $zero ,10   # $t1 = 0 +10 = 10
add $a0 ,$t1, $zero     #add $4, $9, $0

addi $v0 ,$zero ,1 #tell the computer we are going to print an integer
syscall

addi $v0 ,$zero ,10  #program ends
syscall
