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
        WindowsWidget *widget = (WindowsWidget *) GetFromHwnd (hwnd);

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
            widget->hwnd = NULL;
            break;

          default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
          }
        return 0;
      }

      /**
       * Each HWND (of a window) holds a pointer to it's WindowsWindow
       */
      void*
      WindowsWidget::GetFromHwnd (HWND hwnd)
      {
        return (WindowsWidget*) GetWindowLongPtr (hwnd, GWLP_USERDATA);
      }

      void
      WindowsWidget::SetToHwnd (HWND hwnd, void* ww)
      {
        SetWindowLongPtr (hwnd, GWLP_USERDATA, (LONG_PTR) ww);
      }

      WindowsWidget::WindowsWidget (std::string text, AbstractWidget *parent)
      : AbstractWidget (text, parent)
      {
        this->hwnd = NULL;
      }

      void
      WindowsWidget::RealDestroyChildren (bool ChildHwndsAreValid)
      {
        for (std::list<AbstractWidget*>::iterator iter = children.begin (); iter != children.end (); iter++)
          {
            WindowsWidget *child = (WindowsWidget*) * iter;
            if (ChildHwndsAreValid && child->hwnd != NULL)
              DestroyWindow (child->hwnd);
            child->RealDestroyChildren (ChildHwndsAreValid);
            delete child;
          }
        children.clear ();
      }

      WindowsWidget::~WindowsWidget ()
      {
        RealDestroyChildren ((this->hwnd == NULL) ? false : true);
      }
    }
  }
}
