|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|MAXGOODTEST
|     1|    21|    59|;
|     2|     2|   405|CONST
|     3|     6|  1002|SOME
|     3|    11|    61|=
|     3|    13|   501|20
|     3|    15|    59|;
|     4|     6|  1003|SOME2
|     4|    12|    61|=
|     4|    14|   502|40
|     4|    16|    59|;
|     5|     6|   403|BEGIN
|     6|     6|  1004|VSOME
|     6|    12|   303|:=
|     6|    15|   503|10
|     6|    17|    59|;
|     7|     6|  1005|VSOME2
|     7|    13|   303|:=
|     7|    16|  1004|VSOME
|     7|    22|    43|+
|     7|    24|   502|40
|     7|    26|    59|;
|     8|     6|   406|CASE
|     8|    11|  1005|VSOME2
|     8|    18|    43|+
|     8|    20|  1004|VSOME
|     8|    26|    45|-
|     8|    28|   504|5
|     8|    30|   407|OF
|     9|     6|  1004|VSOME
|     9|    12|    45|-
|     9|    14|   505|1
|     9|    15|    58|:
|    10|    10|    47|/
|    10|    11|  1006|RESULT1
|    10|    19|   303|:=
|    10|    22|   502|40
|    10|    25|    43|+
|    10|    27|   504|5
|    10|    29|    45|-
|    10|    31|  1004|VSOME
|    10|    36|    59|;
|    10|    37|    92|\
|    11|     6|  1004|VSOME
|    11|    12|    43|+
|    11|    14|   504|5
|    11|    15|    58|:
|    12|    10|    47|/
|    12|    11|  1007|RESULT2
|    12|    19|   303|:=
|    12|    22|   506|50
|    12|    25|    43|+
|    12|    27|  1004|VSOME
|    12|    33|    43|+
|    12|    35|   504|5
|    12|    36|    59|;
|    12|    37|    92|\
|    13|     6|   408|ENDCASE
|    13|    13|    59|;
|    14|     6|  1008|RESULT3
|    14|    14|   303|:=
|    14|    17|  1005|VSOME2
|    14|    24|    43|+
|    14|    26|   504|5
|    14|    27|    59|;
|    15|     6|   404|END
|    15|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||MAXGOODTEST
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
||||||<constant-declarations-list>
|||||||<constant-declaration>
||||||||<constant-identifier>
|||||||||<identifier>
||||||||||SOME2
||||||||=
||||||||<constant>
|||||||||<unsigned-integer>
||||||||||40
||||||||;
|||||||<empty>
||||||||<empty>
|||BEGIN
|||<statements-list>
||||<statement>
|||||<variable-identifier>
||||||<identifier>
|||||||VSOME
|||||:=
|||||<expression>
||||||<summand>
|||||||<unsigned-integer>
||||||||10
||||||<summands-list>
|||||||<empty>
||||||||<empty>
|||||;
||||<statements-list>
|||||<statement>
||||||<variable-identifier>
|||||||<identifier>
||||||||VSOME2
||||||:=
||||||<expression>
|||||||<summand>
||||||||<variable-identifier>
|||||||||<identifier>
||||||||||VSOME
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
|||||<statements-list>
||||||<statement>
|||||||CASE
|||||||<expression>
||||||||<summand>
|||||||||<variable-identifier>
||||||||||<identifier>
|||||||||||VSOME2
||||||||<summands-list>
|||||||||<add-instruction>
||||||||||+
|||||||||<summand>
||||||||||<variable-identifier>
|||||||||||<identifier>
||||||||||||VSOME
|||||||||<summands-list>
||||||||||<add-instruction>
|||||||||||-
||||||||||<summand>
|||||||||||<unsigned-integer>
||||||||||||5
||||||||||<summands-list>
|||||||||||<empty>
||||||||||||<empty>
|||||||OF
|||||||<alternatives-list>
||||||||<alternative>
|||||||||<expression>
||||||||||<summand>
|||||||||||<variable-identifier>
||||||||||||<identifier>
|||||||||||||VSOME
||||||||||<summands-list>
|||||||||||<add-instruction>
||||||||||||-
|||||||||||<summand>
||||||||||||<unsigned-integer>
|||||||||||||1
|||||||||||<summands-list>
||||||||||||<empty>
|||||||||||||<empty>
|||||||||:
|||||||||/
|||||||||<statements-list>
||||||||||<statement>
|||||||||||<variable-identifier>
||||||||||||<identifier>
|||||||||||||RESULT1
|||||||||||:=
|||||||||||<expression>
||||||||||||<summand>
|||||||||||||<unsigned-integer>
||||||||||||||40
||||||||||||<summands-list>
|||||||||||||<add-instruction>
||||||||||||||+
|||||||||||||<summand>
||||||||||||||<unsigned-integer>
|||||||||||||||5
|||||||||||||<summands-list>
||||||||||||||<add-instruction>
|||||||||||||||-
||||||||||||||<summand>
|||||||||||||||<variable-identifier>
||||||||||||||||<identifier>
|||||||||||||||||VSOME
||||||||||||||<summands-list>
|||||||||||||||<empty>
||||||||||||||||<empty>
|||||||||||;
||||||||||<empty>
|||||||||||<empty>
|||||||||\
||||||||<alternatives-list>
|||||||||<alternative>
||||||||||<expression>
|||||||||||<summand>
||||||||||||<variable-identifier>
|||||||||||||<identifier>
||||||||||||||VSOME
|||||||||||<summands-list>
||||||||||||<add-instruction>
|||||||||||||+
||||||||||||<summand>
|||||||||||||<unsigned-integer>
||||||||||||||5
||||||||||||<summands-list>
|||||||||||||<empty>
||||||||||||||<empty>
||||||||||:
||||||||||/
||||||||||<statements-list>
|||||||||||<statement>
||||||||||||<variable-identifier>
|||||||||||||<identifier>
||||||||||||||RESULT2
||||||||||||:=
||||||||||||<expression>
|||||||||||||<summand>
||||||||||||||<unsigned-integer>
|||||||||||||||50
|||||||||||||<summands-list>
||||||||||||||<add-instruction>
|||||||||||||||+
||||||||||||||<summand>
|||||||||||||||<variable-identifier>
||||||||||||||||<identifier>
|||||||||||||||||VSOME
||||||||||||||<summands-list>
|||||||||||||||<add-instruction>
||||||||||||||||+
|||||||||||||||<summand>
||||||||||||||||<unsigned-integer>
|||||||||||||||||5
|||||||||||||||<summands-list>
||||||||||||||||<empty>
|||||||||||||||||<empty>
||||||||||||;
|||||||||||<empty>
||||||||||||<empty>
||||||||||\
|||||||||<empty>
||||||||||<empty>
|||||||ENDCASE
|||||||;
||||||<statements-list>
|||||||<statement>
||||||||<variable-identifier>
|||||||||<identifier>
||||||||||RESULT3
||||||||:=
||||||||<expression>
|||||||||<summand>
||||||||||<variable-identifier>
|||||||||||<identifier>
||||||||||||VSOME2
|||||||||<summands-list>
||||||||||<add-instruction>
|||||||||||+
||||||||||<summand>
|||||||||||<unsigned-integer>
||||||||||||5
||||||||||<summands-list>
|||||||||||<empty>
||||||||||||<empty>
||||||||;
|||||||<empty>
||||||||<empty>
|||END
||.

