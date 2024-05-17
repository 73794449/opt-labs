|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|VARBADTEST
|     1|    20|    59|;
|     2|     2|   405|CONST
|     3|     6|  1002|SOME
|     3|    11|    61|=
|     3|    13|   501|20
|     3|    15|    59|;
|     4|     6|   403|BEGIN
|     5|     6|  1001|VARBADTEST
|     5|    17|   303|:=
|     5|    20|   502|40
|     5|    23|    43|+
|     5|    25|   501|20
|     5|    27|    59|;
|     6|     6|  1002|SOME
|     6|    11|   303|:=
|     6|    14|   503|50
|     6|    17|    43|+
|     6|    19|   502|40
|     6|    21|    59|;
|     7|     6|   404|END
|     7|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||VARBADTEST
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
|||||||||20
|||||||;
||||||<empty>
|||||||<empty>
|||BEGIN
|||<statements-list>
||||<statement>
|||||<variable-identifier>
||||||<identifier>
|||||||VARBADTEST
|||||:=
|||||<expression>
||||||<summand>
|||||||<unsigned-integer>
||||||||40
||||||<summands-list>
|||||||<add-instruction>
||||||||+
|||||||<summand>
||||||||<unsigned-integer>
|||||||||20
|||||||<summands-list>
||||||||<empty>
|||||||||<empty>
|||||;
||||<statements-list>
|||||<statement>
||||||<variable-identifier>
|||||||<identifier>
||||||||SOME
||||||:=
||||||<expression>
|||||||<summand>
||||||||<unsigned-integer>
|||||||||50
|||||||<summands-list>
||||||||<add-instruction>
|||||||||+
||||||||<summand>
|||||||||<unsigned-integer>
||||||||||40
||||||||<summands-list>
|||||||||<empty>
||||||||||<empty>
||||||;
|||||<empty>
||||||<empty>
|||END
||.

CODEGEN:
.section .rodata
	SOME:	.quad 20


.section .bbs


.section .text
.globl main
main:
	jmp VARBADTEST
VARBADTEST:
	movq	40, %rax
	subq	20, %rax
	movq	%rax, VARBADTEST
	movq	50, %rax
	subq	40, %rax
	movq	%rax, SOME
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
ERRORS:
#1|Error(Semantics): Cannot create var VARBADTEST, name used by CONST or PROGRAM
#2|Error(Semantics): Cannot create var SOME, name used by CONST or PROGRAM
