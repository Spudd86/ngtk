#include "ngtk-win-base.h"
#include "ngtk-win-component.h"
#include "../basic/ngtk-basic.h"
#include "ngtk-win-widget-types.h"

NGtkInterface* ngtk_win_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (enabled, parent, text, visible);

	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_win_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_win_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_win_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_win_component_set_visible;

	return in;
}

void ngtk_win_component_set_enabled (NGtkComponent *self, int enabled)
{
	EnableWindow (NGTK_WINBASE_O2D (self)->hwnd, enabled);
	ngtk_basic_component_set_enabled (self, enabled);
}

void ngtk_win_component_set_visible (NGtkComponent *self, int visible)
{
	ShowWindow (NGTK_WINBASE_O2D (self)->hwnd, visible ? SW_NORMAL : SW_HIDE);
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_win_component_set_text (NGtkComponent *self, const char *text)
{
	SetWindowTextA (NGTK_WINBASE_O2D (self)->hwnd, text);
	ngtk_basic_component_set_text (self, text);
}

void ngtk_win_component_redraw (NGtkComponent *self)
{
	ngtk_basic_component_redraw (self);
}
