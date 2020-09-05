%define api.pure
%define parse.trace
%define parse.error verbose

%code top{
#include <stdio.h>
#include <string.h>
}

%code requires{
#include "triple_proc.h"
typedef void * yyscan_t;
}

%code {
char *concat_s(char *s1, char *s2);
int clean_triple(NTTriple *ntriple);
int yyerror(yyscan_t scanner, const char *msg);
int yylex(YYSTYPE* yylvalp, yyscan_t scanner);
ProcDataScan *yyget_extra(yyscan_t scanner);
}

%parse-param {yyscan_t scanner}
%lex-param {yyscan_t scanner}

%union{
    char *string;
    NTRes ntRes;
}

%token <string> IRIREF;
%token <string> STRING_LITERAL_QUOTE;
%token <string> BLANK_NODE_LABEL;
%token <string> LITERAL_SUFFIX;
%token DOT
%token EOL;

%type <ntRes> subject predicate object
%type <string> literal;

%%

ntfile:
      ntfile triple EOL
      | ntfile triple
      |
      ;

triple:
      subject predicate object DOT {
        NTTriple ntriple = {$1, $2, $3};
        ProcDataScan *proc = yyget_extra(scanner);
        proc->proc_fun(&ntriple); 
        clean_triple(&ntriple);}
      ;

subject:
       BLANK_NODE_LABEL { NTRes res = {$1, BLANK_NODE}; $$ = res;}
       | IRIREF  { NTRes res = {$1, IRI}; $$ = res; }
       ;

predicate:
       IRIREF { NTRes res = {$1, IRI}; $$ = res; }
       ;

object:
      literal  { NTRes res = {$1, LITERAL}; $$ = res;}
      | BLANK_NODE_LABEL { NTRes res = {$1, BLANK_NODE}; $$ = res;}
      | IRIREF { NTRes res = {$1, IRI}; $$ = res; }
      ;

literal:
       STRING_LITERAL_QUOTE { $$ = $1; }
       | STRING_LITERAL_QUOTE LITERAL_SUFFIX { $$ = concat_s($1, $2);}
       ;


%%

char *concat_s(char *s1, char *s2){

    const size_t sz_1 = strlen(s1);
    const size_t sz_2 = strlen(s2);

    char *result = malloc(sz_1 + sz_2 + 1);
    memcpy(result, s1, sz_1);
    memcpy(result + sz_1, s2, sz_2+1);

    free(s1);
    free(s2);

    return result;
}

int clean_triple(NTTriple *ntriple){
    free(ntriple->subject.data);
    free(ntriple->predicate.data);
    free(ntriple->object.data);
    return 0;
}


