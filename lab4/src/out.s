.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

read:
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
sw $fp, 0($sp)
addi $fp, $sp, 8
li $v0, 4
la $a0, _prompt
syscall
li $v0, 5
syscall
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
jr $ra

write:
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
sw $fp, 0($sp)
addi $fp, $sp, 8
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
move $v0, $0
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
jr $ra

fib	:
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
sw $fp, 0($sp)
addi $fp, $sp, 8
subu $sp,$sp,228

move $t0, $a0


li $t1 0
subu  $v1 ,$fp , 12
sw $t0, 0($v1)
subu  $v1 ,$fp , 16
sw $t1, 0($v1)
bne $t0, $t1, label2	
li $t2 1
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
move $v0,$t2
jr $ra
subu  $v1 ,$fp , 12
sw $t0, 0($v1)
subu  $v1 ,$fp , 16
sw $t1, 0($v1)
subu  $v1 ,$fp , 20
sw $t2, 0($v1)
j label3	
label2	:

li $t0 1
subu $v1 ,$fp , 12
lw $t1, 0($v1)
subu  $v1 ,$fp , 12
sw $t1, 0($v1)
subu  $v1 ,$fp , 24
sw $t0, 0($v1)
bne $t1, $t0, label5	
li $t2 1
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
move $v0,$t2
jr $ra
subu  $v1 ,$fp , 12
sw $t1, 0($v1)
subu  $v1 ,$fp , 24
sw $t0, 0($v1)
subu  $v1 ,$fp , 28
sw $t2, 0($v1)
j label6	
label5	:

subu $v1 ,$fp , 12
lw $t1, 0($v1)
addi $t0, $t1, -1

subu $v1 ,$fp , 12
sw $t1, 0($v1)
subu $v1 ,$fp , 32
sw $t0, 0($v1)
move $a0, $t0
jal fib	
addi $sp, $sp, 0
move $t0, $v0
subu $v1 ,$fp , 12
lw $t2, 0($v1)
addi $t1, $t2, -2

subu $v1 ,$fp , 12
sw $t2, 0($v1)
subu $v1 ,$fp , 36
sw $t0, 0($v1)
subu $v1 ,$fp , 40
sw $t1, 0($v1)
move $a0, $t1
jal fib	
addi $sp, $sp, 0
move $t0, $v0
subu $v1 ,$fp , 36
lw $t2, 0($v1)
add $t1, $t2, $t0
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
move $v0,$t1
jr $ra
subu  $v1 ,$fp , 36
sw $t2, 0($v1)
subu  $v1 ,$fp , 44
sw $t0, 0($v1)
subu  $v1 ,$fp , 48
sw $t1, 0($v1)
label6	:

label3	:


main	:
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
sw $fp, 0($sp)
addi $fp, $sp, 8
subu $sp,$sp,192

li $t0 5

subu $v1 ,$fp , 12
sw $t0, 0($v1)
move $a0, $t0
jal fib	
addi $sp, $sp, 0
move $t0, $v0
move $a0, $t0
jal write
li $t1 4

subu $v1 ,$fp , 16
sw $t0, 0($v1)
subu $v1 ,$fp , 20
sw $t1, 0($v1)
move $a0, $t1
jal fib	
addi $sp, $sp, 0
move $t0, $v0
move $a0, $t0
jal write
li $t1 3

subu $v1 ,$fp , 24
sw $t0, 0($v1)
subu $v1 ,$fp , 28
sw $t1, 0($v1)
move $a0, $t1
jal fib	
addi $sp, $sp, 0
move $t0, $v0
move $a0, $t0
jal write
li $t1 2

subu $v1 ,$fp , 32
sw $t0, 0($v1)
subu $v1 ,$fp , 36
sw $t1, 0($v1)
move $a0, $t1
jal fib	
addi $sp, $sp, 0
move $t0, $v0
move $a0, $t0
jal write
li $t1 1

subu $v1 ,$fp , 40
sw $t0, 0($v1)
subu $v1 ,$fp , 44
sw $t1, 0($v1)
move $a0, $t1
jal fib	
addi $sp, $sp, 0
move $t0, $v0
move $a0, $t0
jal write
li $t1 0
subu $sp, $fp, 8
lw $fp, 0($sp)
addi $sp, $sp, 4
lw $ra, 0($sp)
addi $sp, $sp, 4
move $v0,$t1
jr $ra
