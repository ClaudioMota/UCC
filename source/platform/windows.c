#ifdef _WIN32
#include "utils.h"
#include <windows.h>

bool createDirectory(char* path)
{
  CreateDirectory(path, nullptr);
}
#endif
