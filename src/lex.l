%{
	#include <stdio.h>
	#include <string.h>
	#include "src/nodes.h"
	#include "grammar.tab.h"
	void yyerror(char*);
	int yyparse(void); 
%}

%%

"print"                { return PRINT; }
[0-9][0-9]*(.[0-9]+)?  { yylval.int_val = atoi(yytext); return NUMBER; }
"+"                    { return PLUS; }
[ \t\n]+               ; /* skip whitespace */ 
.                      { yyerror("Invalid token\n"); exit(1); }
%%
