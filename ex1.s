			.data
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
.globl main
main:
	 addi		$sp,	$sp,	-8
	   sw		$fp,	4($sp) 
	   sw		$ra,	0($sp) 
	 addi		$fp,	$sp,	4
	 addi		$sp,	$sp,	-16
	   li		$t0,	1
	   sw		$t0,	-8($fp) 
	   li		$t0,	2
	   sw		$t0,	-12($fp) 
	   li		$t0,	3
	   sw		$t0,	-16($fp) 
	   li		$t0,	4
	   sw		$t0,	-20($fp) 
	   lw		$t0,	-8($fp) 
	   lw		$t1,	-12($fp) 
	  add		$t0,	$t0,	$t1
	   lw		$t1,	-16($fp) 
	   lw		$t2,	-20($fp) 
	  add		$t1,	$t1,	$t2
	   li		$t2,	5
	  add		$t1,	$t1,	$t2
	   li		$t2,	6
	  add		$t1,	$t1,	$t2
	  add		$t0,	$t0,	$t1
	   li		$t1,	7
	  add		$t0,	$t0,	$t1
	   li		$t1,	8
	   li		$t2,	9
	  mul		$t1,	$t1,	$t2
	  add		$t0,	$t0,	$t1
	   sw		$t0,	-8($fp) 
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
	   lw		$t0,	-16($fp) 
	   lw		$t1,	-20($fp) 
	  mul		$t0,	$t0,	$t1
	   lw		$t1,	-12($fp) 
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-12($fp) 
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t0,	-12($fp) 
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
	   lw		$t0,	-20($fp) 
	   lw		$t1,	-16($fp) 
	   li		$t2,	1
	  sub		$t1,	$t1,	$t2
	  div		$t0,	$t0,	$t1
	   sw		$t0,	-16($fp) 
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t0,	-16($fp) 
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
	   lw		$t0,	-8($fp) 
	   lw		$t1,	-12($fp) 
	  div		$t0,	$t0,	$t1
	   lw		$t1,	-16($fp) 
	   lw		$t2,	-16($fp) 
	  mul		$t1,	$t1,	$t2
	  sub		$t0,	$t0,	$t1
	   sw		$t0,	-20($fp) 
	   li		$v0,	4
	   la		$a0,	output
	syscall		
	   lw		$t0,	-20($fp) 
	   li		$v0,	1
	 move		$a0,	$t0
	syscall		
	   li		$v0,	4
	   la		$a0,	new_line
	syscall		
_lab_0:
	 addi		$sp,	$sp,	16
	   lw		$ra,	0($sp) 
	   lw		$fp,	4($sp) 
	 addi		$sp,	$sp,	8
	   jr		$ra
