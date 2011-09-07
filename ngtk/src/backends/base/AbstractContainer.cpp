#include "AbstractContainer.h"
#include "AbstractComponent.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Base
		{
			AbstractContainer::AbstractContainer ()
			{
			}

			AbstractContainer::~AbstractContainer ()
			{
				for (std::list<Base::AbstractComponent*>::iterator iter = children.begin (); iter != children.end (); iter++)
				{
					AbstractComponent *child = *iter;
					delete child;
				}
				children.clear ();
			}

			void AbstractContainer::RegisterChild (AbstractComponent* child)
			{
				this->children.push_back (child);
			}

			void AbstractContainer::AddResizeEventListener (ResizeEventListener ListenFunc, void *Data, DataFreeFunc FreeFunc)
			{
				ResizeEventListenerInfo inf (ListenFunc, Data, FreeFunc);
				this->ResizeListeners.push_back (inf);
			}

			void AbstractContainer::CallOnResize (int newWidth, int newHeight)
			{
				std::list<ResizeEventListenerInfo>::iterator iter;
				for (iter = this->ResizeListeners.begin (); iter != this->ResizeListeners.end (); iter++)
					iter->ListenFunc (*this, newWidth, newHeight, iter->Data);
			}

			void AbstractContainer::ClearResizeEventListeners ()
			{
				std::list<ResizeEventListenerInfo>::iterator iter;
				for (iter = this->ResizeListeners.begin (); iter != this->ResizeListeners.end (); iter++)
					if (iter->FreeFunc && iter->Data)
						iter->FreeFunc (iter->Data);

				this->ResizeListeners.clear ();
			}
		}
	}
}

