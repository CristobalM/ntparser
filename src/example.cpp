#include <nt_parser.hpp>
#include <iostream>
#include <fstream>

void processor(NTTriple *ntriple){
    // ntriple->subject, ntriple->predicate, ntriple->object
    // each one has a "char *data" containing the full string of the resource
    // also each resource has a type that can be one of IRI, LITERAL or BLANK_NODE
    // eg
    std::cout << "Resource " << ntriple->subject.data << " has type " << ntriple->subject.type << std::endl;
}

int main(int argc, char **argv){
    std::ifstream ifs(argv[1]);
    NTParser parser(&ifs, processor);
    parser.parse();

}