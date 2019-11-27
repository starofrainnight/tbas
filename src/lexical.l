%option noyywrap

%{
#include <stdio.h>
// #define YY_DECL int yylex()

// Our header must before parser's header! otherwise there have warnings :
// "assignment from incompatible pointer type [-Wincompatible-pointer-types]"
#include "main.h"
#include "syntax-parser.h"


%}

PAT_NEWLINE     \r\n|\n|\r
PAT_IDENT       (?i:[a-z_][a-z0-9_]*)
PAT_SPACE       [ \t\v]

%x COND_LINE_COMMENT

%%

{PAT_SPACE}+            ; /* ignore all whitespace, no passing to parser. */
[0-9]+\.[0-9]+ 	        { YY_SAVE_TOKEN(); return TOK_FLOAT;}
[0-9]+		            { YY_SAVE_TOKEN(); return TOK_INT;}
(?i:REM)                { BEGIN(COND_LINE_COMMENT); } /* ignore all line comments, no passing to parser. */
<COND_LINE_COMMENT>{PAT_NEWLINE}    { BEGIN(INITIAL); }
<COND_LINE_COMMENT>.*   ;
{PAT_NEWLINE}       { return TOK_NEWLINE; }
(?i:END)            { return TOK_END; }
(?i:LET)            { return TOK_LET; }
(?i:CALL)           { return TOK_CALL; }
(?i:FUNC)           { return TOK_FUNC; }
{PAT_IDENT}         { YY_SAVE_TOKEN(); return TOK_IDENT; }
{PAT_IDENT}{PAT_SPACE}*\:  { YY_SAVE_TOKEN(); return TOK_LABEL; }
"+"		            { return TOK_PLUS; }
"-"		            { return TOK_MINUS; }
"*"		            { return TOK_MULTIPLY; }
"/"		            { return TOK_DIV; }
"("		            { return TOK_LEFT_PAR; }
")"		            { return TOK_RIGHT_PAR; }
"="		            { return TOK_EQUAL; }
","		            { return TOK_COMMA; }
.                   { printf("Unknown token(%d): %s\n", yyget_lineno(), yyget_text()); yyterminate(); }
%%
