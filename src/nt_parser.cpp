#include "nt_parser.hpp"
extern "C" {
#include "triple_proc.h"
#include "parser.tab.h"
#include "scanner.h"
}

#include <iostream>

NTParser::NTParser(std::istream *is, proc_fun_t fun) : fun(fun), is(is) {}


void NTParser::parse(){
    yyscan_t scanner;
    ProcDataScan proc;
    proc.proc_fun = fun;
    proc.is = reinterpret_cast<void *>(is);


    int err;
    err = yylex_init_extra(&proc, &scanner);
    if(err){
      printf("There was an error while initializing scanner %d %d\n", err, errno);
      return;
    }
    yyset_in(nullptr, scanner);

    yyparse(scanner);
    yylex_destroy(scanner);
}