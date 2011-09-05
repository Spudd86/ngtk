#include "WindowsBackend.h"
#include "WindowsContainer.h"
#include "WindowsComponent.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      WindowsContainer::WindowsContainer () { }

      WindowsContainer::~WindowsContainer () { }

      void
      WindowsContainer::SetChildRect (Base::AbstractComponent *comp, int x, int y, int width, int height)
      {
        bool IsChild = false;
        WindowsComponent *wcmp;
        std::list<Base::AbstractComponent*>::iterator iter;

        for (iter = this->children.begin (); iter != this->children.end (); iter++)
          if (IsChild = (*iter == comp))
            break;

        if (!IsChild)
          WindowsBackend::instance->Error ("Tried to set the size of a component via a container that doesn't contain it!");

        if (wcmp = dynamic_cast<WindowsComponent*> (comp))
          {
            SetWindowPos (wcmp->hwnd, NULL, x, y, width, height, SWP_NOZORDER);
          }
        else
          WindowsBackend::instance->Error ("Encountered a non Windows Component inside a Windows Container!");
      }
    }
  }
}
