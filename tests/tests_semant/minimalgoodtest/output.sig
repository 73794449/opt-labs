|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|MINIMALGOODTEST
|     1|    25|    59|;
|     2|     2|   405|CONST
|     3|     6|   403|BEGIN
|     4|     6|  1002|ANY
|     4|    10|   303|:=
|     4|    13|   501|0
|     4|    14|    59|;
|     5|     6|   404|END
|     5|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||MINIMALGOODTEST
||;
||<block>
|||<declarations>
||||<constant-declarations>
|||||CONST
|||||<empty>
||||||<empty>
|||BEGIN
|||<statements-list>
||||<statement>
|||||<variable-identifier>
||||||<identifier>
|||||||ANY
|||||:=
|||||<expression>
||||||<summand>
|||||||<unsigned-integer>
||||||||0
||||||<summands-list>
|||||||<empty>
||||||||<empty>
|||||;
||||<empty>
|||||<empty>
|||END
||.

CODEGEN:
.section .rodata


.section .bbs
	ANY:	.space 8


.section .text
.globl main
main:
	jmp MINIMALGOODTEST
MINIMALGOODTEST:
	movq	0, %rax
	movq	%rax, ANY
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
