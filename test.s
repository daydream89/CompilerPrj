# C-- Compilation to SPIM Code
# File: test.s
# Standard prelude:
	.text
# End of standard prelude.
# -> Function Declaration
.globl bubbleSort
bubbleSort:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	0	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
	   li		$t0,	0	# const: immediate value to tmpReg
	   sw		$t0,	0($fp) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
_lab_0:
	 addi		$sp,	$sp,	0	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# -> Function Declaration
.globl main
main:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	0	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
# -> Call Function
	   lw		$t1,	0($fp) 	# id: variable value to tmpReg
	   li		$t2,	100	# const: immediate value to tmpReg
	 addi		$sp,	$sp,	-8	# add: retrive space for pushing argument
	   sw		$t1,	0($sp) 	# push argument
	   sw		$t2,	4($sp) 	# push argument
	 addi		$sp,	$sp,	40	# add: reserve space for save temp register
	   sw		$t0,	36($sp) 	# save tmp register
	   sw		$t1,	32($sp) 	# save tmp register
	   sw		$t2,	28($sp) 	# save tmp register
	   sw		$t3,	24($sp) 	# save tmp register
	   sw		$t4,	20($sp) 	# save tmp register
	   sw		$t5,	16($sp) 	# save tmp register
	   sw		$t6,	12($sp) 	# save tmp register
	   sw		$t7,	8($sp) 	# save tmp register
	   sw		$t8,	4($sp) 	# save tmp register
	   sw		$t9,	0($sp) 	# save tmp register
	  jal		bubbleSort	# jump to function body
	   lw		$t0,	36($sp) 	# retrive tmp register
	   lw		$t1,	32($sp) 	# retrive tmp register
	   lw		$t2,	28($sp) 	# retrive tmp register
	   lw		$t3,	24($sp) 	# retrive tmp register
	   lw		$t4,	20($sp) 	# retrive tmp register
	   lw		$t5,	16($sp) 	# retrive tmp register
	   lw		$t6,	12($sp) 	# retrive tmp register
	   lw		$t7,	8($sp) 	# retrive tmp register
	   lw		$t8,	4($sp) 	# retrive tmp register
	   lw		$t9,	0($sp) 	# retrive tmp register
	 addi		$sp,	$sp,	40	# add: retrive space for saved temp register
	 addi		$sp,	$sp,	8	# addi: remove space for argument
	 move		$t0,	$v0	# move: v0 to tempReg(function result save)
# <- Call Function
	   sw		$t2,	0($fp) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
_lab_1:
	 addi		$sp,	$sp,	0	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# End of execution.
