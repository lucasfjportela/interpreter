%{
#include <stdio.h>
#include <string.h>
#include "src/nodes.h"
#include "grammar.tab.h"
void yyerror(char*);
int yyparse(void); 
%}

%%

[ \t\n]+   ; /* skip whitespace */ 
"print"    { return PRINT; }
[0-9]+     { yylval.int_val = atoi(yytext); return NUMBER; }
"+"        { return PLUS; }
"-"        { return MINUS; }
.          { yyerror("Invalid token\n"); exit(1); }
%%
