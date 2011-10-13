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

/** The maximal amount of unique interface types that may be
 *       defined using the object system */
#define NGTK_MAX_INTERFACES           (sizeof(NGtkObjectTypeMask) * 8 - 1)
/** The maximal amount of implementation levels that may be used to
 *       implement a single interface */
#define NGTK_MAX_INTERFACE_IMP_LEVELS 5

/** The type-bit-mask of an object which implements no interface */
#define NGTK_TYPE_NONE 0

/** The general type of a listener function.
 * @param sigsrc The source object (NGtkObject*) or interface
 *               (NGtkInterface*) that generated the signal. Note that
 *               if a listener was registered for an object, it will
 *               always receive the object even if the signal originated
 *               in one of it's implemented interfaces.
 * @param signame The name of the signal
 * @param sigdata Specific data relevant to this signal instance
 *                (can change in every call).
 * @param lisdata Specific data registered with this listener.
 */
typedef void (*NGtkListener) (void *sigsrc, const char *signame, void *sigdata, void *lisdata);

/** A value indicating that a listener wants to listen to all the
 * signals without filtering by name */
#define NGTK_ALL_SIGNALS NULL

typedef struct _ngtk_listener_info {
	NGtkListener  func;
	const char   *signame;
	void         *lisdata;
} NGtkListenerInfo;


typedef void (*NGtkDestructor)  (NGtkObject *obj);

struct _ngtk_object {
	/** A bitmask of the implemented interfaces */
	NGtkObjectTypeMask  interface_mask;

	/** An array containing pointers to the implemented interfaces */
	NGtkInterface      *interfaces[NGTK_MAX_INTERFACES];

	/** Amount of references directly to this object */
	int                 direct_ref_count;

	/** Signal listeners */
	NGtkList            listeners;

	/** The object's destructor list. Destructors are called from
	 *  first to last */
	NGtkList            destructors;

	/** Warn from multiple attempts to free the object that occure
	 *  because of a free-ing recursion */
	int                 double_free_lock;
};


struct _ngtk_inteface {
	/** The object containing this interface */
	NGtkObject         *object;

	/** The type of this interface */
	NGtkType            type;

	/** Custom data for different implementation levels **/
	void               *imp_data[NGTK_MAX_INTERFACE_IMP_LEVELS];
	/** Functions to free the data of the implementation levels */
	NGtkFreeFunc        imp_data_free[NGTK_MAX_INTERFACE_IMP_LEVELS];
	/** Destructors for the different implementation levels */
	NGtkDestructor      imp_destruct[NGTK_MAX_INTERFACE_IMP_LEVELS];

	/** A pointer to the struct containing the function pointers of this
	 *  interface */
	void               *functions;
	/** A function to free the struct of the function pointers */
	NGtkFreeFunc        functions_free;

	/** Signal listeners for this interface*/
	NGtkList            listeners;
};

/** Create a new empty object, which doesn't implement any interface */
NGTK_EXPORT NGtkObject*    ngtk_object_new             ();
/** Call all the destructors of an object (interface destructors and
 *  object destructors) and then free the object. */
NGTK_EXPORT void           ngtk_object_free            (NGtkObject *obj);
/**
 * Return the interface implementation matching a certain type for a
 * given object.
 * @warning If the object does not implement that interface, a fatal
 *          runtime error will be raised!
 */
NGTK_EXPORT NGtkInterface* ngtk_object_cast            (NGtkObject *obj, NGtkType type);
/** Check if an object implements the given type of interface */
NGTK_EXPORT int            ngtk_object_is_a            (NGtkObject *obj, NGtkType type);
/** Increase the reference count of an object. Currently unused since
 * NGtk doesn't use reference counting for freeing objects */
NGTK_EXPORT void           ngtk_object_ref             (NGtkObject *obj);
/** Decrease the reference count of an object. Currently unused since
 * NGtk doesn't use reference counting for freeing objects */
