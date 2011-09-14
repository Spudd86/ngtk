#include <stdio.h>
#include "ngtk-win-defs.h"
#include "../../object-system/ngtk-object.h"
#include "ngtk-widget-window.h"

const static LPCSTR WinClassNameA  =  "Ngtk_WindowsWindowClassName";
const static LPCWSTR WinClassNameW = L"Ngtk_WindowsWindowClassName";
static int NGtkClassRegistered = FALSE;

const static int cbWndExtraSize = sizeof (NGtkObject*);

#define NGtk_hInstance (GetModuleHandle (NULL))

static NGtkObject* GetFromHwnd (HWND hwnd)
{
	return (NGtkObject*) GetWindowLongPtr (hwnd, GWLP_USERDATA);
}

void SetToHwnd (HWND hwnd, NGtkObject* wdgt)
{
	SetWindowLongPtr (hwnd, GWLP_USERDATA, (LONG_PTR) wdgt);
}

/**
* A procedure to handle window messages, as defined in
* http://msdn.microsoft.com/en-us/library/ms633573.aspx
*/
LRESULT CALLBACK ngtk_win_window_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	NGtkObject *ww = GetFromHwnd (hwnd);

	/* Upon creation of the window (and the following messages), we still
	 * won't have the object pointer set into the HWND object, so in these
	 * cases we should allow the object to be NULL.
	 */
	ngtk_assert (ww == NULL || ngtk_object_is_a (ww, NGTK_WINBASE_TYPE));

	switch (msg)
	{
	case WM_CLOSE: /* Signals the X button / alt-F4 / etc. was pressed */
		//switch (window->wcb)
		//{
		//case Widgets::WCB_CLOSE:
		//case Widgets::WCB_QUIT:
		//	DestroyWindow (hwnd);
		//	break;

		//case Widgets::WCB_HIDE:
		//	window->SetVisible (false);
		//	break;

		//case Widgets::WCB_IGNORE:
		//default:
		//	break;
		//}
		DestroyWindow (hwnd);
		break;

	case WM_DESTROY: /* The window was destroyed */
		{
			NGTK_WINBASE_O2D (ww)->hwnd = NULL;
			//if (window->wcb == Widgets::WCB_QUIT)
			//{
			//	/* Quit the main loop and destroy the window */
			//	WindowsBackend::QuitMainLoop ();
			//}
			ngtk_win_quit_main_loop ();
			break;

		}

	case WM_LBUTTONDOWN:
		if (ngtk_object_is_a (ww, NGTK_EVENT_GENERATOR_TYPE))
		{
			NGtkMouseEvent m;
			m.met = NGTK_MOUSE_LCLICK;
			ngtk_event_generator_send_click (ww, &m);
		}
		break;

	case WM_RBUTTONDOWN:
		if (ngtk_object_is_a (ww, NGTK_EVENT_GENERATOR_TYPE))
		{
			NGtkMouseEvent m;
			m.met = NGTK_MOUSE_RCLICK;
			ngtk_event_generator_send_click (ww, &m);
		}
		break;

	case WM_MBUTTONDOWN:
		if (ngtk_object_is_a (ww, NGTK_EVENT_GENERATOR_TYPE))
		{
			NGtkMouseEvent m;
			m.met = NGTK_MOUSE_MCLICK;
			ngtk_event_generator_send_click (ww, &m);
		}
		break;

			
		//case WM_SIZING:
		//	{
		//		if (window->layout != NULL)
		//		{
		//			/* The lParam is now a pointer to the new screen size of the
		//				* window. That is NOT the size of the area inside the window that we
		//				* can actually use! To get that, use GetClientRect. But, GetClientRect
		//				* will return the size before the new resizing...
		//				* So, we will compute the difference between a Client Rect and the
		//				* Screen Rect, and we will add that to the new Screen Rect.
		//				*/
		//			RECT rectC, rectW, *rectN, rect;
		//			GetClientRect (window->hwnd, &rectC); /* Coordinates relative to client area, i.e. from (0,0) */
		//			GetWindowRect (window->hwnd, &rectW); /* Absolute Screen Coordinates, i.e. where the window really is */
		//			rectN = (RECT*) lParam;

		//			rect.left   = rectN->left   + (rectC.left   - rectW.left);
		//			rect.right  = rectN->right  + (rectC.right  - rectW.right);
		//			rect.top    = rectN->top    + (rectC.top    - rectW.top);
		//			rect.bottom = rectN->bottom + (rectC.bottom - rectW.bottom);

		//			RectArea ra;
		//			ra.x = ra.y = 0;
		//			ra.width = rect.right - rect.left;
		//			ra.height = rect.bottom - rect.top;
		//			window->layout->pack (ra);
		//			break;
		//		}
		//	}

#if FALSE
	default:
#else
	}
#endif
		if (ww == NULL)
			return DefWindowProc (hwnd, msg, wParam, lParam);
		else
			return CallWindowProc (NGTK_WINBASE_O2D (ww)->base_wndproc, hwnd, msg, wParam, lParam);
#if FALSE
	}
	return 0;
#endif
}

