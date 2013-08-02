/*
 * ngtk-container.h - Part of the NGtk library
 *
 * Copyright (c) 2011, Barak Itkin <lightningismyname at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NGtk nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
