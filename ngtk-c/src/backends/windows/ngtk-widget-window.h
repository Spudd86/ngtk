#ifndef __NGtk_win_widget_window_h__
#define __NGtk_win_widget_window_h__

#include "ngtk-win-base.h"
#include "ngtk-win-container.h"
#include "ngtk-win-component.h"
#include "../basic/ngtk-basic.h"
#include "ngtk-win-widget-types.h"

NGtkObject* ngtk_win_create_window (const char* title, int visible);
NGtkObject* ngtk_win_create_button (const char* text, NGtkContainer *parent);
#endif