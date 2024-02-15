#ifndef TOKEN_H
#define TOKEN_H
struct token {
  unsigned int row;
  unsigned int col;
  unsigned long int code;
  char *_data;
  unsigned int dataSize;
};
typedef struct token Token;

extern Token *_tokens;
extern unsigned long int tokenCount;

Token create_token(unsigned int row, unsigned int col, unsigned long int code,
                   char _data[], unsigned int dataSize);
void add_to_tokens(Token token);
#endif