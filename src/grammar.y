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

%token              IF PRINT SEMICOL PLUS MINUS 
                    LPAREN RPAREN LBRACE RBRACE;
%token  <int_val>   NUMBER;
%type   <node_p>    body line constant statement expression block;

%start parsetree

%%

parsetree   : body                               { eval($1); }
            ;
body        : line                               { $$ = body_n($1); }
            | body line                          { body_push($1, $2); $$ = $1; }
            ;
line        : statement SEMICOL
            | expression SEMICOL
            | block
            ;
statement   : PRINT expression                   { $$ = print_n($2); }
            ;
expression  : expression PLUS constant           { $$ = add_n($1, $3); }
            | expression MINUS constant          { $$ = subtract_n($1, $3); }
            | constant                           { $$ = $1; }
            ;
block       : IF expression LBRACE body RBRACE   { $$ = if_n($2, $4); }
            ;
constant    : NUMBER                             { $$ = constant_n($1); }
            ;
