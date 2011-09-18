#ifndef __NGtk_nc_base_h__
#define __NGtk_nc_base_h__

#include <ncurses.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-nc-widget-types.h"

/* The class in this file is an abstract class with final methods. This
 * means it should not be used directly as the only class of a
 * NGtkObject, and also that it's methods should not be overriden (and
 * therefore there is not function pointer struct).
 */
 
typedef struct _ngtk_win_base_d {
	NGtkRectangle  area;
	WINDOW        *wnd;
} NGtkNcBaseD;

#define NGTK_NCBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_NCBASE_TYPE,NGtkNcBaseD,0)
#define NGTK_NCBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_NCBASE_TYPE,NGtkNcBaseD,0)

NGtkNcBaseI*          ngtk_nc_base_create_interface  ();
void                  ngtk_nc_base_d_free            (void *d);

WINDOW*               ngtk_nc_base_get_window        (NGtkNcBase *self);
const NGtkRectangle*  ngtk_nc_base_get_abs_rect      (NGtkNcBase *self);

void                  ngtk_nc_base_map_to            (NGtkNcBase *self, const NGtkRectangle *area);
void                  ngtk_nc_base_unmap_window      (NGtkNcBase *self);

#endif
