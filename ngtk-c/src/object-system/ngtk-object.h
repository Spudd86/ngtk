/*
 * ngtk-object.h
 * (C) Barak Itkin <lightningismyname at gmail dot com>, 2011
 *
 * This file is part of NGtk.
 *
 * NGtk is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * NGtk is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NGtk.  If not, see <http://www.gnu.org/licenses/>.
 */

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

typedef void (*NGtkListener) (void *signal_src, const char *signame, NGtkValue *data);

#define NGTK_ALL_SIGNALS NULL
typedef struct _ngtk_listener_info {
	NGtkListener  func;
	const char   *signame;
} NGtkListenerInfo;

struct _ngtk_object {
	NGtkObjectTypeMask  iBits;
	NGtkInterface      *iImps[NGTK_MAX_INTERFACES];
	void               *d;
	NGtkFreeFunc        d_free;

	/* Amount of references directly to this object */
	int                 direct_ref_count;
	/* Amount of references to the interfaces (not including by the
	 * object itself */
	int                 interfaces_ref_count;

	NGtkList            listeners;
};

struct _ngtk_inteface {
	NGtkObject         *obj;
	NGtkType            iType;
	void               *d[NGTK_MAX_INTERFACE_IMP_LEVELS];
	NGtkFreeFunc        d_free[NGTK_MAX_INTERFACE_IMP_LEVELS];
	void               *f;
	NGtkFreeFunc        f_free;

	/* Amount of references to the interface directly, INCLUDING the
	 * one from the object itself */
	int                 ref_count;

	NGtkList            listeners;
};

NGtkObject*    ngtk_object_new           ();
void           ngtk_object_free          (NGtkObject* obj);
NGtkInterface* ngtk_object_cast          (NGtkObject* obj, NGtkType iType);
int            ngtk_object_is_a          (NGtkObject* obj, NGtkType iType);
void           ngtk_object_ref           (NGtkObject* obj);
void           ngtk_object_unref         (NGtkObject* obj);
void           ngtk_object_connect_to    (NGtkObject *obj, const char* signal, NGtkListener listener);
void           ngtk_object_send_signal   (NGtkObject* obj, const char* signal, NGtkValue *data);

NGtkInterface* ngtk_interface_new        (NGtkType iType);
void           ngtk_interface_free       (NGtkInterface *in);
NGtkInterface* ngtk_interface_cast       (NGtkInterface* in, NGtkType iType);
int            ngtk_interface_is_a       (NGtkInterface* in, NGtkType iType);
NGtkObject*    ngtk_interface_get_object (NGtkInterface *in);
void           ngtk_interface_ref        (NGtkInterface *in);
void           ngtk_interface_unref      (NGtkInterface *in);
void           ngtk_interface_connect_to (NGtkInterface *in, const char* signal, NGtkListener listener);
void           ngtk_interface_send_signal(NGtkInterface *in, const char* signal, NGtkValue *data, int also_object);

void           ngtk_object_implement     (NGtkObject *obj, NGtkInterface *in);

#define NGTK_O2F_CAST(o,bit,type) ((type*)(ngtk_object_cast(o,bit)->f))
#define NGTK_O2D_CAST(o,bit,type,pos) ((type*)(ngtk_object_cast(o,bit)->d[(pos)]))

#define NGTK_I2F_CAST(i,bit,type) ((type*)(ngtk_interface_cast(i,bit)->f))
#define NGTK_I2D_CAST(i,bit,type,pos) ((type*)(ngtk_interface_cast(i,bit)->d[(pos)]))

#endif
