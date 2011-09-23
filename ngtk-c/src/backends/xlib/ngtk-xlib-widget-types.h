#ifndef __NGtk_xlib_widget_types__
#define __NGtk_xlib_widget_types__

#include "../../widgets/ngtk-widget-types.h"
#include "../../object-system/ngtk-object.h"

enum {
	NGTK_XLIBBASE_TYPE = NGTK_BACKEND_BASE_TYPE
};

typedef NGtkInterface                NGtkXlibBaseI;
typedef NGtkObject                   NGtkXlibBase;

#endif
