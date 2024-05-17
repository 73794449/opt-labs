|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|CONSTGOODTEST
|     1|    23|    59|;
|     2|     2|   405|CONST
|     3|     6|  1002|SOME
|     3|    11|    61|=
|     3|    13|   501|10
|     3|    15|    59|;
|     4|     6|  1003|SOME2
|     4|    12|    61|=
|     4|    14|   502|20
|     4|    16|    59|;
|     5|     6|   403|BEGIN
|     6|     6|  1004|ANY
|     6|    10|   303|:=
|     6|    13|   503|0
|     6|    14|    59|;
|     7|     6|   404|END
|     7|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||CONSTGOODTEST
||;
||<block>
|||<declarations>
||||<constant-declarations>
|||||CONST
|||||<constant-declarations-list>
||||||<constant-declaration>
|||||||<constant-identifier>
||||||||<identifier>
|||||||||SOME
|||||||=
|||||||<constant>
||||||||<unsigned-integer>
|||||||||10
|||||||;
||||||<constant-declarations-list>
|||||||<constant-declaration>
||||||||<constant-identifier>
|||||||||<identifier>
||||||||||SOME2
||||||||=
||||||||<constant>
|||||||||<unsigned-integer>
||||||||||20
||||||||;
|||||||<empty>
||||||||<empty>
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
	SOME:	.quad 10
	SOME2:	.quad 20


.section .bbs
	ANY:	.space 8


.section .text
.globl main
main:
	jmp CONSTGOODTEST
CONSTGOODTEST:
	movq	0, %rax
	movq	%rax, ANY
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
