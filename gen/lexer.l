%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
#include "triple_proc.h"
#define YY_EXTRA_TYPE ProcDataScan *
void yyerror(yyscan_t, char*);

#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) \
do { \
ProcDataScan *proc = yyget_extra(yyscanner); \
int total_read = 0; \
int err = istream_c_read(proc->is, buf, max_size, &total_read); \
result = total_read; \
if(err == ISTREAM_C_EOF) result = 0; \
else if(err == ISTREAM_C_BAD) { \
    printf("Error while reading input\n"); \
    exit(1); \
} \
} while(0)

%}

%option noyywrap
%option yylineno
%option reentrant bison-bridge

ALPH_LETTER [a-zA-Z]
ALPH_NUMERIC_LETTER [a-zA-Z0-9]
HEX [0-9A-Fa-f]

PN_CHAR_2 ([\xC3][\x80-\x96]|[\xC3][\x99-\xB6]|[\xC3][\xB8-\xBF]|[\xC4-\xCB][\x80-\xBF]|[\xCD][\xB0-\xBD]|[\xCD][\xBF]|[\xCE-\xDF][\x80-\xBF])
PN_CHAR_3 ([\xE0][\xA0-\xBF][\x80-\xBF]|[\xE1][\x80-\xBF][\x80-\xBF]|[\xE2][\x80][\x8C-\x8D]|[\xE2][\x81][\xB0-\xBF]|[\xE2][\x82-\x85][\x80-\xBF]|[\xE2][\x86][\x80-\x8F]|[\xE2][\xB0-\xBE][\x80-\xBF]|[\xE2][\xBF][\x80-\xAF]|[\xE3][\x80][\x81-\xBF]|[\xE3][\x81-\xBF][\x80-\xBF]|[\xE4-\xEC][\x80-\xBF][\x80-\xBF]|[\xED][\x80-\x9F][\x80-\xBF]|[\xEF][\xA4-\xB6][\x80-\xBF]|[\xEF][\xB7][\x80-\x8F]|[\xEF][\xB7][\xB0-\xBF]|[\xEF][\xB8-\xBE][\x80-\xBF]|[\xEF][\xBF][\x80-\xBD])
PN_CHAR_4 ([\xF0][\x90-\xBF][\x80-\xBF][\x80-\xBF]|[\xF1-\xF2][\x80-\xBF][\x80-\xBF][\x80-\xBF]|[\xF3][\x80-\xAF][\x80-\xBF][\x80-\xBF])
ECHAR "\\"[tbnrf"'\\]
UCHAR ("\\u"{HEX}{4}|"\\U"{HEX}{8})

PN_CHARS_EXTRA_2  [\xCC][\x80-\xBF]|[\xCD][\x80-\xAF]
PN_CHARS_EXTRA_3 [\xE2][\x80][\xBF]|[\xE2][\x81][\x80]

PN_CHARS_BASE ([a-zA-Z]|{PN_CHAR_2}|{PN_CHAR_3}|{PN_CHAR_4})
PN_CHARS_U ({PN_CHARS_BASE}|"_"|":")
PN_CHARS ({PN_CHARS_U}|"-"|[0-9]|\xB7|{PN_CHARS_EXTRA_2}|{PN_CHARS_EXTRA_3})

IRI_VALID_LETTER [^\x00-\x20<>"{}|^`\\]

IRI_VALID ({IRI_VALID_LETTER}|{UCHAR})*

STRING_LITERAL_Q ([^\x22\x5C\xA\xD]|{ECHAR}|{UCHAR})

IRI_REF "<"{IRI_VALID}*">"
LANG_TAG "@"{ALPH_LETTER}+("-"{ALPH_NUMERIC_LETTER}+)*

%%

{IRI_REF} { yylval->string = strdup(yytext); return IRIREF;  }
"\""{STRING_LITERAL_Q}*"\"" {yylval->string = strdup(yytext); return STRING_LITERAL_QUOTE;}
"_:"({PN_CHARS_U}|[0-9])(({PN_CHARS}|".")*{PN_CHARS})? {yylval->string = strdup(yytext); return BLANK_NODE_LABEL; }
("^^"{IRI_REF}|{LANG_TAG}) { yylval->string = strdup(yytext); return LITERAL_SUFFIX;}

[\n\r]+ ;
"." { return DOT;}
[ \t]+ ;
'\0' ;
.   yyerror(&yyscanner, "Unknown Character");


%%

void yyerror(yyscan_t scanner, char *msg){
    printf("%s: '%s' in line %d\n", msg, yyget_text(scanner),yyget_lineno(scanner));
}
