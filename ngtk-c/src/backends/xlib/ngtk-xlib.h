#ifndef __NGtk_xlib_h__
#define __NGtk_xlib_h__

#include "ngtk-xlib-defs.h"

#include "ngtk-xlib-widget-types.h"

#include "ngtk-xlib-base.h"
#include "ngtk-xlib-component.h"
#include "ngtk-xlib-container.h"
#include "ngtk-xlib-event-generator.h"

#include "ngtk-xlib-window.h"

#define ngtk_init                ngtk_xlib_init
#define ngtk_start_main_loop     ngtk_xlib_start_main_loop
#define ngtk_quit_main_loop      ngtk_xlib_quit_main_loop
#define ngtk_quit                ngtk_xlib_quit

#define ngtk_create_root_window  ngtk_xlib_create_root_window
#define ngtk_create_button       ngtk_xlib_create_button
#define ngtk_create_label        ngtk_xlib_create_label
#define ngtk_create_text_entry   ngtk_xlib_create_text_entry

#endif
