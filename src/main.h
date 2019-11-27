#ifndef _9M_MAIN_42951ACC
#define _9M_MAIN_42951ACC

/**
 * The header of compiler parser
 *
 * Contained all as node types related stuffs that provied for bison generate
 * the AST tree.
 *
 * @author Hong-She Liang <starofrainnight@gmail.com>
 * @date 2019-11-16
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/**
 * Save the current lexical token string to `yylval.value_str`, so the syntax
 * parser could be obtain that string later.
 *
 * Only use in lexical actions.
 */
#define YY_SAVE_TOKEN() \
  { yylval.value_str = yyget_text(); }

// Extern function and variables
extern int yylex();
extern int yyparse();
extern void yyerror(const char *s);
extern FILE *yyin;
extern an_program_t *g_an_program;

#endif