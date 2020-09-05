
#include <istream>

extern "C" {
#include "triple_proc.h"
}

int istream_c_read(istream_c is, char *buf, int size, int *total_read) {
  std::istream *real_is = reinterpret_cast<std::istream *>(is);
  if (real_is->fail() || real_is->bad())
    return ISTREAM_C_BAD;
  if (real_is->eof())
    return ISTREAM_C_EOF;
  *total_read = real_is->readsome(buf, size);

  return ISTREAM_C_GOOD;
}