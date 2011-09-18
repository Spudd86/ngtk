#ifndef __NGtk_nc_defs__
#define __NGtk_nc_defs__

#include "../../widgets/ngtk-widgets.h"

void            ngtk_nc_init                ();
void            ngtk_nc_start_main_loop     ();
void            ngtk_nc_quit_main_loop      ();
void            ngtk_nc_quit                ();

NGtkContainer*  ngtk_nc_create_root_window  (const char* title);
NGtkComponent*  ngtk_nc_create_button       (const char* text);
NGtkComponent*  ngtk_nc_create_label        (const char* text);
NGtkComponent*  ngtk_nc_create_text_entry   (const char* text);

/* Utility functions of this backend */
void                ngtk_nc_set_focus_holder (NGtkEventGenerator* eg);
NGtkEventGenerator* ngtk_nc_get_focus_holder ();

#endif
