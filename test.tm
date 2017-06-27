# C-- Compilation to SPIM Code
# File: test.tm
# Standard prelude:
# End of standard prelude.
# -> Function Declaration
bubbleSort:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	0	# addi: reserve space for local variable
# COMPOUND
_lab_0:
	 addi		$sp,	$sp,	0	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# -> Function Declaration
main:
	 addi		$sp,	$sp,	-8	# add: reserve space for fp, ra
	   sw		$fp,	4($sp) 	# save fp
	   sw		$ra,	0($sp) 	# save ra
	 addi		$fp,	$sp,	4	# addi : setting fp
	 addi		$sp,	$sp,	0	# addi: reserve space for local variable
# COMPOUND
_lab_1:
	 addi		$sp,	$sp,	0	# addi: remove space for local variable
	   lw		$ra,	0($sp) 	# retrive ra
	   lw		$fp,	4($sp) 	# retrive fp
	 addi		$sp,	$sp,	8	# add: remove space for fp,ra
	   jr		$ra	# return to caller
# <- Function Declaration
# End of execution.
