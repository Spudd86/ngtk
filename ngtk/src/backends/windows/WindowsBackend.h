#ifndef __Ngtk_Backends_Windows_WindowsBackend_h__
#define __Ngtk_Backends_Windows_WindowsBackend_h__

#include <Windows.h>

#include "../base/AbstractBackend.h"
#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      class WindowsBackend : public Base::AbstractBackend
      {
      public:
        static HINSTANCE hinstance;
        static WindowsBackend* instance;

      public:
        NGTK_DLL_FUNC WindowsBackend ();
        NGTK_DLL_FUNC ~WindowsBackend ();

        NGTK_DLL_FUNC void StartMainLoop ();
        void QuitMainLoop ();

        NGTK_DLL_FUNC void Debug (const char* format, ...);
        NGTK_DLL_FUNC void Error (const char* format, ...);
        NGTK_DLL_FUNC void Warn (const char* format, ...);
      };
    }
  }
}

#endif