CODEGEN:
.section .rodata
	SOME:	.quad 20
	SOME2:	.quad 40


.section .bbs
	VSOME:	.space 8
	VSOME2:	.space 8
	RESULT1:	.space 8
	RESULT2:	.space 8
	RESULT3:	.space 8


.section .text
.globl main
main:
	jmp MAXGOODTEST
MAXGOODTEST:
	movq	10, %rax
	movq	%rax, VSOME
	movq	VSOME, %rax
	subq	40, %rax
	movq	%rax, VSOME2
	movq	VSOME2, %rax
	subq	VSOME, %rax
	subq	5, %rax
	movq	VSOME, %rbx
	subq	1, %rbx
	cmpq	%rax, %rbx
	je	?L0
	movq	VSOME, %rbx
	subq	5, %rbx
	cmpq	%rax, %rbx
	je	?L1
	jmp	?L2
?L0: NOP
	movq	40, %rax
	subq	5, %rax
	subq	VSOME, %rax
	movq	%rax, RESULT1
	jmp	?L2
?L1: NOP
	movq	50, %rax
	subq	VSOME, %rax
	subq	5, %rax
	movq	%rax, RESULT2
	jmp	?L2
?L2: NOP
	movq	VSOME2, %rax
	subq	5, %rax
	movq	%rax, RESULT3
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
