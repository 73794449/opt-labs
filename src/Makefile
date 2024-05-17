CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0
INCLUDE=-I./util/ -I./syntax_state/ -I./lexer_state/ -I./semant_state/

SRCDIR=./
UTILDIR=$(SRCDIR)util/
SYNTAXDIR=$(SRCDIR)syntax_state/
LEXERDIR=$(SRCDIR)lexer_state/
SEMANTDIR=$(SRCDIR)semant_state/
TESTDIR=../tests/
SEM_TESTDIR=$(TESTDIR)tests_semant/

TESTFILENAME=input.sig
TESTOUTNAME=output.sig
CASEGOODTEST=$(SEM_TESTDIR)casegoodtest
CONSTBADTEST=$(SEM_TESTDIR)constbadtest
CONSTGOODTEST=$(SEM_TESTDIR)constgoodtest
MAXBADTEST=$(SEM_TESTDIR)maxbadtest
MAXGOODTEST=$(SEM_TESTDIR)maxgoodtest
MINIMALGOODTEST=$(SEM_TESTDIR)minimalgoodtest
VARBADTEST=$(SEM_TESTDIR)varbadtest
VARGOODTEST=$(SEM_TESTDIR)vargoodtest



SRC=$(wildcard $(SRCDIR)*.c)
UTILSRC=$(wildcard $(UTILDIR)*.c)
SYNTAXSRC=$(wildcard $(SYNTAXDIR)*.c)
LEXERSRC=$(wildcard $(LEXERDIR)*.c)
SEMANTSRC=$(wildcard $(SEMANTDIR)*.c)

OBJ=$(SRC:.c=.o) $(UTILSRC:.c=.o) $(SYNTAXSRC:.c=.o) $(LEXERSRC:.c=.o)  $(SEMANTSRC:.c=.o)

EXECUTABLE=outDebug.exe

.PHONY: all clean

all: $(EXECUTABLE)

test_semant: test_casegoodtest test_constbadtest test_constgoodtest test_maxbadtest test_maxgoodtest test_minimalgoodtest test_varbadtest test_vargoodtest
	
test_casegoodtest: 
	$(EXECUTABLE) -f $(CASEGOODTEST)/$(TESTFILENAME) -o $(CASEGOODTEST)/$(TESTOUTNAME)
test_constbadtest: 
	$(EXECUTABLE) -f $(CONSTBADTEST)/$(TESTFILENAME) -o $(CONSTBADTEST)/$(TESTOUTNAME)
test_constgoodtest: 
	$(EXECUTABLE) -f $(CONSTGOODTEST)/$(TESTFILENAME) -o $(CONSTGOODTEST)/$(TESTOUTNAME)
test_maxbadtest: 
	$(EXECUTABLE) -f $(MAXBADTEST)/$(TESTFILENAME) -o $(MAXBADTEST)/$(TESTOUTNAME)
test_maxgoodtest: 
	$(EXECUTABLE) -f $(MAXGOODTEST)/$(TESTFILENAME) -o $(MAXGOODTEST)/$(TESTOUTNAME)
test_minimalgoodtest: 
	$(EXECUTABLE) -f $(MINIMALGOODTEST)/$(TESTFILENAME) -o $(MINIMALGOODTEST)/$(TESTOUTNAME)
test_varbadtest: 
	$(EXECUTABLE) -f $(VARBADTEST)/$(TESTFILENAME) -o $(VARBADTEST)/$(TESTOUTNAME)
test_vargoodtest: 
	$(EXECUTABLE) -f $(VARGOODTEST)/$(TESTFILENAME) -o $(VARGOODTEST)/$(TESTOUTNAME)

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)