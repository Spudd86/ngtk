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

/**
  * @defgroup ObjectSystem The object system
  * @{
  */
typedef struct _ngtk_object   NGtkObject;
typedef struct _ngtk_inteface NGtkInterface;

typedef unsigned long long NGtkObjectTypeMask;
typedef unsigned short     NGtkType;

/** /def The maximal amount of unique interface types that may be
 *       defined using the object system */
#define NGTK_MAX_INTERFACES           (sizeof(NGtkObjectTypeMask) * 8 - 1)
/** /def The maximal amount of implementation levels that may be used to
 *       implement a single interface */
#define NGTK_MAX_INTERFACE_IMP_LEVELS 5

#define NGTK_TYPE_NONE 0

typedef void (*NGtkListener) (void *sigsrc, const char *signame, void *sigdata, void *lisdata);

#define NGTK_ALL_SIGNALS NULL

typedef struct _ngtk_listener_info {
	NGtkListener  func;
	const char   *signame;
	void         *lisdata;
} NGtkListenerInfo;


typedef void (*NGtkDestructor)  (NGtkObject *obj);

struct _ngtk_object {
	/* A bitmask of the implemented interfaces */
	NGtkObjectTypeMask  interface_mask;

	/* An array containing pointers to the implemented interfaces */
	NGtkInterface      *interfaces[NGTK_MAX_INTERFACES];

	/* Amount of references directly to this object */
	int                 direct_ref_count;

	/* Signal listeners */
	NGtkList            listeners;

	/* The object's destructor list. Destructors are called from
	 * first to last */
	NGtkList            destructors;

	/* Warn from multiple attempts to free the object that occure
	 * because of a free-ing recursion */
	int                 double_free_lock;
};


struct _ngtk_inteface {
	/* The object containing this interface */
	NGtkObject         *object;

	/* The type of this interface */
	NGtkType            type;

	/* Custom data for different implementation levels, with the free
	 * functions and destructors */
	void               *imp_data[NGTK_MAX_INTERFACE_IMP_LEVELS];
	NGtkFreeFunc        imp_data_free[NGTK_MAX_INTERFACE_IMP_LEVELS];
	NGtkDestructor      imp_destruct[NGTK_MAX_INTERFACE_IMP_LEVELS];

	void               *functions;
	NGtkFreeFunc        functions_free;

	/* Signal listeners */
	NGtkList            listeners;
};

NGTK_EXPORT NGtkObject*    ngtk_object_new             ();
NGTK_EXPORT void           ngtk_object_free            (NGtkObject *obj);
NGTK_EXPORT NGtkInterface* ngtk_object_cast            (NGtkObject *obj, NGtkType type);
NGTK_EXPORT int            ngtk_object_is_a            (NGtkObject *obj, NGtkType type);
NGTK_EXPORT void           ngtk_object_ref             (NGtkObject *obj);
NGTK_EXPORT void           ngtk_object_unref           (NGtkObject *obj);
NGTK_EXPORT void           ngtk_object_connect_to      (NGtkObject *obj, const char* signal, NGtkListener listener, void *user_data);
NGTK_EXPORT void           ngtk_object_send_signal     (NGtkObject *obj, const char* signal, void *sigdata);
NGTK_EXPORT void           ngtk_object_push_destructor (NGtkObject *obj, NGtkDestructor dest);

NGTK_EXPORT NGtkInterface* ngtk_interface_new          (NGtkObject *obj, NGtkType type);
NGTK_EXPORT NGtkInterface* ngtk_interface_cast         (NGtkInterface *in, NGtkType type);
NGTK_EXPORT int            ngtk_interface_is_a         (NGtkInterface *in, NGtkType type);
NGTK_EXPORT NGtkObject*    ngtk_interface_get_object   (NGtkInterface *in);
NGTK_EXPORT void           ngtk_interface_connect_to   (NGtkInterface *in, const char* signal, NGtkListener listener, void *user_data);
NGTK_EXPORT void           ngtk_interface_send_signal  (NGtkInterface *in, const char* signal, void *sigdata, int also_object);

/* To be used by external destructors of the objects. When a destructor
 * wants to finish a certain interface of an object, this is what he
 * should call */
NGTK_EXPORT void ngtk_interface_detach_and_free (NGtkInterface *in);


#define NGTK_O2F_CAST(o,bit,type) ((type*)(ngtk_object_cast(o,bit)->functions))
#define NGTK_O2D_CAST(o,bit,type,pos) ((type*)(ngtk_object_cast(o,bit)->imp_data[(pos)]))

#define NGTK_I2F_CAST(i,bit,type) ((type*)(ngtk_interface_cast(i,bit)->functions))
#define NGTK_I2D_CAST(i,bit,type,pos) ((type*)(ngtk_interface_cast(i,bit)->imp_data[(pos)]))

/** @} */
#endif
