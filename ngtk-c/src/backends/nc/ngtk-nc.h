#ifndef __NGtk_nc_h__
#define __NGtk_nc_h__

#include "ngtk-nc-defs.h"

#include "ngtk-nc-widget-types.h"

#include "ngtk-nc-base.h"
#include "ngtk-nc-component.h"
#include "ngtk-nc-container.h"
#include "ngtk-nc-event-generator.h"


#define ngtk_init                ngtk_nc_init
#define ngtk_start_main_loop     ngtk_nc_start_main_loop
#define ngtk_quit_main_loop      ngtk_nc_quit_main_loop
#define ngtk_quit                ngtk_nc_quit

#define ngtk_create_root_window  ngtk_nc_create_root_window
#define ngtk_create_button       ngtk_nc_create_button
#define ngtk_create_label        ngtk_nc_create_label
#define ngtk_create_text_entry   ngtk_nc_create_text_entry

#endif
