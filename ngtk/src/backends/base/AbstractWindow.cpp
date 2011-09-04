#include <string>

#include "AbstractWindow.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      AbstractWindow::AbstractWindow (std::string title, WindowCloseBehaviour OnClose)
      : AbstractWidget (title, NULL), OnClose (OnClose) { }

      AbstractWindow::~AbstractWindow () { }

      void
      AbstractWindow::SetVisible (bool visible)
      {
        this->visible = visible;
      }
    }
  }
}
