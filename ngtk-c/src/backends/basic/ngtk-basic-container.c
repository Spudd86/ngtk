#include "ngtk-basic-container.h"

NGtkInterface* ngtk_basic_container_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_CONTAINER_TYPE);
	NGtkBasicContainerD *bcd;

	in->d[0] = bcd = ngtk_new (NGtkBasicContainerD);
	bcd->children  = ngtk_list_new ();
	in->d_free[0] = ngtk_free;

	in->f = ngtk_new (NGtkContainerF);
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_basic_container_get_children;
	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_basic_container_add_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_basic_container_remove_child;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_basic_container_place_child;
	in->f_free = ngtk_free;

	return in;
}

NGtkComponentList* ngtk_basic_container_get_children (NGtkContainer *self)
{
	return NGTK_BASIC_CONTAINER_O2D (self) -> children;
}

void ngtk_basic_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_append (NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
}

void ngtk_basic_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_remove (NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
}

void ngtk_basic_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
}
