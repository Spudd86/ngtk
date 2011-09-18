#ifndef __NGtk_layout_h__
#define __NGtk_layout_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"

typedef struct _NGtkLayoutF {
	void (*pack) (NGtkLayout *self, NGtkContainer *cont, int width, int height);
} NGtkLayoutF;

#define NGTK_LAYOUT_O2F(comp) NGTK_O2F_CAST(comp,NGTK_LAYOUT_TYPE,NGtkLayoutF)
#define NGTK_LAYOUT_I2F(comp) NGTK_I2F_CAST(comp,NGTK_LAYOUT_TYPE,NGtkLayoutF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkLayoutF object */

void ngtk_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height);

#endif
