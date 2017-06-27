# C-- Compilation to SPIM Code
# File: ex2.s
			.data
# Data Area Allocation.
.space	4004
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
# -> Function Declaration
.globl fibonacci
fibonacci:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	-1656	# addi: reserve space for local variable
# -> Compound Statement
# -> Selection Statement
# -> Op
	   lw		$t0,	44($fp) 	# id: variable value to tempReg
	   li		$t1,	0	# const: immediate value to tempReg
	  sle		$t0,	$t0,	$t1	# sle: set 1 if less or equal
# <- Op
	 beqz		$t0,	_lab_1	# branch if condition is false
# -> Return Statement
	   li		$t0,	0	# const: immediate value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
	    b		_lab_2	# branch to end of selection statement
_lab_1:
# -> Selection Statement
# -> Op
	   lw		$t0,	44($fp) 	# id: variable value to tempReg
	   li		$t1,	2	# const: immediate value to tempReg
	  sle		$t0,	$t0,	$t1	# sle: set 1 if less or equal
# <- Op
	 beqz		$t0,	_lab_3	# branch if condition is false
# -> Return Statement
	   li		$t0,	1	# const: immediate value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
_lab_3:
# <- Selection Statement
_lab_2:
# <- Selection Statement
# -> Compound Statement
# -> Assign
	   lw		$t0,	44($fp) 	# id: variable value to tempReg
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# -> Compound Statement
# -> Assign
	   li		$t0,	0	# const: immediate value to tempReg
	   li		$t1,	5	# const: immediate value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$fp	# add: calculate address of l-value
	   sw		$t0,	0($t1) 	# store word: r-value to l-value
# <- Assign
# -> Selection Statement
# -> Op
# -> Array Accessing
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$t1,	4	# li: load word size
	  mul		$t0,	$t0,	$t1	# mul: value * wordsize
	  add		$t0,	$t0,	$gp	# calculate array element address
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
# -> Array Accessing
	   li		$t1,	5	# const: immediate value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$fp	# calculate array element address
	   lw		$t1,	0($t1) 	# array accessing: array element to tempReg
# <- Array Accessing
	  sne		$t0,	$t0,	$t1	# sne: set 1 if not equal
# <- Op
	 beqz		$t0,	_lab_4	# branch if condition is false
# -> Return Statement
# -> Array Accessing
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$t1,	4	# li: load word size
	  mul		$t0,	$t0,	$t1	# mul: value * wordsize
	  add		$t0,	$t0,	$gp	# calculate array element address
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
_lab_4:
# <- Selection Statement
# <- Compound Statement
# -> Compound Statement
# -> Assign
# -> Call Function
# -> Op
	   lw		$t1,	-8($fp) 	# id: variable value to tempReg
	   li		$t2,	1	# const: immediate value to tempReg
	  sub		$t1,	$t1,	$t2	# sub: subtract two operand
# <- Op
	 addi		$sp,	$sp,	-4	# add: reserve space for pushing argument
	   sw		$t1,	0($sp) 	# push argument
	 addi		$sp,	$sp,	-40	# add: reserve space for save temp register
	   sw		$t0,	36($sp) 	# save temp register
	   sw		$t1,	32($sp) 	# save temp register
	   sw		$t2,	28($sp) 	# save temp register
	   sw		$t3,	24($sp) 	# save temp register
	   sw		$t4,	20($sp) 	# save temp register
	   sw		$t5,	16($sp) 	# save temp register
	   sw		$t6,	12($sp) 	# save temp register
	   sw		$t7,	8($sp) 	# save temp register
	   sw		$t8,	4($sp) 	# save temp register
	   sw		$t9,	0($sp) 	# save temp register
	  jal		fibonacci	# jump to function body
	   lw		$t0,	36($sp) 	# retrive temp register
	   lw		$t1,	32($sp) 	# retrive temp register
	   lw		$t2,	28($sp) 	# retrive temp register
	   lw		$t3,	24($sp) 	# retrive temp register
	   lw		$t4,	20($sp) 	# retrive temp register
	   lw		$t5,	16($sp) 	# retrive temp register
	   lw		$t6,	12($sp) 	# retrive temp register
	   lw		$t7,	8($sp) 	# retrive temp register
	   lw		$t8,	4($sp) 	# retrive temp register
	   lw		$t9,	0($sp) 	# retrive temp register
	 addi		$sp,	$sp,	40	# add: remove space for saved temp register
	 addi		$sp,	$sp,	4	# addi: remove space for argument
	 move		$t0,	$v0	# move: v0 to tempReg(function result save)
# <- Call Function
	   sw		$t0,	-52($fp) 	# store word: r-value to l-value
# <- Assign
# -> Compound Statement
# -> Assign
# -> Call Function
# -> Op
	   lw		$t1,	-8($fp) 	# id: variable value to tempReg
	   li		$t2,	2	# const: immediate value to tempReg
	  sub		$t1,	$t1,	$t2	# sub: subtract two operand
