#include "ngtk-win-base.h"
#include "ngtk-win-container.h"
#include "../basic/ngtk-basic.h"
#include "ngtk-win-widget-types.h"

NGtkInterface* ngtk_win_container_create_interface ()
{
	NGtkInterface *in = ngtk_basic_container_create_interface ();

	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_win_container_add_child;
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_win_container_get_children;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_win_container_place_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_win_container_remove_child;

	return in;
}

void ngtk_win_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	HWND p = NGTK_WINBASE_O2D(self)->hwnd;
	HWND c = NGTK_WINBASE_O2D(child)->hwnd;
	SetParent (c,p);
	ngtk_basic_container_add_child (self, child);
}

void ngtk_win_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	SetParent (NGTK_WINBASE_O2D(child)->hwnd, NULL);
	ngtk_basic_container_remove_child (self, child);
}

void ngtk_win_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
	SetWindowPos (NGTK_WINBASE_O2D(child)->hwnd, HWND_TOP, rect->x, rect->y, rect->w, rect->h, SWP_NOZORDER);
	ngtk_basic_container_place_child (self, child, rect);
}
