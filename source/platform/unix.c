#ifndef _WIN32
#include "utils.h"
#include <sys/stat.h>

bool createDirectory(char* path)
{
  return mkdir(path, 0777) == 0;
}
#endif