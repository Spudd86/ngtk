#ifndef __Ngtk_Backends_Base_AbstractComponent_h__
#define __Ngtk_Backends_Base_AbstractComponent_h__

#include "../../utils/DynamicLibrary.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Base
		{
			class AbstractContainer;

			class NGTK_DLL_CLASS AbstractComponent
			{
			public:
				AbstractComponent (AbstractContainer *parent);
				virtual ~AbstractComponent ();

			protected:
				AbstractContainer *parent;
			public:
				virtual AbstractContainer* GetParent ();

			protected:
				bool visible;
			public:
				virtual bool GetVisible ();
				virtual void SetVisible (bool visible);

			public:
				virtual void Redraw () = 0;
			};
		}
	}
}

#endif

