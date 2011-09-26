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

/**
 * Pack the specified container and positions it's children, according
 * to the given size limitations
 *
 * @param self The layout object
 * @param cont The container to pack
 * @param width The width to use
 * @param height The height to use
 *
 * @warning This method should not be called outside of NGtk! Also,
 *          since containers may add functionallity to their pack
 *          method, then this function should not be called from
 *          anywhere other than a container's pack.
 * 
 * @since 0.9
 */
void ngtk_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height);

#endif
