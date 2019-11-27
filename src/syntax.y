%require "3.4"

%{
#include "main.h"
%}

// %language "C++"
%union {
	const char * value_str;
	an_assignment_t * assignment;
	an_node_t * stmt;
	an_func_call_t * func_call;
	list_t func_call_params;
}

%token <value_str> TOK_INT TOK_FLOAT TOK_IDENT TOK_LABEL
%token TOK_PLUS TOK_MINUS TOK_MULTIPLY TOK_DIV
%token TOK_LEFT_PAR TOK_RIGHT_PAR TOK_COMMA
%token TOK_NEWLINE TOK_LINE_COMMENT
%token TOK_END TOK_LET TOK_FUNC TOK_CALL
%left TOK_PLUS TOK_MINUS
%left TOK_MULTIPLY TOK_DIV
%right TOK_EQUAL

%type <assignment> assignment
%type <stmt> expr stmt
%type <func_call> func_call func_call_expr
%type <func_call_params> func_call_params

%start stmts

%%

stmts: stmt { list_append(g_an_program->stmts, $1); }
	| stmts stmt { list_append(g_an_program->stmts, $2); }
;

stmt: TOK_NEWLINE 	{}
	| TOK_END 		{ $$ = an_node_new(ANT_END); }
	| assignment	{ $$ = (an_node_t *)$1; }
	| func_call		{ $$ = (an_node_t *)$1; }
;

assignment: TOK_LET TOK_IDENT TOK_EQUAL expr {
	$$ = an_assignment_new((an_node_t *)an_value_str_new($2), $4);
	}
	| TOK_IDENT TOK_EQUAL expr { $$ = an_assignment_new((an_node_t *)an_value_str_new($1), $3);}
;

func_call_params: expr { $$ = list_new(NULL); list_append($$, $1);}
	| func_call_params TOK_COMMA expr { list_append($$, $1); }
;

func_call: TOK_IDENT TOK_NEWLINE { $$ = an_func_call_new($1); }
	| TOK_IDENT func_call_params TOK_NEWLINE {
		$$ = an_func_call_new($1);
		list_delete(&$$->params);
		$$->params = $2;
		}
	| TOK_CALL func_call_expr TOK_NEWLINE {
		$$ = $2;
	}
;

func_call_expr: TOK_IDENT TOK_LEFT_PAR TOK_RIGHT_PAR {
		$$ = an_func_call_new($1);
	}
	| TOK_IDENT TOK_LEFT_PAR func_call_params TOK_RIGHT_PAR {
		$$ = an_func_call_new($1);
		list_delete(&$$->params);
		$$->params = $3;
	}
;

expr: TOK_INT			{ $$ = (an_node_t *)an_value_int_new(atoi($1)); }
	| TOK_FLOAT 		{ $$ = (an_node_t *)an_value_float_new(atof($1)); }
	| TOK_IDENT 		{ $$ = (an_node_t *)an_value_str_new($1); }
	| func_call_expr	{ $$ = (an_node_t *)$1; }
	| expr TOK_PLUS expr		{ $$ = (an_node_t *)an_expr_math_new(ANT_EXPR_PLUS, $1, $3); }
	| expr TOK_MINUS expr		{ $$ = (an_node_t *)an_expr_math_new(ANT_EXPR_MINUS, $1, $3); }
	| expr TOK_MULTIPLY expr	{ $$ = (an_node_t *)an_expr_math_new(ANT_EXPR_MULTIPLY, $1, $3); }
	| expr TOK_DIV expr		{ $$ = (an_node_t *)an_expr_math_new(ANT_EXPR_DIV, $1, $3); }
	| TOK_LEFT_PAR expr TOK_RIGHT_PAR		{ $$ = (an_node_t *)$2; }
;

%%

