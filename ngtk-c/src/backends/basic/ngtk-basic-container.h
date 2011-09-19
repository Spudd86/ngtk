#ifndef __NGtk_basic_container__
#define __NGtk_basic_container__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_container_d {
	NGtkComponentList* children;
	NGtkLayout*        layout;
} NGtkBasicContainerD;

#define NGTK_BASIC_CONTAINER_O2D(comp) NGTK_O2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)
#define NGTK_BASIC_CONTAINER_I2D(comp) NGTK_I2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)

NGtkInterface*     ngtk_basic_container_create_interface ();
void               ngtk_basic_container_free_d           (void *d);

NGtkComponentList* ngtk_basic_container_get_children  (NGtkContainer *self);

void               ngtk_basic_container_add_child     (NGtkContainer *self, NGtkComponent* child);
void               ngtk_basic_container_remove_child  (NGtkContainer *self, NGtkComponent* child);

void               ngtk_basic_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

void               ngtk_basic_container_set_layout    (NGtkContainer *self, NGtkLayout *layout);
void               ngtk_basic_container_pack          (NGtkContainer *self);

#endif
