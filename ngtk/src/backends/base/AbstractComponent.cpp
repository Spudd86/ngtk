#include "AbstractComponent.h"
#include "AbstractContainer.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Base
		{
			AbstractComponent::AbstractComponent (AbstractContainer *parent)
			{
				this->parent = parent;
			}

			AbstractComponent::~AbstractComponent () { }

			AbstractContainer* AbstractComponent::GetParent ()
			{
				return this->parent;
			}

			bool AbstractComponent::GetVisible ()
			{
				return this->visible;
			}

			void AbstractComponent::SetVisible (bool visible)
			{
				bool NeedsRedraw = visible && ! this->visible;
				this->visible = visible;
				if (NeedsRedraw)
				{
					Redraw ();
				}
			}
		}
	}
}
