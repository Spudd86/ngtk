#ifndef __Ngtk_Backends_Windows_WindowsWidget_h__
#define __Ngtk_Backends_Windows_WindowsWidget_h__

#include <Windows.h>
#include "../base/AbstractWidget.h"
#include "WindowsWindow.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      class WindowsWidget : public Base::AbstractWidget
      {
      public:
        static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static void* GetFromHwnd (HWND hwnd);
        static void SetToHwnd (HWND hwnd, void* ww);
        const static int cbWndExtraSize = sizeof (void*);

      private:
        void RealDestroyChildren (bool ChildHwndsAreValid);

      protected:
        HWND hwnd;

      public:
        WindowsWidget (std::string text, AbstractWidget *parent);
        virtual ~WindowsWidget ();

        friend class WindowsWindow;
      };

    }
  }
}

#endif

