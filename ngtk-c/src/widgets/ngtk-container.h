#ifndef __NGtk_container_h__
#define __NGtk_container_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"

typedef NGtkList NGtkComponentList;

typedef struct _NGtkContainerF {
	NGtkComponentList* (*get_children)  (NGtkContainer *self);

	void               (*add_child)     (NGtkContainer *self, NGtkComponent* child);
	void               (*remove_child)  (NGtkContainer *self, NGtkComponent* child);

	void               (*place_child)   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);
} NGtkContainerF;

#define NGTK_CONTAINER_O2F(comp) NGTK_O2F_CAST(comp,NGTK_CONTAINER_TYPE,NGtkContainerF)
#define NGTK_CONTAINER_I2F(comp) NGTK_I2F_CAST(comp,NGTK_CONTAINER_TYPE,NGtkContainerF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkContainerF object */

NGtkComponentList* ngtk_container_get_children  (NGtkContainer *self);

void               ngtk_container_add_child     (NGtkContainer *self, NGtkComponent* child);
void               ngtk_container_remove_child  (NGtkContainer *self, NGtkComponent* child);

void               ngtk_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);
#endif