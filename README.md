# OPT-RGR(LAB2): "РОЗРОБКА СИНТАКСИЧНОГО АНАЛІЗАТОРА"
## Usage

    ./opt-lab <filename>
    -f <filename>            Input filename
    -o <filename>            Output filename
    -v                       Verbose output

## Мета лабораторної роботи
Метою розрахунково-графічної роботи «Розробка синтаксисного аналізатора» є засвоєння теоретичного матеріалу та набуття практичного досвіду і практичних навичок розробки синтаксичних аналізаторів (парсерів).
## Постановка задачі 
1. Розробити програму синтаксичного аналізатора (СА) для підмножини мови програмування SIGNAL згідно граматики за варіантом.
2. Програма має забезпечувати наступне:
* читання рядка лексем та таблиць, згенерованих лексичним аналізатором, який було розроблено в лабораторній роботі «Розробка лексичного аналізатора»;
* синтаксичний аналіз (розбір) програми, поданої рядком лексем (алгоритм синтаксичного аналізатора вибирається за варіантом);
* побудову дерева розбору;
* формування таблиць ідентифікаторів та різних констант з повною інформацією, необхідною для генерування коду;
* формування лістингу вхідної програми з повідомленнями про лексичні та синтаксичні помилки.

## Варіант 23
### Syntax analizer:
низхідний розбір за алгоритмом аналізуючої машини Кнута;
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

## Building

    git clone https://github.com/73794449/opt-labs.git
    cd ./opt-labs/src
    make all