# <- Op
	 addi		$sp,	$sp,	-4	# add: reserve space for pushing argument
	   sw		$t1,	0($sp) 	# push argument
	 addi		$sp,	$sp,	-40	# add: reserve space for save temp register
	   sw		$t0,	36($sp) 	# save temp register
	   sw		$t1,	32($sp) 	# save temp register
	   sw		$t2,	28($sp) 	# save temp register
	   sw		$t3,	24($sp) 	# save temp register
	   sw		$t4,	20($sp) 	# save temp register
	   sw		$t5,	16($sp) 	# save temp register
	   sw		$t6,	12($sp) 	# save temp register
	   sw		$t7,	8($sp) 	# save temp register
	   sw		$t8,	4($sp) 	# save temp register
	   sw		$t9,	0($sp) 	# save temp register
	  jal		fibonacci	# jump to function body
	   lw		$t0,	36($sp) 	# retrive temp register
	   lw		$t1,	32($sp) 	# retrive temp register
	   lw		$t2,	28($sp) 	# retrive temp register
	   lw		$t3,	24($sp) 	# retrive temp register
	   lw		$t4,	20($sp) 	# retrive temp register
	   lw		$t5,	16($sp) 	# retrive temp register
	   lw		$t6,	12($sp) 	# retrive temp register
	   lw		$t7,	8($sp) 	# retrive temp register
	   lw		$t8,	4($sp) 	# retrive temp register
	   lw		$t9,	0($sp) 	# retrive temp register
	 addi		$sp,	$sp,	40	# add: remove space for saved temp register
	 addi		$sp,	$sp,	4	# addi: remove space for argument
	 move		$t0,	$v0	# move: v0 to tempReg(function result save)
# <- Call Function
	   sw		$t0,	-56($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
# -> Op
	   lw		$t0,	-52($fp) 	# id: variable value to tempReg
	   lw		$t1,	-56($fp) 	# id: variable value to tempReg
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
	   lw		$t1,	44($fp) 	# id: variable value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$gp	# add: calculate address of l-value
	   sw		$t0,	0($t1) 	# store word: r-value to l-value
# <- Assign
# -> Compound Statement
# -> Assign
# -> Array Accessing
	   lw		$t0,	44($fp) 	# id: variable value to tempReg
	   li		$t1,	4	# li: load word size
	  mul		$t0,	$t0,	$t1	# mul: value * wordsize
	  add		$t0,	$t0,	$gp	# calculate array element address
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
	   li		$t1,	333	# const: immediate value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$fp	# add: calculate address of l-value
	   sw		$t0,	0($t1) 	# store word: r-value to l-value
# <- Assign
# -> Return Statement
# -> Array Accessing
	   li		$t0,	333	# const: immediate value to tempReg
	   li		$t1,	4	# li: load word size
	  mul		$t0,	$t0,	$t1	# mul: value * wordsize
	  add		$t0,	$t0,	$fp	# calculate array element address
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
# <- Compound Statement
# <- Compound Statement
# <- Compound Statement
# <- Compound Statement
# <- Compound Statement
_lab_0:
	 addi		$sp,	$sp,	1656	# addi: remove space for local variable
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
	 addi		$sp,	$sp,	-8	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
# -> Input
	   li		$v0,	4	# load print_string call code
	   la		$a0,	input	# load address of "Input:"
	syscall			# call OS to perform operation
	   li		$v0,	5	# load read_int call code
	syscall			# call OS to perform operation
	 move		$t0,	$v0	# value read from keyboard -> $v0 -> tempReg
# <- Input
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# -> Output
	   li		$v0,	4	# load print_string call code
	   la		$a0,	output	# load address of "Output:"
	syscall			# call OS to perform operation
# -> Call Function
	   lw		$t1,	-8($fp) 	# id: variable value to tempReg
	 addi		$sp,	$sp,	-4	# add: reserve space for pushing argument
	   sw		$t1,	0($sp) 	# push argument
	 addi		$sp,	$sp,	-40	# add: reserve space for save temp register
	   sw		$t0,	36($sp) 	# save temp register
	   sw		$t1,	32($sp) 	# save temp register
	   sw		$t2,	28($sp) 	# save temp register
	   sw		$t3,	24($sp) 	# save temp register
	   sw		$t4,	20($sp) 	# save temp register
	   sw		$t5,	16($sp) 	# save temp register
	   sw		$t6,	12($sp) 	# save temp register
	   sw		$t7,	8($sp) 	# save temp register
	   sw		$t8,	4($sp) 	# save temp register
	   sw		$t9,	0($sp) 	# save temp register
	  jal		fibonacci	# jump to function body
	   lw		$t0,	36($sp) 	# retrive temp register
	   lw		$t1,	32($sp) 	# retrive temp register
	   lw		$t2,	28($sp) 	# retrive temp register
	   lw		$t3,	24($sp) 	# retrive temp register
	   lw		$t4,	20($sp) 	# retrive temp register
	   lw		$t5,	16($sp) 	# retrive temp register
	   lw		$t6,	12($sp) 	# retrive temp register
	   lw		$t7,	8($sp) 	# retrive temp register
	   lw		$t8,	4($sp) 	# retrive temp register
	   lw		$t9,	0($sp) 	# retrive temp register
	 addi		$sp,	$sp,	40	# add: remove space for saved temp register
	 addi		$sp,	$sp,	4	# addi: remove space for argument
	 move		$t0,	$v0	# move: v0 to tempReg(function result save)
# <- Call Function
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
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
# <- Compound Statement
_lab_5:
	 addi		$sp,	$sp,	8	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# End of execution.
