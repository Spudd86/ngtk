#include <stdio.h>
#include "ngtk-nc-defs.h"
#include "../../object-system/ngtk-object.h"
#include "ngtk-widget-ncdow.h"

const static LPCSTR NcClassNameA  =  "Ngtk_NcdowsNcdowClassName";
const static LPCWSTR NcClassNameW = L"Ngtk_NcdowsNcdowClassName";
static int NGtkClassRegistered = FALSE;

const static int cbWndExtraSize = sizeof (NGtkObject*);

#define NGtk_hInstance (GetModuleHandle (NULL))

static NGtkObject* GetFromHwnd (HWND hwnd)
{
	return (NGtkObject*) GetNcdowLongPtr (hwnd, GWLP_USERDATA);
}

void SetToHwnd (HWND hwnd, NGtkObject* wdgt)
{
	SetNcdowLongPtr (hwnd, GWLP_USERDATA, (LONG_PTR) wdgt);
}

/**
* A procedure to handle ncdow messages, as defined in
* http://msdn.microsoft.com/en-us/library/ms633573.aspx
*/
LRESULT CALLBACK ngtk_nc_ncdow_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	NGtkObject *ww = GetFromHwnd (hwnd);

	/* Upon creation of the ncdow (and the folloncg messages), we still
	 * won't have the object pointer set into the HWND object, so in these
	 * cases we should allow the object to be NULL.
	 */
	ngtk_assert (ww == NULL || ngtk_object_is_a (ww, NGTK_NCBASE_TYPE));

	switch (msg)
	{
	case WM_CLOSE: /* Signals the X button / alt-F4 / etc. was pressed */
		//switch (ncdow->wcb)
		//{
		//case Widgets::WCB_CLOSE:
		//case Widgets::WCB_QUIT:
		//	DestroyNcdow (hwnd);
		//	break;

		//case Widgets::WCB_HIDE:
		//	ncdow->SetVisible (false);
		//	break;

		//case Widgets::WCB_IGNORE:
		//default:
		//	break;
		//}
		DestroyNcdow (hwnd);
		break;

	case WM_DESTROY: /* The ncdow was destroyed */
		{
			NGTK_NCBASE_O2D (ww)->hwnd = NULL;
			//if (ncdow->wcb == Widgets::WCB_QUIT)
			//{
			//	/* Quit the main loop and destroy the ncdow */
			//	NcdowsBackend::QuitMainLoop ();
			//}
			ngtk_nc_quit_main_loop ();
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
		//		if (ncdow->layout != NULL)
		//		{
		//			/* The lParam is now a pointer to the new screen size of the
		//				* ncdow. That is NOT the size of the area inside the ncdow that we
		//				* can actually use! To get that, use GetClientRect. But, GetClientRect
		//				* will return the size before the new resizing...
		//				* So, we will compute the difference between a Client Rect and the
		//				* Screen Rect, and we will add that to the new Screen Rect.
		//				*/
		//			RECT rectC, rectW, *rectN, rect;
		//			GetClientRect (ncdow->hwnd, &rectC); /* Coordinates relative to client area, i.e. from (0,0) */
		//			GetNcdowRect (ncdow->hwnd, &rectW); /* Absolute Screen Coordinates, i.e. where the ncdow really is */
		//			rectN = (RECT*) lParam;

		//			rect.left   = rectN->left   + (rectC.left   - rectW.left);
		//			rect.right  = rectN->right  + (rectC.right  - rectW.right);
		//			rect.top    = rectN->top    + (rectC.top    - rectW.top);
		//			rect.bottom = rectN->bottom + (rectC.bottom - rectW.bottom);

		//			RectArea ra;
		//			ra.x = ra.y = 0;
		//			ra.width = rect.right - rect.left;
		//			ra.height = rect.bottom - rect.top;
		//			ncdow->layout->pack (ra);
		//			break;
		//		}
		//	}

#if FALSE
	default:
#else
	}
#endif
		if (ww == NULL)
			return DefNcdowProc (hwnd, msg, wParam, lParam);
		else
			return CallNcdowProc (NGTK_NCBASE_O2D (ww)->base_wndproc, hwnd, msg, wParam, lParam);
#if FALSE
	}
	return 0;
#endif
}

