#ifndef __Ngtk_Backends_Windows_WindowsWidget_h__
#define __Ngtk_Backends_Windows_WindowsWidget_h__

#include <Windows.h>
#include "../base/AbstractWidget.h"
#include "WindowsWindow.h"
#include "WindowsComponent.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Windows
		{
			class WindowsWidget
			{
			public:
				static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			};
		}
	}
}

#endif

