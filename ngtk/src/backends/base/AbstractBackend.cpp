#include "AbstractBackend.h"

#include <cstdio>

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      AbstractBackend::AbstractBackend (bool FatalWarnings)
      {
        this->FatalWarnings = FatalWarnings;
        printf ("AbstractBackend: initialized\n");
      }

      AbstractBackend::~AbstractBackend ()
      {
        printf ("AbstractBackend: destroyed\n");
      }
    }
  }
}
