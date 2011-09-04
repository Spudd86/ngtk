#include <Windows.h>
#include <string>

#include "WindowsBackend.h"
#include "WindowsWidget.h"
#include "WindowsWindow.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {
      LPCSTR WindowsWindow::WinClassNameA = "Ngtk_WindowsWindowClassName";
      LPCWSTR WindowsWindow::WinClassNameW = L"Ngtk_WindowsWindowClassName";
      bool WindowsWindow::NgtkClassRegistered = false;

      void
      WindowsWindow::NgtkRegisterClass ()
      {
        WNDCLASSEX wc;

        /* Initialize the size of the struct */
        wc.cbSize = sizeof (WNDCLASSEX);

        /* The style of the window. A bit-mask of several flags that
         * indicate stuff such as whether the window has a shadow, whether
         * it has a close button, etc. For nothing special, just set as 0.
         * More details at http://msdn.microsoft.com/en-us/library/ff729176.aspx
         */
        wc.style = 0;

        /* A function that processes messages that are sent to the window,
         * such as close messages. */
        wc.lpfnWndProc = WindowsWindow::WndProc;

        /* Amount of extra bytes to allocate for this class in memory. Can be used
         * in the case where someone wants to maintain some data common to all
         * the windows of that class. We don't want to do that, so set to 0 */
        wc.cbClsExtra = 0;

        /* Amount of extra bytes to allocate for each window instance in memory.
         * We will use that space to point to the WindowsWindow containing this HWND */
        wc.cbWndExtra = WindowsWidget::cbWndExtraSize;

        /* hInstace is a parameter representing the instance of the current windows
         * program/dll/module. */
        wc.hInstance = WindowsBackend::hinstance;

        /* A pointer to a large icon for the window. I'll pass NULL for the default icon */
        wc.hIcon = NULL;
        /* A pointer to a small icon for the window. I'll pass NULL for the default icon */
        wc.hIconSm = NULL;

        /* The cursor used by the windows of this class. We choose the regular one */
        wc.hCursor = LoadCursor (NULL, IDC_ARROW);

        /* The background color of the window. Can be a brush object, or a color
         * value from a list of standard colors (this is what we choose) */
        wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

        /* If we want to have a menu, here we should give the name of it's resource */
        wc.lpszMenuName = NULL;

        /* The name for this class of windows */
        wc.lpszClassName = WindowsWindow::WinClassNameA;

        /* Attempt registering the class */
        if (!RegisterClassEx (&wc))
          WindowsBackend::instance->Error ("Couldn't register the window class %s", WindowsWindow::WinClassNameA);
        else
          WindowsWindow::NgtkClassRegistered = true;
      }

      /**
       * A procedure to handle window messages, as defined in
       * http://msdn.microsoft.com/en-us/library/ms633573.aspx
       */
      LRESULT CALLBACK
      WindowsWindow::WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
      {
        WindowsWindow *window = (WindowsWindow *) WindowsWidget::GetFromHwnd (hwnd);

        switch (msg)
          {
          case WM_CLOSE: /* Signals the X button / alt-F4 / etc. was pressed */
            switch (window->OnClose)
              {
              case Base::WCB_CLOSE:
              case Base::WCB_QUIT:
                DestroyWindow (hwnd);
                break;

              case Base::WCB_HIDE:
                window->SetVisible (false);
                break;

              case Base::WCB_IGNORE:
              default:
                break;
              }
            break;

          case WM_DESTROY: /* The window was destroyed */
            {
              window->hwnd = NULL;
              if (window->OnClose == Base::WCB_QUIT)
                {
                  /* Quit the main loop and destroy the window */
                  WindowsBackend::instance->QuitMainLoop ();
                }

              break;

            }

          default:
            return WindowsWidget::WndProc (hwnd, msg, wParam, lParam);
          }
        return 0;
      }

      WindowsWindow::WindowsWindow (std::string title, int rows, int cols, Base::WindowCloseBehaviour OnClose)
      : AbstractWindow (title, rows, cols, OnClose)
      {
        if (!WindowsWindow::NgtkClassRegistered) WindowsWindow::NgtkRegisterClass ();

        this->hwnd = CreateWindowExA (
                                      WS_EX_CLIENTEDGE, /* A sunken edge border. Pretty sure we can just use 0=WS_EX_LEFT default */
                                      WindowsWindow::WinClassNameA,
                                      title.c_str (),
                                      WS_OVERLAPPEDWINDOW, /* Default window style - border and title bar */
                                      CW_USEDEFAULT, CW_USEDEFAULT, /* Initial X and Y position of the window */
                                      CW_USEDEFAULT, CW_USEDEFAULT, /* Initial width and height of the window. Default is only valid for overlapped windows! */
                                      NULL, /* Parent window */
                                      NULL, /* Menu resource */
                                      WindowsBackend::hinstance,
                                      NULL /* The lParam value that will be passed to the window function on the WM_CREATE message */
                                      );

        WindowsWidget::SetToHwnd (this->hwnd, const_cast<WindowsWindow*> (this));
      }

      WindowsWindow::~WindowsWindow () {
 }

      void
      WindowsWindow::SetVisible (bool visible)
      {
        if (visible)
          {
            /* Activate and Show the window in it's original size and position, restore if min/maximized */
            ShowWindow (hwnd, SW_SHOWNORMAL);
            /* Redraw the window, just in case */
            UpdateWindow (hwnd);
          }
        else
          {
            /* Hide the window */
            ShowWindow (this->hwnd, SW_HIDE);
          }

        AbstractWindow::SetVisible (visible);
      }
    }
  }
}
