#include "nt_parser.hpp"
extern "C" {
#include "parser.tab.h"
#include "scanner.h"
#include "triple_proc.h"
}

#include <iostream>

NTParser::NTParser(std::istream *is, proc_fun_t fun, void *data)
    : fun(fun), is(is), data(data) {}
NTParser::NTParser(std::istream *is, proc_fun_t fun)
    : NTParser(is, fun, nullptr) {}

void NTParser::parse() {
  yyscan_t scanner;
  ProcDataScan proc;
  proc.proc_fun = fun;
  proc.is = reinterpret_cast<void *>(is);
  proc.data = data;

  int err;
  err = yylex_init_extra(&proc, &scanner);
  if (err) {
    printf("There was an error while initializing scanner %d %d\n", err, errno);
    return;
  }
  yyset_in(nullptr, scanner);

  yyparse(scanner);
  yylex_destroy(scanner);
}