#include "AbstractContainer.h"
#include "AbstractComponent.h"

namespace Ngtk
{
  namespace Backends
  {
    namespace Base
    {

      AbstractContainer::AbstractContainer () { }

      AbstractContainer::~AbstractContainer ()
      {
        for (std::list<Base::AbstractComponent*>::iterator iter = children.begin (); iter != children.end (); iter++)
          {
            AbstractComponent *child = *iter;
            delete child;
          }
        children.clear ();
      }
    }
  }
}

