#ifndef NT_PARSER_HPP
#define NT_PARSER_HPP

#include <functional>
#include <istream>

extern "C" {
#include "triple_proc.h"
}

class NTParser {

public:
  typedef void (*proc_fun_t)(NTTriple *, void *);

  NTParser(std::istream *is, proc_fun_t fun, void *data);
  NTParser(std::istream *is, proc_fun_t fun);

  void parse();

private:
  proc_fun_t fun;
  std::istream *is;
  void *data;
};

#endif /* NT_PARSER_HPP */