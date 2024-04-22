CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0
INCLUDE=-Isrc/util/ -Isrc/syntax_state/ -Isrc/lexer_state/


SRCDIR=src/
UTILDIR=$(SRCDIR)/util/
SYNTAXDIR=$(SRCDIR)/syntax_state/
LEXERDIR=$(SRCDIR)/lexer_state/

SRC=$(wildcard $(SRCDIR)*.c)
UTILSRC=$(wildcard $(UTILDIR)*.c)
SYNTAXSRC=$(wildcard $(SYNTAXDIR)*.c)
LEXERSRC=$(wildcard $(LEXERDIR)*.c)

OBJ=$(SRC:.c=.o) $(UTILSRC:.c=.o) $(SYNTAXSRC:.c=.o) $(LEXERSRC:.c=.o) 

EXECUTABLE=outDebug.exe

.PHONY: all clean

all: $(EXECUTABLE)

true_test: $(EXECUTABLE) true_test.sig -o true_test_output

false_test: $(EXECUTABLE) false_test.sig -o false_test_output

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)