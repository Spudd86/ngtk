#include "ngtk-nc-base.h"
#include "ngtk-nc-component.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_nc_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (enabled, parent, text, visible);
	NGtkNcComponentD *ncd;

	in->d[0] = ncd = ngtk_new (NGtkNcComponentD);
	in->d_free[0] = ngtk_free;
	
	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_nc_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_nc_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_nc_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_nc_component_set_visible;

	return in;
}

void ngtk_nc_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	ngtk_nc_component_redraw (self);
}

void ngtk_nc_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);
	ngtk_basic_component_set_visible (self, visible);
	ngtk_nc_component_redraw (self);

	/* Clear the widget if it wasn't visible */
	if (old_val && ! visible)
	{
		/* TODO: The behaviour is underfined for widgets that overlap one
		 * another. This is not a bug, but it should be documented. Since
		 * redrawing an invisible area clears the area below it, then
		 * redrawing an invisible widget will lead to unexpected results.
		 * maybe fix this by asking the parent to redraw... */
		wclear (ngtk_nc_base_get_window (self));
	}
	else if (! old_val && visible)
	{
		ngtk_component_redraw (self);
	}
}

void ngtk_nc_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	ngtk_nc_component_redraw (self);
}

void ngtk_nc_component_redraw (NGtkComponent *self)
{
	const NGtkBasicComponentD *dReal = NGTK_BASIC_COMPONENT_O2D (self);
	WINDOW *wnd = ngtk_nc_base_get_window (self);
	
	if (wnd == NULL || ! dReal->visible)
		return;

	box (wnd, 0, 0);

	if (! dReal->enabled)
		wattron (wnd, A_DIM);

	/* Don't use the printw version, since then you need "%s" to avoid
	 * format string attacks, which is just an annoyance */
	mvwaddstr (wnd, 1, 1, dReal->text);

	if (! dReal->enabled)
		wattroff (wnd, A_DIM);

	refresh ();
	wrefresh (wnd);

	/* Base will redraw the children if needed */
	ngtk_basic_component_redraw (self);
}
