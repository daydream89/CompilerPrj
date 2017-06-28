			.data
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
.globl heapify
heapify:
	 addi		$sp,	$sp,	-8
	   sw		$fp,	4($sp) 
	   sw		$ra,	0($sp) 
	 addi		$fp,	$sp,	4
	 addi		$sp,	$sp,	-16
	   lw		$t0,	52($fp) 
	   sw		$t0,	-8($fp) 
	   li		$t0,	2
	   lw		$t1,	52($fp) 
	  mul		$t0,	$t0,	$t1
	   li		$t1,	1
	  add		$t0,	$t0,	$t1
	   sw		$t0,	-12($fp) 
	   li		$t0,	2
	   lw		$t1,	52($fp) 
	  mul		$t0,	$t0,	$t1
	   li		$t1,	2
	  add		$t0,	$t0,	$t1
	   sw		$t0,	-16($fp) 
	   lw		$t0,	-12($fp) 
	   lw		$t1,	48($fp) 
	  slt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_1
	   lw		$t0,	-12($fp) 
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   lw		$t1,	-8($fp) 
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   lw		$t1,	0($t1) 
	  sgt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_2
	   lw		$t0,	-12($fp) 
	   sw		$t0,	-8($fp) 
_lab_2:
_lab_1:
	   lw		$t0,	-16($fp) 
	   lw		$t1,	48($fp) 
	  slt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_3
	   lw		$t0,	-16($fp) 
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   lw		$t1,	-8($fp) 
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   lw		$t1,	0($t1) 
	  sgt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_4
	   lw		$t0,	-16($fp) 
	   sw		$t0,	-8($fp) 
_lab_4:
_lab_3:
	   lw		$t0,	-8($fp) 
	   lw		$t1,	52($fp) 
	  sne		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_5
	   lw		$t0,	52($fp) 
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   sw		$t0,	-20($fp) 
	   lw		$t0,	-8($fp) 
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   lw		$t1,	52($fp) 
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   sw		$t0,	0($t1) 
	   lw		$t0,	-20($fp) 
	   lw		$t1,	-8($fp) 
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   sw		$t0,	0($t1) 
	 addi		$t1,	$fp,	44
	   lw		$t2,	48($fp) 
	   lw		$t3,	-8($fp) 
	 addi		$sp,	$sp,	-12
	   sw		$t1,	0($sp) 
	   sw		$t2,	4($sp) 
	   sw		$t3,	8($sp) 
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
	  jal		heapify
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
	 addi		$sp,	$sp,	12
	 move		$t0,	$v0
_lab_5:
_lab_0:
	 addi		$sp,	$sp,	16
	   lw		$ra,	0($sp) 
	   lw		$fp,	4($sp) 
	 addi		$sp,	$sp,	8
	   jr		$ra
.globl heapSort
heapSort:
	 addi		$sp,	$sp,	-8
	   sw		$fp,	4($sp) 
	   sw		$ra,	0($sp) 
	 addi		$fp,	$sp,	4
	 addi		$sp,	$sp,	-8
	   lw		$t0,	48($fp) 
	   li		$t1,	2
	  div		$t0,	$t0,	$t1
	   li		$t1,	1
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-8($fp) 
_lab_7:
	   lw		$t0,	-8($fp) 
	   li		$t1,	0
	  sge		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_8
	 addi		$t1,	$fp,	44
	   lw		$t2,	48($fp) 
	   lw		$t3,	-8($fp) 
	 addi		$sp,	$sp,	-12
	   sw		$t1,	0($sp) 
	   sw		$t2,	4($sp) 
	   sw		$t3,	8($sp) 
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
	  jal		heapify
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
	 addi		$sp,	$sp,	12
	 move		$t0,	$v0
	   lw		$t0,	-8($fp) 
	   li		$t1,	1
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-8($fp) 
	    b		_lab_7
_lab_8:
	   lw		$t0,	48($fp) 
	   li		$t1,	1
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-8($fp) 
_lab_9:
	   lw		$t0,	-8($fp) 
	   li		$t1,	0
	  sge		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_10
	   li		$t0,	0
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   sw		$t0,	-12($fp) 
	   lw		$t0,	-8($fp) 
	   lw		$t1,	44($fp) 
	   li		$t2,	4
	  mul		$t0,	$t0,	$t2
	  add		$t0,	$t0,	$t1
	   lw		$t0,	0($t0) 
	   li		$t1,	0
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   sw		$t0,	0($t1) 
	   lw		$t0,	-12($fp) 
	   lw		$t1,	-8($fp) 
	   lw		$t2,	44($fp) 
	   li		$t3,	4
	  mul		$t1,	$t1,	$t3
	  add		$t1,	$t1,	$t2
	   sw		$t0,	0($t1) 
	 addi		$t1,	$fp,	44
	   lw		$t2,	-8($fp) 
	   li		$t3,	0
	 addi		$sp,	$sp,	-12
	   sw		$t1,	0($sp) 
	   sw		$t2,	4($sp) 
	   sw		$t3,	8($sp) 
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
	  jal		heapify
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
	 addi		$sp,	$sp,	12
	 move		$t0,	$v0
	   lw		$t0,	-8($fp) 
	   li		$t1,	1
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-8($fp) 
	    b		_lab_9
_lab_10:
_lab_6:
	 addi		$sp,	$sp,	8
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
	 addi		$sp,	$sp,	-44
_lab_12:
	   lw		$t0,	-48($fp) 
	   li		$t1,	10
	  slt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_13
	   li		$v0,	4
	   la		$a0,	input
	syscall		
	   li		$v0,	5
	syscall		
	 move		$t0,	$v0
	   lw		$t1,	-48($fp) 
	   li		$t2,	4
	  mul		$t1,	$t1,	$t2
	 addi		$t1,	$t1,	-44
	  add		$t1,	$t1,	$fp
	   sw		$t0,	0($t1) 
	   lw		$t0,	-48($fp) 
	   li		$t1,	1
	  add		$t0,	$t0,	$t1
	   sw		$t0,	-48($fp) 
	    b		_lab_12
_lab_13:
	 addi		$t1,	$fp,	-44
	   li		$t2,	10
	 addi		$sp,	$sp,	-8
	   sw		$t1,	0($sp) 
	   sw		$t2,	4($sp) 
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
	  jal		heapSort
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
	 addi		$sp,	$sp,	8
	 move		$t0,	$v0
_lab_14:
	   lw		$t0,	-48($fp) 
	   li		$t1,	10
	  slt		$t0,	$t0,	$t1
	 beqz		$t0,	_lab_15
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t0,	-48($fp) 
	   li		$t1,	4
	  mul		$t0,	$t0,	$t1
	 addi		$t0,	$t0,	-44
	  add		$t0,	$t0,	$fp
	   lw		$t0,	0($t0) 
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
	   lw		$t0,	-48($fp) 
	   li		$t1,	1
	  add		$t0,	$t0,	$t1
	   sw		$t0,	-48($fp) 
	    b		_lab_14
_lab_15:
_lab_11:
	 addi		$sp,	$sp,	44
	   lw		$ra,	0($sp) 
	   lw		$fp,	4($sp) 
	 addi		$sp,	$sp,	8
	   jr		$ra
