#include <stdio.h>
#include <stdlib.h>

enum token_type {
  TOK_LBRACKET,
  TOK_RBRACKET,
  TOK_VARIABLE,
  TOK_NUMBER,
  TOK_LOG,
  TOK_OP,
};

struct token {
  enum token_type token_type;
  float number;
};

struct Tree *parse_expr(char *string) {
}



a * b + c - d * e

parse_pm . a * b + c - d * e
  parse_tdm . a * b + c - d * e
  parse_val . a * b + c - d * e
    parse_val a . * b + c - d * e (a)
  parse_tdm a . * b + c - d * e
  parse_tdm a * . b + c - d * e
    parse_val a * . b + c - d * e
    parse_val a * b . + c - d * e (b)
  parse_tdm a * b . + c - d * e (a * b)
parse_pm a * b . + c - d * e
parse_pm a * b + . c - d * e
  parse_tdm a * b + . c - d * e
    parse_val a * b + c . - d * e (c)
  parse_tdm a * b + c . - d * e (c)
parse_pm . - d * e

  parse_tdm
