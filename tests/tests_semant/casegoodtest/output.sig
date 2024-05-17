|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|CASEGOODTEST
|     1|    22|    59|;
|     2|     2|   405|CONST
|     3|     6|   403|BEGIN
|     4|     6|  1002|ELEM
|     4|    11|   303|:=
|     4|    14|   501|20
|     4|    17|    43|+
|     4|    19|   502|10
|     4|    21|    59|;
|     5|     6|   406|CASE
|     5|    11|  1002|ELEM
|     5|    16|    45|-
|     5|    18|   503|0
|     5|    20|   407|OF
|     6|     6|   504|40
|     6|     9|    45|-
|     6|    11|   502|10
|     6|    13|    58|:
|     7|     6|    47|/
|     7|     7|  1002|ELEM
|     7|    12|   303|:=
|     7|    15|   501|20
|     7|    18|    43|+
|     7|    20|   502|10
|     7|    22|    59|;
|     7|    23|    92|\
|     8|     6|   501|20
|     8|     9|    43|+
|     8|    11|   505|30
|     8|    13|    58|:
|     9|     6|    47|/
|     9|     7|  1003|ELEM1
|     9|    13|   303|:=
|     9|    16|   505|30
|     9|    19|    43|+
|     9|    21|   502|10
|     9|    23|    59|;
|     9|    24|    92|\
|    10|     6|   408|ENDCASE
|    10|    13|    59|;
|    11|     6|   404|END
|    11|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||CASEGOODTEST
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
|||||||ELEM
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
||||||||<empty>
|||||||||<empty>
|||||;
||||<statements-list>
|||||<statement>
||||||CASE
||||||<expression>
|||||||<summand>
||||||||<variable-identifier>
|||||||||<identifier>
||||||||||ELEM
|||||||<summands-list>
||||||||<add-instruction>
|||||||||-
||||||||<summand>
|||||||||<unsigned-integer>
||||||||||0
||||||||<summands-list>
|||||||||<empty>
||||||||||<empty>
||||||OF
||||||<alternatives-list>
|||||||<alternative>
||||||||<expression>
|||||||||<summand>
||||||||||<unsigned-integer>
|||||||||||40
|||||||||<summands-list>
||||||||||<add-instruction>
|||||||||||-
||||||||||<summand>
|||||||||||<unsigned-integer>
||||||||||||10
||||||||||<summands-list>
|||||||||||<empty>
||||||||||||<empty>
||||||||:
||||||||/
||||||||<statements-list>
|||||||||<statement>
||||||||||<variable-identifier>
|||||||||||<identifier>
||||||||||||ELEM
||||||||||:=
||||||||||<expression>
|||||||||||<summand>
||||||||||||<unsigned-integer>
|||||||||||||20
|||||||||||<summands-list>
||||||||||||<add-instruction>
|||||||||||||+
||||||||||||<summand>
|||||||||||||<unsigned-integer>
||||||||||||||10
||||||||||||<summands-list>
|||||||||||||<empty>
||||||||||||||<empty>
||||||||||;
|||||||||<empty>
||||||||||<empty>
||||||||\
|||||||<alternatives-list>
||||||||<alternative>
|||||||||<expression>
||||||||||<summand>
|||||||||||<unsigned-integer>
||||||||||||20
||||||||||<summands-list>
|||||||||||<add-instruction>
||||||||||||+
|||||||||||<summand>
||||||||||||<unsigned-integer>
|||||||||||||30
|||||||||||<summands-list>
||||||||||||<empty>
|||||||||||||<empty>
|||||||||:
|||||||||/
|||||||||<statements-list>
||||||||||<statement>
|||||||||||<variable-identifier>
||||||||||||<identifier>
|||||||||||||ELEM1
|||||||||||:=
|||||||||||<expression>
||||||||||||<summand>
|||||||||||||<unsigned-integer>
||||||||||||||30
||||||||||||<summands-list>
|||||||||||||<add-instruction>
||||||||||||||+
|||||||||||||<summand>
||||||||||||||<unsigned-integer>
|||||||||||||||10
|||||||||||||<summands-list>
||||||||||||||<empty>
|||||||||||||||<empty>
|||||||||||;
||||||||||<empty>
|||||||||||<empty>
|||||||||\
||||||||<empty>
|||||||||<empty>
||||||ENDCASE
||||||;
|||||<empty>
||||||<empty>
|||END
||.

CODEGEN:
.section .rodata


.section .bbs
	ELEM:	.space 8
	ELEM:	.space 8
	ELEM1:	.space 8


.section .text
.globl main
main:
	jmp CASEGOODTEST
CASEGOODTEST:
	movq	20, %rax
	subq	10, %rax
	movq	%rax, ELEM
	movq	ELEM, %rax
	subq	0, %rax
	movq	40, %rbx
	subq	10, %rbx
	cmpq	%rax, %rbx
	je	?L0
	movq	20, %rbx
	subq	30, %rbx
	cmpq	%rax, %rbx
	je	?L1
	jmp	?L2
?L0: NOP
	movq	20, %rax
	subq	10, %rax
	movq	%rax, ELEM
	jmp	?L2
?L1: NOP
	movq	30, %rax
	subq	10, %rax
	movq	%rax, ELEM1
	jmp	?L2
?L2: NOP
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
