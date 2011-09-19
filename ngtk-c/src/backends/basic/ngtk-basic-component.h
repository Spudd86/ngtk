#ifndef __NGtk_basic_component__
#define __NGtk_basic_component__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_component_d {
	NGtkContainer* parent;
	int            enabled;
	int            visible;
	const char*    text;
} NGtkBasicComponentD;

#define NGTK_BASIC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)
#define NGTK_BASIC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)

NGtkInterface* ngtk_basic_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible);
void           ngtk_basic_component_d_free           (void *d);

NGtkContainer* ngtk_basic_component_get_parent  (NGtkComponent *self);

int            ngtk_basic_component_get_enabled (NGtkComponent *self);
void           ngtk_basic_component_set_enabled (NGtkComponent *self, int enabled);

int            ngtk_basic_component_get_visible (NGtkComponent *self);
void           ngtk_basic_component_set_visible (NGtkComponent *self, int visible);

const char*    ngtk_basic_component_get_text    (NGtkComponent *self);
void           ngtk_basic_component_set_text    (NGtkComponent *self, const char *text);

void           ngtk_basic_component_redraw      (NGtkComponent *self);

#endif
