#include "ngtk-container.h"

NGtkComponentList* ngtk_container_get_children (NGtkContainer *self)
{
	return NGTK_CONTAINER_O2F (self)->get_children (self);
}

void ngtk_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	NGTK_CONTAINER_O2F (self)->add_child (self, child);
}

void ngtk_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	NGTK_CONTAINER_O2F (self)->remove_child (self, child);
}

void ngtk_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
	NGTK_CONTAINER_O2F (self)->place_child (self, child, rect);
}