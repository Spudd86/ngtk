#include "ngtk-basic-component.h"

NGtkInterface* ngtk_basic_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible)
{
	NGtkInterface *in = ngtk_interface_new (NGTK_COMPONENT_TYPE);
	NGtkBasicComponentD *bcd;

	bcd = ngtk_new (NGtkBasicComponentD);
	bcd->enabled = enabled;
	bcd->parent = parent;
	bcd->text = text;
	bcd->visible = visible;

	in->d[0] = bcd;
	in->d_free[0] = ngtk_basic_component_d_free;

	in->f = ngtk_new (NGtkComponentF);
	NGTK_COMPONENT_I2F (in) -> get_enabled = ngtk_basic_component_get_enabled;
	NGTK_COMPONENT_I2F (in) -> get_parent  = ngtk_basic_component_get_parent;
	NGTK_COMPONENT_I2F (in) -> get_text    = ngtk_basic_component_get_text;
	NGTK_COMPONENT_I2F (in) -> get_visible = ngtk_basic_component_get_visible;
	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_basic_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_basic_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_basic_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_basic_component_set_visible;
	in->f_free = ngtk_free;

	return in;
}

void ngtk_basic_component_d_free (void *d)
{
	NGtkBasicComponentD *d_real = (NGtkBasicComponentD*) d;
	ngtk_free (d_real);
}
NGtkContainer* ngtk_basic_component_get_parent  (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> parent;
}

int ngtk_basic_component_get_enabled (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> enabled;
}
void ngtk_basic_component_set_enabled (NGtkComponent *self, int enabled)
{
	NGTK_BASIC_COMPONENT_O2D (self) -> enabled = enabled;
}

int ngtk_basic_component_get_visible (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> visible;
}

void ngtk_basic_component_set_visible (NGtkComponent *self, int visible)
{
	NGTK_BASIC_COMPONENT_O2D (self) -> visible = visible;
}

const char* ngtk_basic_component_get_text (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> text;
}

void ngtk_basic_component_set_text (NGtkComponent *self, const char *text)
{
	NGTK_BASIC_COMPONENT_O2D (self) -> text = text;
}

void ngtk_basic_component_redraw (NGtkComponent *self)
{
	/* Let's break some abstraction */
	if (ngtk_object_is_a (self, NGTK_CONTAINER_TYPE))
	{
		NGtkListNode *iter;
		ngtk_list_foreach (iter, ngtk_container_get_children (self))
		{
			ngtk_component_redraw ((NGtkComponent*) iter->data);
		}
	}
}
