#include "parsers/ucc/conversion.h"
#include "parsers/ucc/productions.h"

bool defaultVisit(Production* prod, VisitData* data)
{
  return true;
} 

void setupVisitFunctions()
{
  ucc_visit_defaultFunction = defaultVisit;
}

