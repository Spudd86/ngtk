#ifndef __NGtk_win_widget_types__
#define __NGtk_win_widget_types__

#include "../../widgets/ngtk-widget-types.h"
#include "../../object-system/ngtk-object.h"

enum {
	NGTK_WINBASE_TYPE = NGTK_BACKEND_BASE_TYPE
};

typedef NGtkInterface                NGtkWinBaseI;
typedef NGtkObject                   NGtkWinBase;

#endif