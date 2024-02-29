#include "token_structure.h"
#include "id_generator.h"
Token create_token(size_t row, size_t col,
                   char *_data, size_t dataSize, __uint8_t type) {
  size_t code = get_id(row,col,type);
  Token token = {row, col, code, _data, dataSize};
  return token;
}
Token create_token_with_code(size_t row, size_t col,
                   char *_data, size_t dataSize,size_t code)
                   {
                      Token token = {row, col, code, _data, dataSize};
  return token;
                   }