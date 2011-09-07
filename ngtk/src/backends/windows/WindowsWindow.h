#ifndef __Ngtk_Backends_Windows_WindowsWindow_h__
#define __Ngtk_Backends_Windows_WindowsWindow_h__

#include <Windows.h>
#include <string>

#include "../base/AbstractWidget.h"
#include "../base/AbstractWindow.h"
#include "../../utils/DynamicLibrary.h"
#include "WindowsContainer.h"
#include "WindowsComponent.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {
      class WindowsWindow : public Base::AbstractWindow, public Base::AbstractWidget, public WindowsComponent, public WindowsContainer
      {
      protected:
        static LPCSTR WinClassNameA;
        static LPCWSTR WinClassNameW;
        static bool NgtkClassRegistered;
        static void NgtkRegisterClass ();

        static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

      public:
        NGTK_DLL_FUNC WindowsWindow (std::string title, Base::WindowCloseBehaviour OnClose);
        NGTK_DLL_FUNC ~WindowsWindow ();

		void NGTK_DLL_FUNC WindowsWindow::GetSize (int *width, int *height);
      };
    }
  }
}

#endif

