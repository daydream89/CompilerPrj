# C-- Compilation to SPIM Code
# File: ex1.s
			.data
# Data Area Allocation.
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
# -> Function Declaration
.globl main
main:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	20	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
	   li		$t0,	1	# const: immediate value to tempReg
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   li		$t0,	2	# const: immediate value to tempReg
	   sw		$t0,	-12($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   li		$t0,	3	# const: immediate value to tempReg
	   sw		$t0,	-16($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   li		$t0,	4	# const: immediate value to tempReg
	   sw		$t0,	-20($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
# -> Op
# -> Op
# -> Op
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
# -> Op
# -> Op
# -> Op
	   lw		$t1,	-16($fp) 	# id: variable value to tempReg
	   lw		$t2,	-20($fp) 	# id: variable value to tempReg
	  add		$t1,	$t1,	$t2	# add: add two operand
# <- Op
	   li		$t2,	5	# const: immediate value to tempReg
	  add		$t1,	$t1,	$t2	# add: add two operand
# <- Op
	   li		$t2,	6	# const: immediate value to tempReg
	  add		$t1,	$t1,	$t2	# add: add two operand
# <- Op
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
	   li		$t1,	7	# const: immediate value to tempReg
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
# -> Op
	   li		$t1,	8	# const: immediate value to tempReg
	   li		$t2,	9	# const: immediate value to tempReg
	  mul		$t1,	$t1,	$t2	# mul: multiply two operand
# <- Op
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# -> Output
	   li		$v0,	4	# load print_string call code
	   la		$a0,	output	# load address of "Output:"
	syscall			# call OS to perform operation
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
# -> Assign
# -> Op
# -> Op
	   lw		$t0,	-16($fp) 	# id: variable value to tempReg
	   lw		$t1,	-20($fp) 	# id: variable value to tempReg
	  mul		$t0,	$t0,	$t1	# mul: multiply two operand
# <- Op
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	  sub		$t0,	$t0,	$t1	# sub: subtract two operand
# <- Op
	   sw		$t0,	-12($fp) 	# store word: r-value to l-value
# <- Assign
# -> Output
	   li		$v0,	4	# load print_string call code
	   la		$a0,	output	# load address of "Output:"
	syscall			# call OS to perform operation
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
# -> Assign
# -> Op
	   lw		$t0,	-20($fp) 	# id: variable value to tempReg
# -> Op
	   lw		$t1,	-16($fp) 	# id: variable value to tempReg
	   li		$t2,	1	# const: immediate value to tempReg
	  sub		$t1,	$t1,	$t2	# sub: subtract two operand
# <- Op
	  div		$t0,	$t0,	$t1	# div: divide two operand
# <- Op
	   sw		$t0,	-16($fp) 	# store word: r-value to l-value
# <- Assign
# -> Output
	   li		$v0,	4	# load print_string call code
	   la		$a0,	output	# load address of "Output:"
	syscall			# call OS to perform operation
	   lw		$t0,	-16($fp) 	# id: variable value to tempReg
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
# -> Assign
# -> Op
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	  div		$t0,	$t0,	$t1	# div: divide two operand
# <- Op
# -> Op
	   lw		$t1,	-16($fp) 	# id: variable value to tempReg
	   lw		$t2,	-16($fp) 	# id: variable value to tempReg
	  mul		$t1,	$t1,	$t2	# mul: multiply two operand
# <- Op
	  sub		$t0,	$t0,	$t1	# sub: subtract two operand
# <- Op
	   sw		$t0,	-20($fp) 	# store word: r-value to l-value
# <- Assign
# -> Output
	   li		$v0,	4	# load print_string call code
	   la		$a0,	output	# load address of "Output:"
	syscall			# call OS to perform operation
	   lw		$t0,	-20($fp) 	# id: variable value to tempReg
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
# <- Compound Statement
_lab_0:
	 addi		$sp,	$sp,	-20	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# End of execution.
