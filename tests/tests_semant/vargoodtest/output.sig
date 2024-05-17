|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|VARGOODTEST
|     1|    21|    59|;
|     2|     2|   405|CONST
|     3|     6|   403|BEGIN
|     4|     6|  1002|SOME
|     4|    11|   303|:=
|     4|    14|   501|20
|     4|    17|    43|+
|     4|    19|   502|10
|     4|    22|    45|-
|     4|    24|   503|30
|     4|    26|    59|;
|     5|     6|  1003|SOME2
|     5|    12|   303|:=
|     5|    15|  1002|SOME
|     5|    20|    43|+
|     5|    22|   502|10
|     5|    24|    59|;
|     6|     6|  1004|SOME3
|     6|    12|   303|:=
|     6|    15|  1002|SOME
|     6|    20|    43|+
|     6|    22|  1003|SOME2
|     6|    27|    59|;
|     7|     6|   404|END
|     7|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||VARGOODTEST
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
|||||||SOME
|||||:=
|||||<expression>
||||||<summand>
|||||||<unsigned-integer>
||||||||20
||||||<summands-list>
|||||||<add-instruction>
||||||||+
|||||||<summand>
||||||||<unsigned-integer>
|||||||||10
|||||||<summands-list>
||||||||<add-instruction>
|||||||||-
||||||||<summand>
|||||||||<unsigned-integer>
||||||||||30
||||||||<summands-list>
|||||||||<empty>
||||||||||<empty>
|||||;
||||<statements-list>
|||||<statement>
||||||<variable-identifier>
|||||||<identifier>
||||||||SOME2
||||||:=
||||||<expression>
|||||||<summand>
||||||||<variable-identifier>
|||||||||<identifier>
||||||||||SOME
|||||||<summands-list>
||||||||<add-instruction>
|||||||||+
||||||||<summand>
|||||||||<unsigned-integer>
||||||||||10
||||||||<summands-list>
|||||||||<empty>
||||||||||<empty>
||||||;
|||||<statements-list>
||||||<statement>
|||||||<variable-identifier>
||||||||<identifier>
|||||||||SOME3
|||||||:=
|||||||<expression>
||||||||<summand>
|||||||||<variable-identifier>
||||||||||<identifier>
|||||||||||SOME
||||||||<summands-list>
|||||||||<add-instruction>
||||||||||+
|||||||||<summand>
||||||||||<variable-identifier>
|||||||||||<identifier>
||||||||||||SOME2
|||||||||<summands-list>
||||||||||<empty>
|||||||||||<empty>
|||||||;
||||||<empty>
|||||||<empty>
|||END
||.

CODEGEN:
.section .rodata


.section .bbs
	SOME:	.space 8
	SOME2:	.space 8
	SOME3:	.space 8


.section .text
.globl main
main:
	jmp VARGOODTEST
VARGOODTEST:
	movq	20, %rax
	subq	10, %rax
	subq	30, %rax
	movq	%rax, SOME
	movq	SOME, %rax
	subq	10, %rax
	movq	%rax, SOME2
	movq	SOME, %rax
	subq	SOME2, %rax
	movq	%rax, SOME3
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
