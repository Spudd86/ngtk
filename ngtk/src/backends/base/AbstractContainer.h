#ifndef __Ngtk_Backends_Base_AbstractContainer_h__
#define __Ngtk_Backends_Base_AbstractContainer_h__

#include <list>

#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {
      class AbstractComponent;
	  class AbstractContainer;
      
      typedef void (*DataFreeFunc) (void* data);
	  typedef void (*ResizeEventListener) (const AbstractContainer &cont, int newWidth, int newHeight, void* data);

      /**
       * A struct containing all the information regarding a resize listener,
       * which is made of the ResizeEventListener function, a pointer to
       * custom data to pass to the listener, and a pointer to a function
       * to be applied on the data once the the window is destroyed. */
      struct ResizeEventListenerInfo
      {
        const ResizeEventListener ListenFunc;
        void* Data;
        const DataFreeFunc FreeFunc;

        ResizeEventListenerInfo (
                                const ResizeEventListener ListenFunc,
                                void* Data,
                                const DataFreeFunc FreeFunc
                                ) : ListenFunc (ListenFunc), Data (Data), FreeFunc (FreeFunc) { }
      };


      class NGTK_DLL_CLASS AbstractContainer
      {
      protected:
        std::list<AbstractComponent*> children;
        /** The list of all the event listeners */
        std::list <ResizeEventListenerInfo> ResizeListeners;

		void CallOnResize (int newWidth, int newHeight);

      public:
        AbstractContainer ();
        virtual ~AbstractContainer ();

		void RegisterChild (AbstractComponent* child);
        virtual void SetChildRect (AbstractComponent *comp, int x, int y, int width, int height) = 0;

	   /**
         * Register a resize event listener with a specified user data to be
         * passed to it, and also a custom function to free the data once the
         * listener is released from this widget. Note that the FreeFunc can be
         * NULL and then no function would be called.
         */
        void AddResizeEventListener (ResizeEventListener ListenFunc, void *Data, DataFreeFunc FreeFunc);
        /**
         * Detach all the Resize Event Listeners that were added to the widget
         */
        void ClearResizeEventListeners ();

      };

    }
  }
}

#endif

