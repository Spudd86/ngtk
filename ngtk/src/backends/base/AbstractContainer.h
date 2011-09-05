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
      
      class NGTK_DLL_CLASS AbstractContainer
      {
      protected:
        std::list<AbstractComponent*> children;

      public:
        AbstractContainer ();
        virtual ~AbstractContainer ();

        virtual void SetChildRect (AbstractComponent *comp, int x, int y, int width, int height) = 0;
      };

    }
  }
}

#endif

