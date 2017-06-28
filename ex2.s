			.data
.space	4004
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
.globl fibonacci
fibonacci:
	 addi		$sp,	$sp,	-8
	   sw		$fp,	4($sp) 
	   sw		$ra,	0($sp) 
	 addi		$fp,	$sp,	4
	 addi		$sp,	$sp,	-1652
	   lw		$t0,	44($fp) 
	   li		$t1,	0
	  sle		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_1
	   li		$t0,	0
	 move		$v0,	$t0
	    j		_lab_0
	    b		_lab_2
_lab_1:
	   lw		$t0,	44($fp) 
	   li		$t1,	2
	  sle		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_3
	   li		$t0,	1
	 move		$v0,	$t0
	    j		_lab_0
_lab_3:
_lab_2:
	   lw		$t0,	44($fp) 
	   sw		$t0,	-8($fp) 
	   li		$t0,	0
	   li		$t1,	5
	   li		$t2,	4
	  mul		$t1,	$t1,	$t2
	 addi		$t1,	$t1,	-48
	  add		$t1,	$t1,	$fp
	   sw		$t0,	0($t1) 
	   lw		$t0,	-8($fp) 
	   li		$t1,	4
	  mul		$t0,	$t0,	$t1
	 addi		$t0,	$t0,	-4004
	  add		$t0,	$t0,	$gp
	   lw		$t0,	0($t0) 
	   li		$t1,	5
	   li		$t2,	4
	  mul		$t1,	$t1,	$t2
	 addi		$t1,	$t1,	-48
	  add		$t1,	$t1,	$fp
	   lw		$t1,	0($t1) 
	  sne		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_4
	   lw		$t0,	-8($fp) 
	   li		$t1,	4
	  mul		$t0,	$t0,	$t1
	 addi		$t0,	$t0,	-4004
	  add		$t0,	$t0,	$gp
	   lw		$t0,	0($t0) 
	 move		$v0,	$t0
	    j		_lab_0
_lab_4:
	   lw		$t1,	-8($fp) 
	   li		$t2,	1
	  sub		$t1,	$t1,	$t2
	 addi		$sp,	$sp,	-4
	   sw		$t1,	0($sp) 
	 addi		$sp,	$sp,	-40
	   sw		$t0,	36($sp) 
	   sw		$t1,	32($sp) 
	   sw		$t2,	28($sp) 
	   sw		$t3,	24($sp) 
	   sw		$t4,	20($sp) 
	   sw		$t5,	16($sp) 
	   sw		$t6,	12($sp) 
	   sw		$t7,	8($sp) 
	   sw		$t8,	4($sp) 
	   sw		$t9,	0($sp) 
	  jal		fibonacci
	   lw		$t0,	36($sp) 
	   lw		$t1,	32($sp) 
	   lw		$t2,	28($sp) 
	   lw		$t3,	24($sp) 
	   lw		$t4,	20($sp) 
	   lw		$t5,	16($sp) 
	   lw		$t6,	12($sp) 
	   lw		$t7,	8($sp) 
	   lw		$t8,	4($sp) 
	   lw		$t9,	0($sp) 
	 addi		$sp,	$sp,	40
	 addi		$sp,	$sp,	4
	 move		$t0,	$v0
	   sw		$t0,	-52($fp) 
	   lw		$t1,	-8($fp) 
	   li		$t2,	2
	  sub		$t1,	$t1,	$t2
	 addi		$sp,	$sp,	-4
	   sw		$t1,	0($sp) 
	 addi		$sp,	$sp,	-40
	   sw		$t0,	36($sp) 
	   sw		$t1,	32($sp) 
	   sw		$t2,	28($sp) 
	   sw		$t3,	24($sp) 
	   sw		$t4,	20($sp) 
	   sw		$t5,	16($sp) 
	   sw		$t6,	12($sp) 
	   sw		$t7,	8($sp) 
	   sw		$t8,	4($sp) 
	   sw		$t9,	0($sp) 
	  jal		fibonacci
	   lw		$t0,	36($sp) 
	   lw		$t1,	32($sp) 
	   lw		$t2,	28($sp) 
	   lw		$t3,	24($sp) 
	   lw		$t4,	20($sp) 
	   lw		$t5,	16($sp) 
	   lw		$t6,	12($sp) 
	   lw		$t7,	8($sp) 
	   lw		$t8,	4($sp) 
	   lw		$t9,	0($sp) 
	 addi		$sp,	$sp,	40
	 addi		$sp,	$sp,	4
	 move		$t0,	$v0
	   sw		$t0,	-56($fp) 
	   lw		$t0,	-52($fp) 
	   lw		$t1,	-56($fp) 
	  add		$t0,	$t0,	$t1
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t1,	$t1,	$t2
	 addi		$t1,	$t1,	-4004
	  add		$t1,	$t1,	$gp
	   sw		$t0,	0($t1) 
	   lw		$t0,	44($fp) 
	   li		$t1,	4
	  mul		$t0,	$t0,	$t1
	 addi		$t0,	$t0,	-4004
	  add		$t0,	$t0,	$gp
	   lw		$t0,	0($t0) 
	   li		$t1,	333
	   li		$t2,	4
	  mul		$t1,	$t1,	$t2
	 addi		$t1,	$t1,	-1656
	  add		$t1,	$t1,	$fp
	   sw		$t0,	0($t1) 
	   li		$t0,	333
	   li		$t1,	4
	  mul		$t0,	$t0,	$t1
	 addi		$t0,	$t0,	-1656
	  add		$t0,	$t0,	$fp
	   lw		$t0,	0($t0) 
	 move		$v0,	$t0
	    j		_lab_0
