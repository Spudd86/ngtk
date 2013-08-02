/*
 * ngtk-container.h
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

#ifndef __NGtk_container_h__
#define __NGtk_container_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"

typedef NGtkList NGtkComponentList;

typedef struct _NGtkContainerF {
	NGtkComponentList* (*get_children)  (NGtkContainer *self);

	void               (*place_child)   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

	void               (*set_layout)    (NGtkContainer *self, NGtkLayout *layout);

	void               (*pack)          (NGtkContainer *self);

	/**
	 * Private methods that should only be called by the child to
	 * un/register itself with the parent.
	 */
	void               (*add_child)     (NGtkContainer *self, NGtkComponent* child);
	void               (*remove_child)  (NGtkContainer *self, NGtkComponent* child);
} NGtkContainerF;

#define NGTK_CONTAINER_O2F(comp) NGTK_O2F_CAST(comp,NGTK_CONTAINER_TYPE,NGtkContainerF)
#define NGTK_CONTAINER_I2F(comp) NGTK_I2F_CAST(comp,NGTK_CONTAINER_TYPE,NGtkContainerF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkContainerF object */

NGTK_EXPORT NGtkComponentList* ngtk_container_get_children  (NGtkContainer *self);

/**
 * Set the location of a child component relative to it's parent.
 *
 * @param self The container
 * @param child The child to position and/or resize
 * @param rect The new area that the child should cover
 *
 * @warning Undefined behaviour will occur if the rectangle will be
 *          partially outside of the parent area or if one or more of
 *          it's dimensions will be zero
 *
 * @since 0.9
 */
NGTK_EXPORT void               ngtk_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

/**
 * Set the layout object of a container
 *
 * @param self The container
 * @param layout The layout object
 *
 * @since 0.9
 */
NGTK_EXPORT void               ngtk_container_set_layout    (NGtkContainer *self, NGtkLayout *layout);

/**
 * Ask a comntainer to lay out it's children inside it's boundries using
 * it's layout object
 *
 * @param self The container
 *
 * @since 0.9
 */
NGTK_EXPORT void               ngtk_container_pack          (NGtkContainer *self);

/**
 * A method for a child to register itself with it's parent container.
 *
 * @param self The container
 * @param child The child to register
 *
 * @warning This method should not be called outside of NGtk!
 *
 * @since 0.9
 */
NGTK_EXPORT void               ngtk_container_add_child     (NGtkContainer *self, NGtkComponent* child);

/**
 * A method for a child to unregister itself from it's parent container.
 *
 * @param self The container
 * @param child The child to unregister
 *
 * @warning This method should not be called outside of NGtk!
 *
 * @since 0.9
 */
NGTK_EXPORT void               ngtk_container_remove_child  (NGtkContainer *self, NGtkComponent* child);

#endif