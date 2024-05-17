|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|CONSTBADTEST
|     1|    22|    59|;
|     2|     2|   405|CONST
|     3|     6|  1001|CONSTBADTEST
|     3|    19|    61|=
|     3|    21|   501|10
|     3|    23|    59|;
|     4|     6|  1002|SOME
|     4|    11|    61|=
|     4|    13|   502|20
|     4|    15|    59|;
|     5|     6|  1002|SOME
|     5|    11|    61|=
|     5|    13|   503|30
|     5|    15|    59|;
|     6|     6|   403|BEGIN
|     7|     6|  1002|SOME
|     7|    11|   303|:=
|     7|    14|   504|40
|     7|    17|    43|+
|     7|    19|   501|10
|     7|    21|    59|;
|     8|     6|   404|END
|     8|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||CONSTBADTEST
||;
||<block>
|||<declarations>
||||<constant-declarations>
|||||CONST
|||||<constant-declarations-list>
||||||<constant-declaration>
|||||||<constant-identifier>
||||||||<identifier>
|||||||||CONSTBADTEST
|||||||=
|||||||<constant>
||||||||<unsigned-integer>
|||||||||10
|||||||;
||||||<constant-declarations-list>
|||||||<constant-declaration>
||||||||<constant-identifier>
|||||||||<identifier>
||||||||||SOME
||||||||=
||||||||<constant>
|||||||||<unsigned-integer>
||||||||||20
||||||||;
|||||||<constant-declarations-list>
||||||||<constant-declaration>
|||||||||<constant-identifier>
||||||||||<identifier>
|||||||||||SOME
|||||||||=
|||||||||<constant>
||||||||||<unsigned-integer>
|||||||||||30
|||||||||;
||||||||<empty>
|||||||||<empty>
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
||||||||40
||||||<summands-list>
|||||||<add-instruction>
||||||||+
|||||||<summand>
||||||||<unsigned-integer>
|||||||||10
|||||||<summands-list>
||||||||<empty>
|||||||||<empty>
|||||;
||||<empty>
|||||<empty>
|||END
||.

CODEGEN:
.section .rodata
	SOME:	.quad 20


.section .bbs


.section .text
.globl main
main:
	jmp CONSTBADTEST
CONSTBADTEST:
	movq	40, %rax
	subq	10, %rax
	movq	%rax, SOME
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
ERRORS:
#1|Error(Semantics): Cannot create const CONSTBADTEST, name used by CONST or PROGRAM
#2|Error(Semantics): Cannot create const SOME, name used by CONST or PROGRAM
#3|Error(Semantics): Cannot create var SOME, name used by CONST or PROGRAM
