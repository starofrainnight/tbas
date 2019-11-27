#include "main.h"
#include <string.h>
#include "common.h"
#include "syntax-parser.h"

enum CompilerError {
  CE_OK = 0,
  CE_NO_FILE_ARGUMENT,
  CE_PARSE_FAILED,
  CE_FILE_NOT_FOUND
};

// Variables:

// The global AST root
an_program_t *g_an_program = NULL;

// Application name
static const char *s_app_name = "";

void show_help() {
  printf(
      "Usage: %s [FILE_NAME]\n\n"
      "A simple compiler program use for demonstrate how to write a\n"
      "programming language compiler by flex/bison with C language. \n\n"
      "It's paser the input file as a simple basic language.\n\n",
      s_app_name);
}

int main(int argc, char *argv[]) {
  s_app_name = argv[0];

  --argc, ++argv;  // Skip over program name

  if (argc <= 0) {
    show_help();
    return CE_NO_FILE_ARGUMENT;
  }

  g_an_program = an_program_new();

  yyin = fopen(argv[0], "r");
  if (!yyin) {
    printf("File \"%s\" not found!\n", argv[0]);
    return CE_FILE_NOT_FOUND;
  }

  printf("Parsing %s ...\n", argv[0]);

  do {
    yyparse();
  } while (!feof(yyin));

  // AST is ready inside the g_an_program

  // TODO Directly execute the program (without generate code from it)

  return CE_OK;
}

void yyerror(const char *s) {
  printf("Parse error: %s\n", s);
  exit(CE_PARSE_FAILED);
}
