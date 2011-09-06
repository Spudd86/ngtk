#ifndef __Ngtk_Backends_Base_AbstractWidget_h__
#define __Ngtk_Backends_Base_AbstractWidget_h__

#include <string>
#include <list>

#include "../../events/MouseEvent.h"
#include "../../utils/DynamicLibrary.h"

#include "AbstractComponent.h"
#include "AbstractContainer.h"

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

      class NGTK_DLL_CLASS AbstractWidget
      {
      public:
        AbstractWidget (std::string text, bool enabled);
        virtual ~AbstractWidget ();

        /**
         * A text field for storing the text of the widget. Most widgets do have
         * at least one text field so they can use this one. Note that using
         * this field isn't mandatory.
         */
      protected:
        std::string text;
      public:
        std::string GetText ();
        virtual void SetText (std::string text);

        /**
         * The "enabled" state of the widget. When a widget is disabled, it will
         * not receive any events from the user untill it is re-enabled somehow.
         * Some implementations may choose to reflect this property graphically
         * by changing the looks of the widget.
         */
      protected:
        bool enabled;
      public:
        bool GetEnabled ();
        virtual void SetEnabled (bool enabled);

      protected:
        /** The list of all the event listeners */
        std::list <MouseEventListenerInfo> MouseListeners;
        /**
         * A widget that wants to listen to it's own MouseEvents should
         * override this function. Note that if this function would return
         * FALSE, the event will not be passed on to the other external
         * listeners.
         *
         * The "external" parameter specifies whether this event was called due
         * to a call to "SendMouseEvent" (true) of if it was sent because of
         * internal widget function (false).
         */
        virtual bool NaturalMouseClickHandler (Events::MouseEvent &evnt, bool external);
      public:
        /**
         * Register a mouse event listener with a specified user data to be
         * passed to it, and also a custom function to free the data once the
         * listener is released from this widget. Note that the FreeFunc can be
         * NULL and then no function would be called.
         */
        void AddMouseEventListener (MouseEventListener ListenFunc, void *Data, DataFreeFunc FreeFunc);
        /**
         * Simulate a mouse event. This should be EXACTLY equivalent to a real
         * mouse click - meaning that it will be ignored if the widget isn't
         * enabled, and it will follow the regular restrictions of catching
         * mouse clicks (as defined in NaturalMouseClickHandler)
         */
        void SendMouseEvent (Events::MouseEvent &evnt);
        /**
         * Detach all the Mouse Event Listeners that were added to the widget
         */
        void ClearMouseEventListeners ();
      };

    }
  }
}

#endif

