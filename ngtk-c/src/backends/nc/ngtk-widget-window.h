#ifndef __NGtk_nc_widget_ncdow_h__
#define __NGtk_nc_widget_ncdow_h__

#include "ngtk-nc-base.h"
#include "ngtk-nc-container.h"
#include "ngtk-nc-component.h"
#include "../basic/ngtk-basic.h"
#include "ngtk-nc-widget-types.h"

NGtkObject* ngtk_nc_create_ncdow (const char* title, int visible);
NGtkObject* ngtk_nc_create_button (const char* text, NGtkContainer *parent);
#endif