#ifndef __NGtk_xlib_container__
#define __NGtk_xlib_container__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_xlib_container_create_interface ();

void     ngtk_xlib_container_add_child     (NGtkContainer *self, NGtkComponent* child);
#define  ngtk_xlib_container_get_children  ngtk_basic_container_get_children
void     ngtk_xlib_container_remove_child  (NGtkContainer *self, NGtkComponent* child);
void     ngtk_xlib_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

#endif
