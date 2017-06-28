# C-- Compilation to SPIM Code
# File: test.s
			.data
# Data Area Allocation.
.space	4
.space	4
.space	400
output: .asciiz	"Output: "
input: .asciiz	"Input: "
new_line: .asciiz "\n"
		.text
# -> Function Declaration
.globl bubbleSort
bubbleSort:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	-32	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
	   li		$t0,	0	# const: immediate value to tempReg
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   li		$t0,	0	# const: immediate value to tempReg
	   sw		$t0,	-4($gp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   li		$t0,	0	# const: immediate value to tempReg
	   sw		$t0,	-8($gp) 	# store word: r-value to l-value
# <- Assign
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
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$v0,	1	# load print_int call code
	 move		$a0,	$t0	# move integer to be printed into $a0
	syscall			# call OS to perform operation
	   li		$v0,	4	# load print_string call code
	   la		$a0,	new_line	# load address of "\n"
	syscall			# call OS to perform operation
# <- Output
# -> Iteration Statement
_lab_1:
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	48($fp) 	# id: variable value to tempReg
	  slt		$t0,	$t0,	$t1	# slt: set 1 if less than
# <- Op
	 beqz		$t0,	_lab_2	# branch if condition is false
# -> Compound Statement
# -> Iteration Statement
_lab_3:
# -> Op
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
# -> Op
	   lw		$t1,	48($fp) 	# id: variable value to tempReg
	   li		$t2,	1	# const: immediate value to tempReg
	  sub		$t1,	$t1,	$t2	# sub: subtract two operand
# <- Op
	  sle		$t0,	$t0,	$t1	# sle: set 1 if less or equal
# <- Op
	 beqz		$t0,	_lab_4	# branch if condition is false
# -> Compound Statement
# -> Assign
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   sw		$t0,	-12($fp) 	# store word: r-value to l-value
# <- Assign
# -> Selection Statement
# -> Op
# -> Array Accessing
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	44($fp) 	# lw: load array base address
	   li		$t2,	4	# li: load word size
	  mul		$t0,	$t0,	$t2	# mul: value * wordsize
	  add		$t0,	$t0,	$t1	# add: calculate address of element
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
# -> Array Accessing
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	   lw		$t2,	44($fp) 	# lw: load array base address
	   li		$t3,	4	# li: load word size
	  mul		$t1,	$t1,	$t3	# mul: value * wordsize
	  add		$t1,	$t1,	$t2	# add: calculate address of element
	   lw		$t1,	0($t1) 	# array accessing: array element to tempReg
# <- Array Accessing
	  sgt		$t0,	$t0,	$t1	# sgt: set 1 if greater than
# <- Op
	 beqz		$t0,	_lab_5	# branch if condition is false
# -> Compound Statement
# -> Assign
# -> Array Accessing
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	44($fp) 	# lw: load array base address
	   li		$t2,	4	# li: load word size
	  mul		$t0,	$t0,	$t2	# mul: value * wordsize
	  add		$t0,	$t0,	$t1	# add: calculate address of element
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
	   sw		$t0,	-24($fp) 	# store word: r-value to l-value
# <- Assign
# -> Assign
# -> Array Accessing
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
	   lw		$t1,	44($fp) 	# lw: load array base address
	   li		$t2,	4	# li: load word size
	  mul		$t0,	$t0,	$t2	# mul: value * wordsize
	  add		$t0,	$t0,	$t1	# add: calculate address of element
	   lw		$t0,	0($t0) 	# array accessing: array element to tempReg
# <- Array Accessing
	   lw		$t1,	-8($fp) 	# id: variable value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$fp	# add: calculate address of l-value
	   sw		$t0,	0($t1) 	# store word: r-value to l-value
# <- Assign
# -> Assign
	   lw		$t0,	-24($fp) 	# id: variable value to tempReg
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	   li		$t2,	4	# li: load word size
	  mul		$t1,	$t1,	$t2	# mul: value * wordsize
	  add		$t1,	$t1,	$fp	# add: calculate address of l-value
	   sw		$t0,	0($t1) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
_lab_5:
# <- Selection Statement
# -> Assign
# -> Op
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
	   li		$t1,	1	# const: immediate value to tempReg
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
	   sw		$t0,	-12($fp) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
	    b		_lab_3	# branch to end of iteration statement
_lab_4:
# <- Iteration Statement
# -> Assign
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$t1,	1	# const: immediate value to tempReg
	  add		$t0,	$t0,	$t1	# add: add two operand
# <- Op
	   sw		$t0,	-8($fp) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
	    b		_lab_1	# branch to end of iteration statement
_lab_2:
# <- Iteration Statement
# -> Selection Statement
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$t1,	0	# const: immediate value to tempReg
	  seq		$t0,	$t0,	$t1	# seq: set 1 if equal
# <- Op
	 beqz		$t0,	_lab_6	# branch if condition is false
# -> Compound Statement
# -> Assign
# -> Op
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
	   li		$t1,	100	# const: immediate value to tempReg
	  mul		$t0,	$t0,	$t1	# mul: multiply two operand
# <- Op
	   sw		$t0,	-28($fp) 	# store word: r-value to l-value
# <- Assign
# -> Return Statement
	   lw		$t0,	-28($fp) 	# id: variable value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
# <- Compound Statement
	    b		_lab_7	# branch to end of selection statement
_lab_6:
# -> Selection Statement
# -> Op
	   lw		$t0,	-12($fp) 	# id: variable value to tempReg
	   li		$t1,	0	# const: immediate value to tempReg
	  sne		$t0,	$t0,	$t1	# sne: set 1 if not equal
# <- Op
	 beqz		$t0,	_lab_8	# branch if condition is false
# -> Compound Statement
# -> Assign
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   li		$t1,	500	# const: immediate value to tempReg
	  div		$t0,	$t0,	$t1	# div: divide two operand
# <- Op
	   sw		$t0,	-32($fp) 	# store word: r-value to l-value
# <- Assign
# -> Return Statement
	   lw		$t0,	-32($fp) 	# id: variable value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
# <- Compound Statement
	    b		_lab_9	# branch to end of selection statement
_lab_8:
# -> Selection Statement
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	  sge		$t0,	$t0,	$t1	# sge: set 1 if grater or equal
# <- Op
	 beqz		$t0,	_lab_10	# branch if condition is false
# -> Compound Statement
# -> Assign
# -> Op
	   lw		$t0,	-8($fp) 	# id: variable value to tempReg
	   lw		$t1,	-12($fp) 	# id: variable value to tempReg
	  sub		$t0,	$t0,	$t1	# sub: subtract two operand
# <- Op
	   sw		$t0,	-36($fp) 	# store word: r-value to l-value
# <- Assign
# -> Return Statement
	   lw		$t0,	-36($fp) 	# id: variable value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
# <- Compound Statement
	    b		_lab_11	# branch to end of selection statement
_lab_10:
# -> Return Statement
	   li		$t0,	0	# const: immediate value to tempReg
	 move		$v0,	$t0	# save function return value in v0
	    j		_lab_0	# jump to function end process
# <- Return Statement
_lab_11:
# <- Selection Statement
_lab_9:
# <- Selection Statement
_lab_7:
# <- Selection Statement
# <- Compound Statement
_lab_0:
	 addi		$sp,	$sp,	32	# addi: remove space for local variable
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
	 addi		$sp,	$sp,	-404	# addi: reserve space for local variable
# -> Compound Statement
# -> Assign
# -> Call Function
	 addi		$t1,	$fp,	-404	# id: variable value to tempReg
	   li		$t2,	100	# const: immediate value to tempReg
	 addi		$sp,	$sp,	-8	# add: reserve space for pushing argument
	   sw		$t1,	0($sp) 	# push argument
	   sw		$t2,	4($sp) 	# push argument
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
	  jal		bubbleSort	# jump to function body
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
	 addi		$sp,	$sp,	8	# addi: remove space for argument
	 move		$t0,	$v0	# move: v0 to tempReg(function result save)
# <- Call Function
	   sw		$t0,	-408($fp) 	# store word: r-value to l-value
# <- Assign
# <- Compound Statement
_lab_12:
	 addi		$sp,	$sp,	404	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# End of execution.
