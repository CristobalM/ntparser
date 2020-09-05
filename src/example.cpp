#include <fstream>
#include <iostream>
#include <nt_parser.hpp>

void print_info(NTRes &res) {
  std::string type;
  switch (res.type) {
  case IRI:
    type = "IRI";
    break;
  case LITERAL:
    type = "LITERAL";
    break;
  case BLANK_NODE:
    type = "BLANK_NODE";
    break;
  default:
    type = "UNKNOWN";
  }
  std::cout << "Resource " << res.data << " has type " << type << std::endl;
}

int main(int argc, char **argv) {
  std::ifstream ifs(argv[1], std::ios::in);
  NTParser parser(&ifs, [](NTTriple *ntriple, void *) {
    // ntriple->subject, ntriple->predicate, ntriple->object
    // each one has a "char *data" containing the full string of the resource
    // also each resource has a type that can be one of IRI, LITERAL or
    // BLANK_NODE
    print_info(ntriple->subject);
    print_info(ntriple->predicate);
    print_info(ntriple->object);
  });
  parser.parse();
}
