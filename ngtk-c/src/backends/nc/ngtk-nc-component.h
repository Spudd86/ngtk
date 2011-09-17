#ifndef __NGtk_nc_component__
#define __NGtk_nc_component__

#include <ncurses.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

typedef struct _ngtk_nc_component_d {
	NGtkRectangle  area;
	
} NGtkNcComponentD;

#define NGTK_NC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)
#define NGTK_NC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)

NGtkInterface* ngtk_nc_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible);

#define  ngtk_nc_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_nc_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_nc_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_nc_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_nc_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_nc_component_get_text     ngtk_basic_component_get_text
void     ngtk_nc_component_set_text     (NGtkComponent *self, const char *text);

void     ngtk_nc_component_redraw       (NGtkComponent *self);

#endif
