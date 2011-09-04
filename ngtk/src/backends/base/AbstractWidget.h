#ifndef __Ngtk_Backends_Base_AbstractWidget_h__
#define __Ngtk_Backends_Base_AbstractWidget_h__

#include <string>
#include <list>

#include "../../events/MouseEvent.h"
#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {
      class AbstractWidget;

      typedef void (*DataFreeFunc) (void* data);
      typedef void (*MouseEventListener) (const AbstractWidget &widget, Events::MouseEvent &evnt, void* data);

      /**
       * A struct containing all the information regarding a mouse listener,
       * which is made of the MouseEventListener function, a pointer to
       * custom data to pass to the listener, and a pointer to a function
       * to be applied on the data once the the widget is destroyed. */
      struct MouseEventListenerInfo
      {
        const MouseEventListener ListenFunc;
        void* Data;
        const DataFreeFunc FreeFunc;

        MouseEventListenerInfo (
                                const MouseEventListener ListenFunc,
                                void* Data,
                                const DataFreeFunc FreeFunc
                                ) : ListenFunc (ListenFunc), Data (Data), FreeFunc (FreeFunc) { }
      };

      class AbstractWidget
      {
      protected:
        AbstractWidget *parent;
        std::list<AbstractWidget*> children;

        std::string text;
        std::list <MouseEventListenerInfo> MouseListeners;

        /* A widget that wants to listen to it's own MouseEvents should
         * override this function. Note that if this function would return
         * FALSE, the event will not be passed on to the other listeners.
         *
         * The "external" parameter specifies whether this event was called
         * due to a call to "SendMouseEvent" (true) of if it was sent because
         * of internal widget function (false).
         */
        virtual bool NaturalMouseClickHandler (Events::MouseEvent &evnt, bool external);

      public:
        NGTK_DLL_CLASS AbstractWidget (std::string text, AbstractWidget *parent);
        virtual NGTK_DLL_CLASS ~AbstractWidget ();

        void NGTK_DLL_CLASS AddMouseEventListener (MouseEventListener ListenFunc, void *Data, DataFreeFunc FreeFunc);
        void NGTK_DLL_CLASS SendMouseEvent (Events::MouseEvent &evnt);
        void NGTK_DLL_CLASS ClearMouseEventListeners ();
      };

    }
  }
}

#endif

