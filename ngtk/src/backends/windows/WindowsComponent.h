#ifndef __Ngtk_Backends_Windows_WindowsComponent_h__
#define __Ngtk_Backends_Windows_WindowsComponent_h__

#include <Windows.h>
#include "../base/AbstractComponent.h"
#include "WindowsContainer.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Windows
		{

			class WindowsComponent : public Base::AbstractComponent
			{
			public:
				const static int cbWndExtraSize = sizeof (WindowsComponent*);
				static WindowsComponent* GetFromHwnd (HWND hwnd);
				static void SetToHwnd (HWND hwnd, WindowsComponent* ww);

			public:
				WindowsComponent (WindowsContainer *parent);
				virtual ~WindowsComponent ();

			protected:
				HWND hwnd;

			public:
				virtual void SetVisible (bool visible);
				virtual void Redraw ();
				HWND GetHwnd ();

				friend class WindowsContainer;
			};

		}
	}
}

#endif

