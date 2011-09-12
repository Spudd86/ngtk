#ifndef __NGtk_memory_h__
#define __NGtk_memory_h__

#include <stdlib.h>

#define ngtk_new(type)         ((type*) ngtk_malloc (sizeof (type)))
#define ngtk_new_array(type,n) ((type*) ngtk_malloc ((n) * sizeof (type)))

/* May be useful to have all the code use our own malloc/free. Note
 * that these must be valid function pointers to be passed on, so if
 * something custom should be made, it must be wrapped in a real function
 */
#define ngtk_malloc      malloc
#define ngtk_free        free

typedef void (*NGtkFreeFunc) (void *data);
#endif