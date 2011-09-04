#include <string>
#include <list>

#include "../../events/MouseEvent.h"
#include "AbstractWidget.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      AbstractWidget::AbstractWidget (std::string text, AbstractWidget *parent)
      : text (text), parent (parent) { }

      AbstractWidget::~AbstractWidget () { }

      bool
      AbstractWidget::NaturalMouseClickHandler (Events::MouseEvent &evnt, bool external)
      {
        /* Pass all events to external listeners, and do nothing other than that */
        return true;
      }

      void
      AbstractWidget::AddMouseEventListener (MouseEventListener ListenFunc, void *Data, DataFreeFunc FreeFunc)
      {
        MouseEventListenerInfo inf (ListenFunc, Data, FreeFunc);
        this->MouseListeners.push_back (inf);
      }

      void
      AbstractWidget::SendMouseEvent (Events::MouseEvent &evnt)
      {
        std::list<MouseEventListenerInfo>::iterator iter;
        if (NaturalMouseClickHandler (evnt, true))
          for (iter = this->MouseListeners.begin (); iter != this->MouseListeners.end (); iter++)
            iter->ListenFunc (*this, evnt, iter->Data);
      }

      void
      AbstractWidget::ClearMouseEventListeners ()
      {
        std::list<MouseEventListenerInfo>::iterator iter;
        for (iter = this->MouseListeners.begin (); iter != this->MouseListeners.end (); iter++)
          if (iter->FreeFunc && iter->Data)
            iter->FreeFunc (iter->Data);

        this->MouseListeners.clear ();
      }
    }
  }
}