static void ngtk_win_window_widget_register_class ()
{
	WNDCLASSEX wc;

	/* Initialize the size of the struct */
	wc.cbSize = sizeof (WNDCLASSEX);

	/* The style of the window. A bit-mask of several flags that
	* indicate stuff such as whether the window has a shadow, whether
	* it has a close button, etc. For nothing special, just set as 0.
	* More details at http://msdn.microsoft.com/en-us/library/ff729176.aspx
	*/
	wc.style = 0;

	/* A function that processes messages that are sent to the window,
	* such as close messages. */
	wc.lpfnWndProc = ngtk_win_window_WndProc;

	/* Amount of extra bytes to allocate for this class in memory. Can be used
	* in the case where someone wants to maintain some data common to all
	* the windows of that class. We don't want to do that, so set to 0 */
	wc.cbClsExtra = 0;

	/* Amount of extra bytes to allocate for each window instance in memory.
	* We will use that space to point to the WindowsWindow containing this HWND */
	wc.cbWndExtra = cbWndExtraSize;

	/* hInstace is a parameter representing the instance of the current windows
	* program/dll/module. */
	wc.hInstance = NGtk_hInstance;

	/* A pointer to a large icon for the window. I'll pass NULL for the default icon */
	wc.hIcon = NULL;
	/* A pointer to a small icon for the window. I'll pass NULL for the default icon */
	wc.hIconSm = NULL;

	/* The cursor used by the windows of this class. We choose the regular one */
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);

	/* The background color of the window. Can be a brush object, or a color
	* value from a list of standard colors (this is what we choose) */
	wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	/* If we want to have a menu, here we should give the name of it's resource */
	wc.lpszMenuName = NULL;

	/* The name for this class of windows */
	wc.lpszClassName = WinClassNameA;

	/* Attempt registering the class */
	if (!RegisterClassEx (&wc))
		fprintf (stderr, "Couldn't register the window class %s", WinClassNameA);
	else
		NGtkClassRegistered = TRUE;
}

NGtkObject* ngtk_win_create_window (const char* title, int visible)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inCont, *inEG;

	if (! NGtkClassRegistered) ngtk_win_window_widget_register_class ();

	obj    = ngtk_object_new ();
	inW    = ngtk_win_base_create_interface ();
	inComp = ngtk_win_component_create_interface (TRUE, NULL, title, visible);
	inCont = ngtk_win_container_create_interface ();
	inEG   = ngtk_basic_event_generator_create_interface ();

	ngtk_object_implement (obj, inW);
	ngtk_object_implement (obj, inComp);
	ngtk_object_implement (obj, inCont);
	ngtk_object_implement (obj, inEG);

	/* Creating the window will start generating messages that should be
	 * handled, so we must have the object ready before doing this */

	NGTK_WINBASE_I2D (inW)->hwnd = CreateWindowExA (
		WS_EX_CLIENTEDGE, /* A sunken edge border. Pretty sure we can just use 0=WS_EX_LEFT default */
		WinClassNameA,
		title,
		WS_OVERLAPPEDWINDOW, /* Default window style - border and title bar */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial X and Y position of the window */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial width and height of the window. Default is only valid for overlapped windows! */
		NULL, /* Parent window */
		NULL, /* Menu resource */
		NGtk_hInstance,
		NULL /* The lParam value that will be passed to the window function on the WM_CREATE message */
		);

	NGTK_WINBASE_I2D (inW)->base_wndproc = (WNDPROC) DefWindowProc;

	SetToHwnd (NGTK_WINBASE_I2D (inW)->hwnd, obj);

	ngtk_component_set_visible (obj, visible);


	return obj;
}

NGtkObject* ngtk_win_create_button (const char* text, NGtkContainer *parent)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inEG;
	WNDPROC nativeButProc;

	obj    = ngtk_object_new ();
	inW    = ngtk_win_base_create_interface ();
	inComp = ngtk_win_component_create_interface (TRUE, NULL, text, TRUE);
	inEG   = ngtk_basic_event_generator_create_interface ();

	ngtk_object_implement (obj, inW);
	ngtk_object_implement (obj, inComp);
	ngtk_object_implement (obj, inEG);

	/* Creating the window will start generating messages that should be
	 * handled, so we must have the object ready before doing this */

	NGTK_WINBASE_I2D (inW)->hwnd = CreateWindowExA (
		0, /* Default */
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT, /* Regular push button */
		0, 0, /* X, Y */
		50, 50, /* Temporary untill someone will change it */
		NGTK_WINBASE_O2D (parent)->hwnd, /* Parent window */
		NULL, /* Number ID */
		NGtk_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	nativeButProc = (WNDPROC) GetWindowLong (NGTK_WINBASE_I2D (inW)->hwnd, GWL_WNDPROC);
	NGTK_WINBASE_I2D (inW)->base_wndproc = nativeButProc;
	SetWindowLong (NGTK_WINBASE_I2D (inW)->hwnd, GWL_WNDPROC, (LONG)ngtk_win_window_WndProc);

	SetToHwnd (NGTK_WINBASE_I2D (inW)->hwnd, obj);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, TRUE);


	return obj;
}
