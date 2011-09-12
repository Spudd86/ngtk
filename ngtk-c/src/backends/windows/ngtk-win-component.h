#ifndef __NGtk_win_component__
#define __NGtk_win_component__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_win_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible);

#define  ngtk_win_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_win_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_win_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_win_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_win_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_win_component_get_text     ngtk_basic_component_get_text
void     ngtk_win_component_set_text     (NGtkComponent *self, const char *text);

void     ngtk_win_component_redraw       (NGtkComponent *self);

#endif