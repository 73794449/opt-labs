|Line  |Column|Code  |Data  
+------+------+------+------
|     1|     2|   401|PROGRAM
|     1|    10|  1001|MAXBADTEST
|     1|    20|    59|;
|     2|     2|   405|CONST
|     3|     6|  1001|MAXBADTEST
|     3|    17|    61|=
|     3|    19|   501|10
|     3|    21|    59|;
|     4|     6|  1002|SOME
|     4|    11|    61|=
|     4|    13|   502|20
|     4|    15|    59|;
|     5|     6|  1003|SOME2
|     5|    12|    61|=
|     5|    14|   503|40
|     5|    16|    59|;
|     6|     6|   403|BEGIN
|     7|     6|  1001|MAXBADTEST
|     7|    17|   303|:=
|     7|    20|   504|30
|     7|    22|    59|;
|     8|     6|  1004|VSOME
|     8|    12|   303|:=
|     8|    15|   501|10
|     8|    17|    59|;
|     9|     6|  1005|VSOME2
|     9|    13|   303|:=
|     9|    16|  1006|UNKNW
|     9|    22|    43|+
|     9|    24|   503|40
|     9|    26|    59|;
|    10|     6|   406|CASE
|    10|    11|  1005|VSOME2
|    10|    18|    43|+
|    10|    20|  1006|UNKNW
|    10|    26|    45|-
|    10|    28|   505|5
|    10|    30|   407|OF
|    11|     6|  1004|VSOME
|    11|    12|    45|-
|    11|    14|   506|1
|    11|    15|    58|:
|    12|    10|    47|/
|    12|    11|  1006|UNKNW
|    12|    17|   303|:=
|    12|    20|   503|40
|    12|    23|    43|+
|    12|    25|   505|5
|    12|    27|    45|-
|    12|    29|  1004|VSOME
|    12|    34|    59|;
|    12|    35|    92|\
|    13|     6|  1004|VSOME
|    13|    12|    43|+
|    13|    14|   505|5
|    13|    15|    58|:
|    14|    10|    47|/
|    14|    11|  1007|RESULT2
|    14|    19|   303|:=
|    14|    22|   507|50
|    14|    25|    43|+
|    14|    27|  1004|VSOME
|    14|    33|    43|+
|    14|    35|   505|5
|    14|    36|    59|;
|    14|    37|    92|\
|    15|     6|   408|ENDCASE
|    15|    13|    59|;
|    16|     6|  1008|RESULT3
|    16|    14|   303|:=
|    16|    17|  1006|UNKNW
|    16|    23|    43|+
|    16|    25|   505|5
|    16|    26|    59|;
|    17|     6|   404|END
|    17|     9|    46|.
SYNTAX:
<signal-program>
|<program>
||PROGRAM
||<procedure-identifier>
|||<identifier>
||||MAXBADTEST
||;
||<block>
|||<declarations>
||||<constant-declarations>
|||||CONST
|||||<constant-declarations-list>
||||||<constant-declaration>
|||||||<constant-identifier>
||||||||<identifier>
|||||||||MAXBADTEST
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
|||||||||||SOME2
|||||||||=
|||||||||<constant>
||||||||||<unsigned-integer>
|||||||||||40
|||||||||;
||||||||<empty>
|||||||||<empty>
|||BEGIN
|||<statements-list>
||||<statement>
|||||<variable-identifier>
||||||<identifier>
|||||||MAXBADTEST
|||||:=
|||||<expression>
||||||<summand>
|||||||<unsigned-integer>
||||||||30
||||||<summands-list>
|||||||<empty>
||||||||<empty>
|||||;
||||<statements-list>
|||||<statement>
||||||<variable-identifier>
|||||||<identifier>
||||||||VSOME
||||||:=
||||||<expression>
|||||||<summand>
||||||||<unsigned-integer>
|||||||||10
|||||||<summands-list>
||||||||<empty>
|||||||||<empty>
||||||;
|||||<statements-list>
||||||<statement>
|||||||<variable-identifier>
||||||||<identifier>
|||||||||VSOME2
|||||||:=
|||||||<expression>
||||||||<summand>
|||||||||<variable-identifier>
||||||||||<identifier>
|||||||||||UNKNW
||||||||<summands-list>
|||||||||<add-instruction>
||||||||||+
|||||||||<summand>
||||||||||<unsigned-integer>
|||||||||||40
|||||||||<summands-list>
||||||||||<empty>
|||||||||||<empty>
|||||||;
||||||<statements-list>
|||||||<statement>
||||||||CASE
||||||||<expression>
|||||||||<summand>
||||||||||<variable-identifier>
|||||||||||<identifier>
||||||||||||VSOME2
|||||||||<summands-list>
||||||||||<add-instruction>
|||||||||||+
||||||||||<summand>
|||||||||||<variable-identifier>
||||||||||||<identifier>
|||||||||||||UNKNW
||||||||||<summands-list>
|||||||||||<add-instruction>
||||||||||||-
|||||||||||<summand>
||||||||||||<unsigned-integer>
|||||||||||||5
|||||||||||<summands-list>
||||||||||||<empty>
|||||||||||||<empty>
||||||||OF
||||||||<alternatives-list>
|||||||||<alternative>
||||||||||<expression>
|||||||||||<summand>
||||||||||||<variable-identifier>
|||||||||||||<identifier>
||||||||||||||VSOME
|||||||||||<summands-list>
||||||||||||<add-instruction>
|||||||||||||-
||||||||||||<summand>
|||||||||||||<unsigned-integer>
||||||||||||||1
||||||||||||<summands-list>
|||||||||||||<empty>
||||||||||||||<empty>
||||||||||:
||||||||||/
||||||||||<statements-list>
|||||||||||<statement>
||||||||||||<variable-identifier>
|||||||||||||<identifier>
||||||||||||||UNKNW
||||||||||||:=
||||||||||||<expression>
|||||||||||||<summand>
||||||||||||||<unsigned-integer>
|||||||||||||||40
|||||||||||||<summands-list>
||||||||||||||<add-instruction>
|||||||||||||||+
||||||||||||||<summand>
|||||||||||||||<unsigned-integer>
||||||||||||||||5
||||||||||||||<summands-list>
|||||||||||||||<add-instruction>
||||||||||||||||-
|||||||||||||||<summand>
||||||||||||||||<variable-identifier>
|||||||||||||||||<identifier>
||||||||||||||||||VSOME
|||||||||||||||<summands-list>
||||||||||||||||<empty>
|||||||||||||||||<empty>
||||||||||||;
|||||||||||<empty>
||||||||||||<empty>
||||||||||\
|||||||||<alternatives-list>
||||||||||<alternative>
|||||||||||<expression>
||||||||||||<summand>
|||||||||||||<variable-identifier>
||||||||||||||<identifier>
|||||||||||||||VSOME
||||||||||||<summands-list>
|||||||||||||<add-instruction>
||||||||||||||+
|||||||||||||<summand>
||||||||||||||<unsigned-integer>
|||||||||||||||5
|||||||||||||<summands-list>
||||||||||||||<empty>
|||||||||||||||<empty>
|||||||||||:
|||||||||||/
|||||||||||<statements-list>
||||||||||||<statement>
|||||||||||||<variable-identifier>
||||||||||||||<identifier>
|||||||||||||||RESULT2
|||||||||||||:=
|||||||||||||<expression>
||||||||||||||<summand>
|||||||||||||||<unsigned-integer>
||||||||||||||||50
||||||||||||||<summands-list>
|||||||||||||||<add-instruction>
||||||||||||||||+
|||||||||||||||<summand>
||||||||||||||||<variable-identifier>
|||||||||||||||||<identifier>
||||||||||||||||||VSOME
|||||||||||||||<summands-list>
||||||||||||||||<add-instruction>
|||||||||||||||||+
||||||||||||||||<summand>
|||||||||||||||||<unsigned-integer>
||||||||||||||||||5
||||||||||||||||<summands-list>
|||||||||||||||||<empty>
||||||||||||||||||<empty>
|||||||||||||;
||||||||||||<empty>
|||||||||||||<empty>
|||||||||||\
||||||||||<empty>
|||||||||||<empty>
||||||||ENDCASE
||||||||;
|||||||<statements-list>
||||||||<statement>
|||||||||<variable-identifier>
||||||||||<identifier>
|||||||||||RESULT3
|||||||||:=
|||||||||<expression>
||||||||||<summand>
|||||||||||<variable-identifier>
||||||||||||<identifier>
|||||||||||||UNKNW
||||||||||<summands-list>
|||||||||||<add-instruction>
||||||||||||+
|||||||||||<summand>
||||||||||||<unsigned-integer>
|||||||||||||5
|||||||||||<summands-list>
||||||||||||<empty>
|||||||||||||<empty>
|||||||||;
||||||||<empty>
|||||||||<empty>
|||END
||.