NGTK_EXPORT void           ngtk_object_unref           (NGtkObject *obj);
/**
 * Register a listener for signals of the object
 * @param obj The object to listen to
 * @param signal The signal to listen to, or \ref NGTK_ALL_SIGNALS to
 *               listen to all the signals.
 * @param listener The actual listener function
 * @param user_data Custom data to pass to the listener (as its last
 *                  argument)
 */
NGTK_EXPORT void           ngtk_object_connect_to      (NGtkObject *obj, const char* signal, NGtkListener listener, void *user_data);
/** Generate a signal for the object, with the given signal data */
NGTK_EXPORT void           ngtk_object_send_signal     (NGtkObject *obj, const char* signal, void *sigdata);
/** Push a destructor to the object's destructor stack */
NGTK_EXPORT void           ngtk_object_push_destructor (NGtkObject *obj, NGtkDestructor dest);

/** Create a new interface of the given type, and attach it to the given
 * object */
NGTK_EXPORT NGtkInterface* ngtk_interface_new          (NGtkObject *obj, NGtkType type);
/**
 * Return the interface implementation matching a certain type for a
 * given interface. If the source interface has the desired type, it is
 * returned. Otherwise, a call to \ref ngtk_object_cast is made with
 * the object containing the given interface implementation
 * @warning If the object does not implement that interface, a fatal
 *          runtime error will be raised!
 */
NGTK_EXPORT NGtkInterface* ngtk_interface_cast         (NGtkInterface *in, NGtkType type);
/** Similar to \ref ngtk_object_is_a - check if the matching object of
 * the interface implements a certain interface type */
NGTK_EXPORT int            ngtk_interface_is_a         (NGtkInterface *in, NGtkType type);
/** Retrieve the object containing the interface */
NGTK_EXPORT NGtkObject*    ngtk_interface_get_object   (NGtkInterface *in);
/** Attach a listener to the interface. Similar to
 * \ref ngtk_object_connect_to */
NGTK_EXPORT void           ngtk_interface_connect_to   (NGtkInterface *in, const char* signal, NGtkListener listener, void *user_data);
/** Similar to \ref ngtk_object_send_signal.
 * @param also_object If TRUE, the signal will also be passed to the
 *                    listeners of the object */
NGTK_EXPORT void           ngtk_interface_send_signal  (NGtkInterface *in, const char* signal, void *sigdata, int also_object);

/* To be used by external destructors of the objects. When a destructor
 * wants to finish a certain interface of an object, this is what he
 * should call */
NGTK_EXPORT void ngtk_interface_detach_and_free (NGtkInterface *in);


/** Given an object, return the functions struct of the desired
 * interface and cast it to the given type. Minimal type checking is
 * included to assert that the object does implement the interface.
 * @param o The object (NGtkObject*)
 * @param bit The type of the interface (NGtkType)
 * @param type The type of the functions struct
 */
#define NGTK_O2F_CAST(o,bit,type) ((type*)(ngtk_object_cast(o,bit)->functions))
/** Given an object, return the data struct of the desired
 * interface and cast it to the given type. Minimal type checking is
 * included to assert that the object does implement the interface.
 * @param o The object (NGtkObject*)
 * @param bit The type of the interface (NGtkType)
 * @param type The type of the data struct
 * @param pos The implementation level containing the data
 */
#define NGTK_O2D_CAST(o,bit,type,pos) ((type*)(ngtk_object_cast(o,bit)->imp_data[(pos)]))

/** Similar to \ref NGTK_O2F_CAST, but receives an interface */
#define NGTK_I2F_CAST(i,bit,type) ((type*)(ngtk_interface_cast(i,bit)->functions))
/** Similar to \ref NGTK_O2D_CAST, but receives an interface */
#define NGTK_I2D_CAST(i,bit,type,pos) ((type*)(ngtk_interface_cast(i,bit)->imp_data[(pos)]))

/** @} */
#endif
