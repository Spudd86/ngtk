#include <Windows.h>
#include <Commctrl.h>
#include <Windowsx.h>

#include "WindowsBackend.h"
#include "WindowsWidget.h"
#include "WindowsButton.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Windows
		{
			LRESULT CALLBACK WindowsButton::WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
			{
				return WindowsWidget::WndProc (hwnd, msg, wParam, lParam);
			}

			NGTK_DLL_FUNC
				WindowsButton::WindowsButton (WindowsContainer *parent, std::string text)
				: Base::AbstractWidget (text, true), WindowsComponent (parent)
			{
				WindowsComponent* p = dynamic_cast<WindowsComponent*> (parent);
				this->hwnd = CreateWindowExA (
					0, /* Default */
					"BUTTON",
					text.c_str (),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT, /* Regular push button */
					0, 0, /* X, Y */
					50, 50, /* Temporary untill someone will change it */
					p == NULL ? NULL : p->GetHwnd (), /* Parent window */
					NULL, /* Number ID */
					WindowsBackend::hinstance, /* Instance */
					NULL /* The lParam passed with WM_CREATE message */
					);

				SetToHwnd (this->hwnd, const_cast<WindowsButton*> (this));
				parent->RegisterChild (this);
			}

			NGTK_DLL_FUNC
				WindowsButton::~WindowsButton () { }

			bool
				WindowsButton::NaturalMouseClickHandler (Events::MouseEvent &evnt, bool external)
			{
				return false;
			}

			void
				WindowsButton::SetEnabled (bool enabled)
			{
				Button_Enable (this->hwnd, enabled);
				AbstractWidget::SetEnabled (enabled);
			}

			void
				WindowsButton::SetText (std::string text)
			{
				SendMessage (this->hwnd, WM_SETTEXT, NULL, (LPARAM) text.c_str ());
			}
		};
	}
}
