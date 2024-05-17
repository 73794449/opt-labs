# OPT-LABS(ALL): "РОЗРОБКА ГЕНЕРАТОРА КОДУ"

## Використання

```
./outDebug.exe
-f <filename>            Input filename
-o <filename>            Output filename
-q                       Quiet mode
-offlexer                Do not output lexer
-offsyntax               Do not output syntax
-offcodegen              Do not output codegen
-v <filename>            Verify filename
```

## Мета лабораторної роботи

Метою лабораторної роботи «Розробка генератора коду» є засвоєння теоретичного матеріалу та набуття практичного досвіду і практичних навичок розробки генераторів коду.

## Постановка задачі

1. Розробити програму генератора коду (ГК) для підмножини мови програмування SIGNAL, заданої за варіантом.
2. Програма генератора коду має забезпечувати:

* читання дерева розбору та таблиць, створених синтаксичним аналізатором, що було розроблено в розрахунково-графічній роботі;
* виявлення семантичних помилок;
* генерацію коду та/або побудову внутрішніх таблиць для генерації коду.

3. Скомпонувати повний компілятор, що складається з розроблених раніше лексичного та синтаксичного аналізаторів і генератора коду, який забезпечує наступне:

* генерацію коду та/або побудову внутрішніх таблиць для генерації коду;
* формування лістингу вхідної програми з повідомленнями про лексичні, синтаксичні та семантичні помилки.

## Варіант 23

### Синтаксичний аналізатор

Низхідний розбір за алгоритмом аналізуючої машини Кнута

### Граматика:

```
<signal-program> --> <program>
<program> --> PROGRAM <procedure-identifier> ;
<block>.
<block> --> <declarations> BEGIN <statements-list> END
<declarations> --> <constant-declarations>
<constant-declarations> --> CONST <constantdeclarations-list> |
<empty>
<constant-declarations-list> --> <constantdeclaration> <constant-declarations-list> |
<empty>
<constant-declaration> --> <constant-identifier> =
<constant>;
<statements-list> --> <statement> <statements-list> |
<empty>
<statement> --> CASE <expression> OF <alternativeslist> ENDCASE ;
<alternatives-list> --> <alternative> <alternativeslist> |
<empty>
<alternative> --> <expression> : /<statements-list>\
<expression> --> <summand> <summands-list> |
- <summand> <summands-list>
<summands-list> --> <add-instruction> <summand>
<summands-list> |
<empty>
<add-instruction> --> + |
-
<summand> --> <variable-identifier> |
<unsigned-integer>
<constant> --> <unsigned-integer>
<variable-identifier> --> <identifier>
<constant-identifier> --> <identifier>
<procedure-identifier> --> <identifier>
<identifier> --> <letter><string>
<string> --> <letter><string> |
<digit><string> |
<empty>
<unsigned-integer> --> <digit><digits-string>
<digits-string> --> <digit><digits-string> |
<empty>
<digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<letter> --> A | B | C | D | ... | Z
```

### Додаткова граматика

Основна граматика мала недолік, а саме відсутність інших <statement> крім CASE OF, що призводило до циклічної залежності, бо <statement> CASE OF має відповідну залежність від <alternativeslist>, та <alternative> відповідно. Що й призводило до циклічної залежності CASE OF від самого себе.

```
<statement> --> CASE <expression> OF <alternativeslist> ENDCASE ;
<alternatives-list> --> <alternative> <alternativeslist> | <empty>
<alternative> --> <expression> : /<statements-list>\
<statements-list> --> <statement> <statements-list> | <empty>
```

З метою звільнення від циклічної залежності було змінене правило <statement>

```
<statement> --> CASE <expression> OF <alternativeslist> ENDCASE ;| <variable-identifier> := <expression> ;
```

