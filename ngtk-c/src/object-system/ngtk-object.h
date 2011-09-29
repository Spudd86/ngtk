#ifndef __NGtk_object_h__
#define __NGtk_object_h__

#include "../utils/ngtk-utils.h"

typedef struct _ngtk_object   NGtkObject;
typedef struct _ngtk_inteface NGtkInterface;

typedef unsigned long      NGtkObjectTypeMask;
typedef unsigned short     NGtkType;

#define NGTK_MAX_INTERFACES           (sizeof(NGtkObjectTypeMask) * 8)
#define NGTK_MAX_INTERFACE_IMP_LEVELS 5

#define NGTK_TYPE_NONE 0

struct _ngtk_object {
	NGtkObjectTypeMask  iBits;
	NGtkInterface      *iImps[NGTK_MAX_INTERFACES];
	void               *d;
	NGtkFreeFunc        d_free;
};

struct _ngtk_inteface {
	NGtkObject         *obj;
	NGtkType            iType;
	void               *d[NGTK_MAX_INTERFACE_IMP_LEVELS];
	NGtkFreeFunc        d_free[NGTK_MAX_INTERFACE_IMP_LEVELS];
	void               *f;
	NGtkFreeFunc        f_free;
};

NGtkObject*    ngtk_object_new           ();
void           ngtk_object_free          (NGtkObject* obj);
NGtkInterface* ngtk_object_cast          (NGtkObject* obj, NGtkType iType);
int            ngtk_object_is_a          (NGtkObject* obj, NGtkType iType);

NGtkInterface* ngtk_interface_new        (NGtkType iType);
void           ngtk_interface_free       (NGtkInterface *in);
NGtkInterface* ngtk_interface_cast       (NGtkInterface* in, NGtkType iType);
int            ngtk_interface_is_a       (NGtkInterface* in, NGtkType iType);
NGtkObject*    ngtk_interface_get_object (NGtkInterface *in);

void           ngtk_object_implement     (NGtkObject *obj, NGtkInterface *in);
void           ngtk_object_detach        (NGtkObject *obj, NGtkInterface *in);

#define NGTK_O2F_CAST(o,bit,type) ((type*)(ngtk_object_cast(o,bit)->f))
#define NGTK_O2D_CAST(o,bit,type,pos) ((type*)(ngtk_object_cast(o,bit)->d[(pos)]))

#define NGTK_I2F_CAST(i,bit,type) ((type*)(ngtk_interface_cast(i,bit)->f))
#define NGTK_I2D_CAST(i,bit,type,pos) ((type*)(ngtk_interface_cast(i,bit)->d[(pos)]))

#endif
