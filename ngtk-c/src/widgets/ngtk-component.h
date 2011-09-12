#ifndef __NGtk_component_h__
#define __NGtk_component_h__

#include "ngtk-widget-types.h"

typedef struct _NGtkComponentF {
	NGtkContainer* (*get_parent)  (NGtkComponent *self);

	int            (*get_enabled) (NGtkComponent *self);
	void           (*set_enabled) (NGtkComponent *self, int enabled);

	int            (*get_visible) (NGtkComponent *self);
	void           (*set_visible) (NGtkComponent *self, int visible);

	const char*    (*get_text)    (NGtkComponent *self);
	void           (*set_text)    (NGtkComponent *self, const char *text);

	void           (*redraw)      (NGtkComponent *self);
} NGtkComponentF;

#define NGTK_COMPONENT_O2F(comp) NGTK_O2F_CAST(comp,NGTK_COMPONENT_TYPE,NGtkComponentF)
#define NGTK_COMPONENT_I2F(comp) NGTK_I2F_CAST(comp,NGTK_COMPONENT_TYPE,NGtkComponentF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkComponentF object */
NGtkContainer* ngtk_component_get_parent  (NGtkComponent *self);

int            ngtk_component_get_enabled (NGtkComponent *self);
void           ngtk_component_set_enabled (NGtkComponent *self, int enabled);

int            ngtk_component_get_visible (NGtkComponent *self);
void           ngtk_component_set_visible (NGtkComponent *self, int visible);

const char*    ngtk_component_get_text    (NGtkComponent *self);
void           ngtk_component_set_text    (NGtkComponent *self, const char *text);

void           ngtk_component_redraw      (NGtkComponent *self);

#endif