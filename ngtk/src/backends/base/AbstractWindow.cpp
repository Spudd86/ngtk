#include <string>

#include "AbstractWindow.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      AbstractWindow::AbstractWindow (std::string title, int rows, int cols, WindowCloseBehaviour OnClose)
      : AbstractWidget (title, NULL), rows (rows), cols (cols), OnClose (OnClose) { }

      AbstractWindow::~AbstractWindow () { }

      void
      AbstractWindow::SetVisible (bool visible)
      {
        this->visible = visible;
      }
    }
  }
}
