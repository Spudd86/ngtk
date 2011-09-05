#include <Windows.h>

#include "WindowsComponent.h"
namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      WindowsComponent::WindowsComponent (WindowsContainer *parent)
      : Base::AbstractComponent (parent)
      {
      }

      WindowsComponent::~WindowsComponent ()
      {
        if (this->hwnd) DestroyWindow (this->hwnd);
      }

      WindowsComponent*
      WindowsComponent::GetFromHwnd (HWND hwnd)
      {
        return (WindowsComponent*) GetWindowLongPtr (hwnd, GWLP_USERDATA);
      }

      void
      WindowsComponent::SetToHwnd (HWND hwnd, WindowsComponent* ww)
      {
        SetWindowLongPtr (hwnd, GWLP_USERDATA, (LONG_PTR) ww);
      }

      void
      WindowsComponent::SetVisible (bool visible)
      {
        /* Activate and Show the "Window" in it's original size and position */
        ShowWindow (hwnd, visible ? SW_SHOWNORMAL : SW_HIDE);

        Base::AbstractComponent::SetVisible (visible);
      }

      void
      WindowsComponent::Redraw ()
      {
        UpdateWindow (hwnd);
      }


    }
  }
}

