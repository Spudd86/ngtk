#ifndef __NGtk_nc_widget_types__
#define __NGtk_nc_widget_types__

#include "../../widgets/ngtk-widget-types.h"
#include "../../object-system/ngtk-object.h"

enum {
	NGTK_NCBASE_TYPE = NGTK_BACKEND_BASE_TYPE
};

typedef NGtkInterface                NGtkNcBaseI;
typedef NGtkObject                   NGtkNcBase;

#endif