### Реалізація машини Кнута, таблиця реалізована у такому вигляді
Дефініції addr_to можна знайти в ([terms.h](https://github.com/73794449/opt-labs/blob/codegen/src/syntax_state/terms.h)) 

```
  /*rule-id addr_to                     term        at     af */
  /*<signal-program> --> <program> */
  rule(0,  SIGNAL_PROGRAM,              NULL,       false, ERROR);
  rule(1,  PROGRAM,                     NULL,       false, ERROR);
  rule(2,  SIGNAL_PROGRAM_FINISH,       NULL,       true,  ERROR);
  /*<program> --> PROGRAM <procedure-identifier> ; <block> .*/
  rule(3,  0,                           "PROGRAM",  false, ERROR);
  rule(4,  PROCEDURE_IDENTIFIER,        NULL,       false, ERROR);
  rule(5,  0,                           ";",        false, ERROR);
  rule(6,  BLOCK,                       NULL,       false, ERROR);
  rule(7,  0,                           ".",        true,  ERROR);
  /*<block> --> <declarations> BEGIN <statements-list> END*/
  rule(8,  DECLARATIONS,                NULL,       false, ERROR);
  rule(9,  0,                           "BEGIN",    false, ERROR);
  rule(10, STATEMENTS_LIST,             NULL,       false, ERROR);
  rule(11, 0,                           "END",      true,  ERROR);
  /*<declarations> --> <constant-declarations>*/
  rule(12, CONSTANT_DECLARATIONS,       NULL,       true,  ERROR);
  /*<constant-declarations> --> CONST <constant-declarations-list> | <empty>*/
  rule(13, 0,                           "CONST",    false, ERROR);
  rule(14, CONSTANT_DECLARATIONS_LIST,  NULL,       true,  15);
  rule(15, EMPTY,                       NULL,       true,  ERROR);
  /*<constant-declarations-list> --> <constantdeclaration>
   * <constant-declarations-list> | <empty>*/
  rule(16, CONSTANT_DECLARATION,        NULL,       false, ERROR);
  rule(17, CONSTANT_DECLARATIONS_LIST,  NULL,       true,  18);
  rule(18, EMPTY, NULL, true, ERROR);
  /*<constant-declaration> --> <constant-identifier> = <constant>;*/
  rule(19, CONSTANT_IDENTIFIER,         NULL,       false, ERROR);
  rule(20, 0,                           "=",        false, ERROR);
  rule(21, CONSTANT,                    NULL,       false, ERROR);
  rule(22, 0,                           ";",        true,  ERROR);
  /*<statements-list> --> <statement> <statement-list> | <empty>*/
  rule(23, STATEMENT,                   NULL,       false, ERROR);
  rule(24, STATEMENTS_LIST,             NULL,       true,  25);
  rule(25, EMPTY,                       NULL,       true,  ERROR);
  /*<statement> --> CASE <expression> OF <alternativeslist> ENDCASE ;| <variable-identifier> := <expression> ;*/
  rule(26, 0,                           "CASE",     false, 32);
  rule(27, EXPRESSION,                  NULL,       false, ERROR);
  rule(28, 0,                           "OF",       false, ERROR);
  rule(29, ALTERNATIVES_LIST,           NULL,       false, ERROR);
  rule(30, 0,                           "ENDCASE",  false, ERROR);
  rule(31, 0,                           ";",        true,  ERROR);
  rule(32, VARIABLE_IDENTIFIER,         NULL,       false, ERROR);
  rule(33, 0,                           ":=",       false, ERROR);
  rule(34, EXPRESSION,                  NULL,       false, ERROR);
  rule(35, 0,                           ";",        true,  ERROR);
  /*<alternatives-list> --> <alternative> <alternativeslist> | <empty>*/
  rule(36, ALTERNATIVE,                 NULL,       false, ERROR);
  rule(37, ALTERNATIVES_LIST,           NULL,       true,  38);
  rule(38, EMPTY,                       NULL,       true,  ERROR);
  /*<alternative> --> <expression> : /<statements-list>\*/
  rule(39, EXPRESSION,                  NULL,       false, ERROR);
  rule(40, 0,                           ":",        false, ERROR);
  rule(41, 0,                           "/",        false, ERROR);
  rule(42, STATEMENTS_LIST,             NULL,       false, ERROR);
  rule(43, 0,                           "\\",       true,  ERROR);
  /*<expression> --> <summand> <summands-list> | - <summand> <summands-list>*/
  rule(44, SUMMAND,                     NULL,       false, 46);
  rule(45, SUMMANDS_LIST,               NULL,       true,  ERROR);
  rule(46, 0,                           "-",        false, ERROR);
  rule(47, SUMMAND,                     NULL,       false, ERROR);
  rule(48, SUMMANDS_LIST,               NULL,       true,  ERROR);
  /*<summands-list> --> <add-instruction> <summand> | <summands-list> | <empty>*/
  rule(49, ADD_INSTRUCTION,             NULL,       false, 54);
  rule(50, SUMMAND,                     NULL,       false, ERROR);
  rule(51, SUMMANDS_LIST,               NULL,       true,  52);
  rule(52, ADD_INSTRUCTION,             NULL,       false, 54);
  rule(53, SUMMAND,                     NULL,       true,  ERROR);
  rule(54, EMPTY,                       NULL,       true,  ERROR);
  /*<add-instruction> --> + | -*/
  rule(55, 0,                           "+",        true,  56);
  rule(56, 0,                           "-",        true,  ERROR);
  /*<summand> --> <variable-identifier> | <unsigned-integer>*/
  rule(57, VARIABLE_IDENTIFIER,         NULL,       true,  58);
  rule(58, UNSIGNED_INTEGER,            NULL,       true,  ERROR);
  /*<constant> --> <unsigned-integer>*/
  rule(59, UNSIGNED_INTEGER,            NULL,       true,  ERROR);
  /*<variable-identifier> --> <identifier>*/
  rule(60, IDENTIFIER,                  NULL,       true,  ERROR);
  /*<constant-identifier> --> <identifier>*/
  rule(61, IDENTIFIER,                  NULL,       true,  ERROR);
  /*<procedure-identifier> --> <identifier>*/
  rule(62, IDENTIFIER,                  NULL,       true,  ERROR);

  /* lexer-base-types */
  /*    rule-id       addr_to term at    af */
  rule(UNSIGNED_INTEGER,    0, "", true, ERROR);
  rule(IDENTIFIER,          0, "", true, ERROR);
  rule(STRING,              0, "", true, ERROR);
  rule(EMPTY,               0, "", true, ERROR);
```

## Генератор коду

Результат подається у вигляді ассемблерного коду NASM

## Building

git clone https://github.com/73794449/opt-labs.git
cd ./opt-labs/src
make all
