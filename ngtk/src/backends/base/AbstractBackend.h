#ifndef __Ngtk_Backends_Base_AbstractBackend_h__
#define __Ngtk_Backends_Base_AbstractBackend_h__

#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      class NGTK_DLL_CLASS AbstractBackend
      {
      protected:
        bool FatalWarnings;

      public:
        AbstractBackend (bool FatalWarnings = false);
        ~AbstractBackend ();

        virtual void StartMainLoop () = 0;
        virtual void QuitMainLoop () = 0;

        virtual void Debug (const char* format, ...) = 0;
        virtual void Error (const char* format, ...) = 0;
        virtual void Warn (const char* format, ...) = 0;

      };
    }
  }
}

#endif

