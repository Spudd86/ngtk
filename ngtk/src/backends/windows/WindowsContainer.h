#ifndef __Ngtk_Backends_Windows_WindowsContainer_h__
#define __Ngtk_Backends_Windows_WindowsContainer_h__

#include <Windows.h>
#include "../base/AbstractContainer.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {

      class WindowsComponent;

      class WindowsContainer : public Base::AbstractContainer
      {
      public:
        WindowsContainer ();
        virtual ~WindowsContainer ();

        virtual void SetChildRect (Base::AbstractComponent *comp, int x, int y, int width, int height);
      };


    }
  }
}

#endif

