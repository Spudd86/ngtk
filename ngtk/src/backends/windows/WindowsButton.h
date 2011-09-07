#ifndef __Ngtk_Backends_Windows_WindowsButton_h__
#define __Ngtk_Backends_Windows_WindowsButton_h__

#include <Windows.h>
#include <string>

#include "../base/AbstractWidget.h"
#include "../base/AbstractWindow.h"
#include "../../utils/DynamicLibrary.h"
#include "WindowsContainer.h"
#include "WindowsComponent.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Windows
		{
			class WindowsButton : public Base::AbstractWidget, public WindowsComponent
			{
			protected:
				static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

			public:
				NGTK_DLL_FUNC WindowsButton (WindowsContainer *parent, std::string text);
				NGTK_DLL_FUNC ~WindowsButton ();

				void
					WindowsButton::SetText (std::string text);
				virtual bool NaturalMouseClickHandler (Events::MouseEvent &evnt, bool external);
				virtual void SetEnabled (bool enabled);
			};
		}
	}
}

#endif

