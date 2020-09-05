#include "nt_parser.hpp"

#include <fstream>
#include <iostream>


std::ofstream iris, blanks, literals;

void cond_write(NTRes &res) {
  char *data = res.data;
  switch (res.type) {
  case IRI:
    iris << data << "\n";
    break;
  case LITERAL:
    literals << data << "\n";
    break;
  case BLANK_NODE:
    blanks << data << "\n";
    break;
  }
}

void processor(NTTriple *triple) {
  cond_write(triple->subject);
  cond_write(triple->predicate);
  cond_write(triple->object);
}

int main(int argc, char **argv) {
  if (argc != 5) {
    std::cerr << "Arguments needed <nt-file> <output-iris-file> "
                 "<output-literals-file> <output-blanknodes-file>"
              << std::endl;
    return 1;
  }

  std::ifstream nt(argv[1], std::ios::in);

  if (!nt.good()) {
    std::cerr << "Cant open file" << argv[1] << std::endl;
  }

  iris = std::ofstream(argv[2], std::ios::out);
  blanks = std::ofstream(argv[3], std::ios::out);
  literals = std::ofstream(argv[4], std::ios::out);

  NTParser parser(&nt, processor);
  parser.parse();
  return 0;
}