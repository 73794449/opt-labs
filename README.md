# OPT-LAB1: "РОЗРОБКА ЛЕКСИЧНОГО АНАЛІЗАТОРА"
## Usage

    ./opt-lab1 <filename>
    -f <filename> 		Input filename
    -o <filename>		Output filename
    -v					Verbose output

## Мета лабораторної роботи
Метою лабораторної роботи «Розробка лексичного аналізатора» є засвоєння теоретичного матеріалу та набуття практичного досвіду і практичних навичок розробки лексичних аналізаторів (сканерів). 
## Постановка задачі 
Розробити програму лексичного аналізатора (ЛА) для підмножини мови програмування SIGNAL. 
Лексичний аналізатор має забезпечувати наступні дії: 
* видалення (пропускання) пробільних символів: пробіл (код ASCII 32), повернення каретки (код ASCII 13); перехід на новий рядок (код ASCII 10), горизонтальна та вертикальна табуляція (коди ASCII 9 та 11), перехід на нову сторінку (код ASCII 12); 
* згортання ключових слів; 
* згортання багато-символьних роздільників (якщо передбачаються граматикою варіанту); 
* згортання констант із занесенням до таблиці значення та типу константи (якщо передбачаються граматикою варіанту); 
* згортання ідентифікаторів; 
* видалення коментарів, заданих у вигляді (*<текст коментаря>*); 
* формування рядка лексем з інформацією про позиції лексем; 
* заповнення таблиць ідентифікаторів та констант інформацією, отриманою під час згортки лексем; 
* виведення повідомлень про помилки.

## Варіант 23
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

    git clone https://github.com/73794449/opt-lab1.git
    cd ./opt-lab1
    gcc -g -O2 ./*.c -o opt-lab1

