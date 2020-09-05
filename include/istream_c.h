#ifndef ISTREAM_C_H
#define ISTREAM_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void * istream_c;


int istream_c_read(istream_c is, char *buf, int size, int *total_read);


#ifdef __cplusplus
}
#endif

#endif /* ISTREAM_C_H */