CODEGEN:
.section .rodata
	SOME:	.quad 20
	SOME2:	.quad 40


.section .bbs
	VSOME:	.space 8
	VSOME2:	.space 8
	UNKNW:	.space 8
	RESULT2:	.space 8
	RESULT3:	.space 8


.section .text
.globl main
main:
	jmp MAXBADTEST
MAXBADTEST:
	movq	30, %rax
	movq	%rax, MAXBADTEST
	movq	10, %rax
	movq	%rax, VSOME
	movq	UNKNW, %rax
	subq	40, %rax
	movq	%rax, VSOME2
	movq	VSOME2, %rax
	subq	UNKNW, %rax
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
	movq	%rax, UNKNW
	jmp	?L2
?L1: NOP
	movq	50, %rax
	subq	VSOME, %rax
	subq	5, %rax
	movq	%rax, RESULT2
	jmp	?L2
?L2: NOP
	movq	UNKNW, %rax
	subq	5, %rax
	movq	%rax, RESULT3
	movq	$60, %rax
	xor	%rdi, %rdi
	syscall
ERRORS:
#1|Error(Semantics): Cannot create const MAXBADTEST, name used by CONST or PROGRAM
#2|Error(Semantics): Cannot create var MAXBADTEST, name used by CONST or PROGRAM
#3|Error(Semantics): Variable UNKNW used before declaration
#4|Error(Semantics): Variable UNKNW used before declaration
