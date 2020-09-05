# NT Parser

This parser processes any .nt file according to the grammar specified in [https://www.w3.org/TR/n-triples/#n-triples-grammar](https://www.w3.org/TR/n-triples/#n-triples-grammar)

## Build

```
mkdir -p build
cd build
cmake ..
make
```

* This will generate the static library libntparser.a
* Also a sample split_nt program that separates IRIS, Blank Nodes and Literals in 3 different files, separated by new lines


## Library usage

```cpp
#include <nt_parser.hpp>
#include <triple_proc.h>
#include <iostream>

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
```
