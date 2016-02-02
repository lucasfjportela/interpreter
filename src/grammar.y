%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/nodes.h"
extern int yylex();
extern void yyerror(char*);
%}

%union {
  int     int_val;
  node*   node_p;
}

%token              PRINT PLUS MINUS;
%token  <int_val>   NUMBER;
%type   <node_p>    line expression constant;

%start parsetree

%%

parsetree   : line                      { eval($1); }
            ;
line        : PRINT expression          { $$ = print_n($2); }
            ;
expression  : expression PLUS constant  { $$ = add_n($1, $3); }
            | expression MINUS constant { $$ = subtract_n($1, $3); }
            | constant                  { $$ = $1; }
            ;
constant    : NUMBER                    { $$ = constant_n($1); }
            ;
