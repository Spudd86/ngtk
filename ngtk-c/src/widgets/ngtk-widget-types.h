#ifndef __NGtk_widget_types_h__
#define __NGtk_widget_types_h__

#include "../object-system/ngtk-object.h"

enum {
	NGTK_NONE_TYPE            = 0,
	NGTK_COMPONENT_TYPE       = 1,
	NGTK_CONTAINER_TYPE       = 2,
	NGTK_EVENT_GENERATOR_TYPE = 3,
	NGTK_LAYOUT_TYPE          = 4,

	NGTK_BACKEND_BASE_TYPE    = (NGTK_MAX_INTERFACES / 2)
};

typedef  NGtkInterface  NGtkComponentI;
typedef  NGtkObject     NGtkComponent;

typedef  NGtkInterface  NGtkContainerI;
typedef  NGtkObject     NGtkContainer;

typedef  NGtkInterface  NGtkEventGeneratorI;
typedef  NGtkObject     NGtkEventGenerator;

typedef  NGtkInterface  NGtkLayoutI;
typedef  NGtkObject     NGtkLayout;

#endif
