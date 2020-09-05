#ifndef TRIPLE_PROC_H
#define TRIPLE_PROC_H

#define ISTREAM_C_GOOD 0
#define ISTREAM_C_BAD 1
#define ISTREAM_C_EOF 2

typedef enum { IRI = 0, LITERAL = 1, BLANK_NODE = 2 } RDFType;

typedef struct {
  char *data;
  RDFType type;
} NTRes;

typedef struct {
  NTRes subject;
  NTRes predicate;
  NTRes object;
} NTTriple;

typedef void (*proc_fun_t)(NTTriple *);
typedef void *istream_c;

typedef struct {
  proc_fun_t proc_fun;
  istream_c is;
} ProcDataScan;

void triple_proc(NTTriple *ntriple);
int istream_c_read(istream_c is, char *buf, int size, int *total_read);

#endif
