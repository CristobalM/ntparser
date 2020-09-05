#ifndef NT_PARSER_HPP
#define NT_PARSER_HPP

#include <functional>
#include <istream>

extern "C" {
#include "triple_proc.h"
}

class NTParser {

public:
  typedef void (*proc_fun_t)(NTTriple *); // std::function<void(NTTriple *)>;

  NTParser(std::istream *is, proc_fun_t fun);

  void parse();

private:
  proc_fun_t fun;
  std::istream *is;
};

#endif /* NT_PARSER_HPP */