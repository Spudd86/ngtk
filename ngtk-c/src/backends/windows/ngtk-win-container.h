#ifndef __NGtk_win_container__
#define __NGtk_win_container__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface*     ngtk_win_container_create_interface ();

void               ngtk_win_container_add_child     (NGtkContainer *self, NGtkComponent* child);
#define            ngtk_win_container_get_children  ngtk_basic_container_get_children
void               ngtk_win_container_remove_child  (NGtkContainer *self, NGtkComponent* child);
void               ngtk_win_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

#endif