_lab_0:
	 addi		$sp,	$sp,	1652
	   lw		$ra,	0($sp) 
	   lw		$fp,	4($sp) 
	 addi		$sp,	$sp,	8
	   jr		$ra
.globl main
main:
	 addi		$sp,	$sp,	-8
	   sw		$fp,	4($sp) 
	   sw		$ra,	0($sp) 
	 addi		$fp,	$sp,	4
	 addi		$sp,	$sp,	-4
	   li		$v0,	4
	   la		$a0,	input
	syscall		
	   li		$v0,	5
	syscall		
	 move		$t0,	$v0
	   sw		$t0,	-8($fp) 
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t1,	-8($fp) 
	 addi		$sp,	$sp,	-4
	   sw		$t1,	0($sp) 
	 addi		$sp,	$sp,	-40
	   sw		$t0,	36($sp) 
	   sw		$t1,	32($sp) 
	   sw		$t2,	28($sp) 
	   sw		$t3,	24($sp) 
	   sw		$t4,	20($sp) 
	   sw		$t5,	16($sp) 
	   sw		$t6,	12($sp) 
	   sw		$t7,	8($sp) 
	   sw		$t8,	4($sp) 
	   sw		$t9,	0($sp) 
	  jal		fibonacci
	   lw		$t0,	36($sp) 
	   lw		$t1,	32($sp) 
	   lw		$t2,	28($sp) 
	   lw		$t3,	24($sp) 
	   lw		$t4,	20($sp) 
	   lw		$t5,	16($sp) 
	   lw		$t6,	12($sp) 
	   lw		$t7,	8($sp) 
	   lw		$t8,	4($sp) 
	   lw		$t9,	0($sp) 
	 addi		$sp,	$sp,	40
	 addi		$sp,	$sp,	4
	 move		$t0,	$v0
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t0,	-8($fp) 
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
_lab_5:
	 addi		$sp,	$sp,	4
	   lw		$ra,	0($sp) 
	   lw		$fp,	4($sp) 
	 addi		$sp,	$sp,	8
	   jr		$ra
