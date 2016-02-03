%{
#include <stdio.h>
#include <string.h>
#include "src/nodes.h"
#include "grammar.tab.h"
void yyerror(char*);
int yyparse(void); 
%}

%option noyywrap
%option nounput
%option noinput

%%

[ \t\n]+   ; /* skip whitespace */ 
"#".+     ; /* skip comments */
"if"       { return IF; }
"print"    { return PRINT; }
[0-9]+     { yylval.int_val = atoi(yytext); return NUMBER; }
";"        { return SEMICOL; }
"("        { return LPAREN; }
")"        { return RPAREN; }
"{"        { return LBRACE; }
"}"        { return RBRACE; }
"+"        { return PLUS; }
"-"        { return MINUS; }
.          { yyerror("Invalid token\n"); exit(1); }
%%