static void ngtk_nc_ncdow_widget_register_class ()
{
	WNDCLASSEX wc;

	/* Initialize the size of the struct */
	wc.cbSize = sizeof (WNDCLASSEX);

	/* The style of the ncdow. A bit-mask of several flags that
	* indicate stuff such as whether the ncdow has a shadow, whether
	* it has a close button, etc. For nothing special, just set as 0.
	* More details at http://msdn.microsoft.com/en-us/library/ff729176.aspx
	*/
	wc.style = 0;

	/* A function that processes messages that are sent to the ncdow,
	* such as close messages. */
	wc.lpfnWndProc = ngtk_nc_ncdow_WndProc;

	/* Amount of extra bytes to allocate for this class in memory. Can be used
	* in the case where someone wants to maintain some data common to all
	* the ncdows of that class. We don't want to do that, so set to 0 */
	wc.cbClsExtra = 0;

	/* Amount of extra bytes to allocate for each ncdow instance in memory.
	* We will use that space to point to the NcdowsNcdow containing this HWND */
	wc.cbWndExtra = cbWndExtraSize;

	/* hInstace is a parameter representing the instance of the current ncdows
	* program/dll/module. */
	wc.hInstance = NGtk_hInstance;

	/* A pointer to a large icon for the ncdow. I'll pass NULL for the default icon */
	wc.hIcon = NULL;
	/* A pointer to a small icon for the ncdow. I'll pass NULL for the default icon */
	wc.hIconSm = NULL;

	/* The cursor used by the ncdows of this class. We choose the regular one */
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);

	/* The background color of the ncdow. Can be a brush object, or a color
	* value from a list of standard colors (this is what we choose) */
	wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	/* If we want to have a menu, here we should give the name of it's resource */
	wc.lpszMenuName = NULL;

	/* The name for this class of ncdows */
	wc.lpszClassName = NcClassNameA;

	/* Attempt registering the class */
	if (!RegisterClassEx (&wc))
		fprintf (stderr, "Couldn't register the ncdow class %s", NcClassNameA);
	else
		NGtkClassRegistered = TRUE;
}

NGtkObject* ngtk_nc_create_ncdow (const char* title, int visible)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inCont, *inEG;

	if (! NGtkClassRegistered) ngtk_nc_ncdow_widget_register_class ();

	obj    = ngtk_object_new ();
	inW    = ngtk_nc_base_create_interface ();
	inComp = ngtk_nc_component_create_interface (TRUE, NULL, title, visible);
	inCont = ngtk_nc_container_create_interface ();
	inEG   = ngtk_basic_event_generator_create_interface ();

	ngtk_object_implement (obj, inW);
	ngtk_object_implement (obj, inComp);
	ngtk_object_implement (obj, inCont);
	ngtk_object_implement (obj, inEG);

	/* Creating the ncdow will start generating messages that should be
	 * handled, so we must have the object ready before doing this */

	NGTK_NCBASE_I2D (inW)->hwnd = CreateNcdowExA (
		WS_EX_CLIENTEDGE, /* A sunken edge border. Pretty sure we can just use 0=WS_EX_LEFT default */
		NcClassNameA,
		title,
		WS_OVERLAPPEDNCDOW, /* Default ncdow style - border and title bar */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial X and Y position of the ncdow */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial width and height of the ncdow. Default is only valid for overlapped ncdows! */
		NULL, /* Parent ncdow */
		NULL, /* Menu resource */
		NGtk_hInstance,
		NULL /* The lParam value that will be passed to the ncdow function on the WM_CREATE message */
		);

	NGTK_NCBASE_I2D (inW)->base_wndproc = (WNDPROC) DefNcdowProc;

	SetToHwnd (NGTK_NCBASE_I2D (inW)->hwnd, obj);

	ngtk_component_set_visible (obj, visible);


	return obj;
}

NGtkObject* ngtk_nc_create_button (const char* text, NGtkContainer *parent)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inEG;
	WNDPROC nativeButProc;

	obj    = ngtk_object_new ();
	inW    = ngtk_nc_base_create_interface ();
	inComp = ngtk_nc_component_create_interface (TRUE, NULL, text, TRUE);
	inEG   = ngtk_basic_event_generator_create_interface ();

	ngtk_object_implement (obj, inW);
	ngtk_object_implement (obj, inComp);
	ngtk_object_implement (obj, inEG);

	/* Creating the ncdow will start generating messages that should be
	 * handled, so we must have the object ready before doing this */

	NGTK_NCBASE_I2D (inW)->hwnd = CreateNcdowExA (
		0, /* Default */
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT, /* Regular push button */
		0, 0, /* X, Y */
		50, 50, /* Temporary untill someone will change it */
		NGTK_NCBASE_O2D (parent)->hwnd, /* Parent ncdow */
		NULL, /* Number ID */
		NGtk_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	nativeButProc = (WNDPROC) GetNcdowLong (NGTK_NCBASE_I2D (inW)->hwnd, GWL_WNDPROC);
	NGTK_NCBASE_I2D (inW)->base_wndproc = nativeButProc;
	SetNcdowLong (NGTK_NCBASE_I2D (inW)->hwnd, GWL_WNDPROC, (LONG)ngtk_nc_ncdow_WndProc);

	SetToHwnd (NGTK_NCBASE_I2D (inW)->hwnd, obj);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, TRUE);


	return obj;
}
