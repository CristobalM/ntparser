#include "nt_parser.hpp"

#include <fstream>
#include <iostream>

struct Ofstreams {
  std::ofstream &iris, &blanks, &literals;
  Ofstreams(std::ofstream &iris, std::ofstream &blanks, std::ofstream &literals)
      : iris(iris), blanks(blanks), literals(literals) {}
};

void cond_write(NTRes &res, Ofstreams &o) {
  char *data = res.data;
  switch (res.type) {
  case IRI:
    o.iris << data << "\n";
    break;
  case LITERAL:
    o.literals << data << "\n";
    break;
  case BLANK_NODE:
    o.blanks << data << "\n";
    break;
  }
}

void processor(NTTriple *triple, void *data) {
  auto &ofstreams = *reinterpret_cast<Ofstreams *>(data);
  cond_write(triple->subject, ofstreams);
  cond_write(triple->predicate, ofstreams);
  cond_write(triple->object, ofstreams);
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

  std::ofstream iris(argv[2], std::ios::out);
  std::ofstream literals(argv[3], std::ios::out);
  std::ofstream blanks(argv[4], std::ios::out);

  Ofstreams ofstreams(iris, blanks, literals);
  NTParser parser(&nt, processor, &ofstreams);

  parser.parse();
  return 0;
}