#include "../base/AbstractWidget.h"
#include "WindowsWidget.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      /**
       * A procedure to handle window messages, as defined in
       * http://msdn.microsoft.com/en-us/library/ms633573.aspx
       */
      LRESULT CALLBACK
      WindowsWidget::WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
      {
        Base::AbstractWidget *widget = dynamic_cast <Base::AbstractWidget *> (WindowsComponent::GetFromHwnd (hwnd));
        
        /* If this is not really a widget but just some other HWND, "pass on" */
        if (widget == NULL)
          return DefWindowProc (hwnd, msg, wParam, lParam);

        switch (msg)
          {
          case WM_CREATE:
            break;

          case WM_LBUTTONDOWN:
            {
              Ngtk::Events::MouseEvent event (Ngtk::Events::LEFT_CLICK);
              widget->SendMouseEvent (event);
              break;
            }

          case WM_MBUTTONDOWN:
            {
              Ngtk::Events::MouseEvent event (Ngtk::Events::MIDDLE_CLICK);
              widget->SendMouseEvent (event);
              break;
            }

          case WM_RBUTTONDOWN:
            {
              Ngtk::Events::MouseEvent event (Ngtk::Events::RIGHT_CLICK);
              widget->SendMouseEvent (event);
              break;
            }

          case WM_DESTROY:
            delete widget;
            break;

          default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
          }
        return 0;
      }
    }
  }
}
