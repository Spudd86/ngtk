#ifndef __NGtk_xlib_base_h__
#define __NGtk_xlib_base_h__

#include <X11/Xlib.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-xlib-widget-types.h"

/* The class in this file is an abstract class with final methods. This
 * means it should not be used directly as the only class of a
 * NGtkObject, and also that it's methods should not be overriden (and
 * therefore there is not function pointer struct).
 */
 
typedef struct _ngtk_xlib_base_d {
	NGtkRectangle area;
	Window        wnd;
} NGtkXlibBaseD;

#define NGTK_XLIBBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_XLIBBASE_TYPE,NGtkXlibBaseD,0)
#define NGTK_XLIBBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_XLIBBASE_TYPE,NGtkXlibBaseD,0)

NGtkXlibBaseI*        ngtk_xlib_base_create_interface  ();
void                  ngtk_xlib_base_d_free            (void *d);

Window                ngtk_xlib_base_get_window        (NGtkXlibBase *self);
const NGtkRectangle*  ngtk_xlib_base_get_abs_rect      (NGtkXlibBase *self);

void                  ngtk_xlib_base_map_to            (NGtkXlibBase *self, const NGtkRectangle *area);
void                  ngtk_xlib_base_unmap_window      (NGtkXlibBase *self);

/** Publish the window content to the screen */
void                  ngtk_xlib_base_publish_window    (NGtkXlibBase *self);

#endif
