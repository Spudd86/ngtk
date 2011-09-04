#ifndef __Ngtk_Backends_Windows_WindowsWindow_h__
#define __Ngtk_Backends_Windows_WindowsWindow_h__

#include <Windows.h>
#include <string>

#include "../base/AbstractWindow.h"
#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      class WindowsWindow : public Base::AbstractWindow
      {
      protected:
        static LPCSTR WinClassNameA;
        static LPCWSTR WinClassNameW;
        static bool NgtkClassRegistered;
        static void NgtkRegisterClass ();

        static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

      protected:
        HWND hwnd;

      public:
        NGTK_DLL_FUNC WindowsWindow (std::string title, int rows, int cols, Base::WindowCloseBehaviour OnClose);
        NGTK_DLL_FUNC ~WindowsWindow ();

        NGTK_DLL_FUNC void SetVisible (bool visible);
      };
    }
  }
}

#endif

