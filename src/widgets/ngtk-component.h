/*
 * ngtk-component.h - Part of the NGtk library
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

#ifndef __NGtk_component_h__
#define __NGtk_component_h__

#include "ngtk-widget-types.h"

typedef struct _NGtkComponentF {
	NGtkContainer* (*get_parent)    (NGtkComponent *self);

	int            (*get_enabled)   (NGtkComponent *self);
	void           (*set_enabled)   (NGtkComponent *self, int enabled);

	int            (*get_visible)   (NGtkComponent *self);
	void           (*set_visible)   (NGtkComponent *self, int visible);
	
	int            (*get_focusable) (NGtkComponent *self);

	const char*    (*get_text)      (NGtkComponent *self);
	void           (*set_text)      (NGtkComponent *self, const char *text);

	void           (*redraw)        (NGtkComponent *self);
} NGtkComponentF;

#define NGTK_COMPONENT_O2F(comp) NGTK_O2F_CAST(comp,NGTK_COMPONENT_TYPE,NGtkComponentF)
#define NGTK_COMPONENT_I2F(comp) NGTK_I2F_CAST(comp,NGTK_COMPONENT_TYPE,NGtkComponentF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkComponentF object */

/**
 * Return the parent container of this component
 *
 * @param self The component who's parent should be returned
 * @return The parent container of the component
 *
 * @since 0.9
 */
NGTK_EXPORT NGtkContainer* ngtk_component_get_parent  (NGtkComponent *self);

/**
 * Check if a component is enabled. Depending on the component, the
 * enabled status may change which events does it receive (if it's also
 * an event generator) and/or the way it's being drawn.
 *
 * @param self The component
 * @return The enabled status of the component
 *
 * @since 0.9
 */
NGTK_EXPORT int            ngtk_component_get_enabled (NGtkComponent *self);

/**
 * Set the enabled status of a component.
 *
 * @param self The component
 * @param enabled The new enabled status of the component
 *
 * @see ngtk_component_get_enabled
 *
 * @since 0.9
 */
NGTK_EXPORT void           ngtk_component_set_enabled (NGtkComponent *self, int enabled);

/**
 * Check whether a component is visible. Note that a visible component
 * inside a hidden parent will not be shown since the parent is hidden.
 *
 * @param self The component
 * @return Whether this component is visible
 *
 * @since 0.9
 */
NGTK_EXPORT int            ngtk_component_get_visible (NGtkComponent *self);

/**
 * Set the visibility of a component
 *
 * @param self The component
 * @param visible The new visibility statues of the component
 *
 * @see ngtk_component_get_visible
 *
 * @since 0.9
 */
NGTK_EXPORT void           ngtk_component_set_visible (NGtkComponent *self, int visible);

/**
 * Check whether a component is focusable. THis is only the focusable
 * property, not the entire conclusion of whether a component can
 * receive the focus.
 *
 * @param self The component
 * @return Whether this component is focusable
 *
 * @since 0.9
 */
NGTK_EXPORT int            ngtk_component_get_focusable (NGtkComponent *self);
/**
 * Get the text content of the component. This is component dependant
 * (for example, for windows the text is the title, for labels this is
 * the actual text displayed, ...)
 *
 * @param self The component
 * @return The text content of the component.
 *
 * @since 0.9
 */
NGTK_EXPORT const char*    ngtk_component_get_text    (NGtkComponent *self);

/**
 * Set the text of a component
 *
 * @param self The component
 * @param text The new visibility text content of the component
 *
 * @see ngtk_component_get_text
 *
 * @since 0.9
 */
NGTK_EXPORT void           ngtk_component_set_text    (NGtkComponent *self, const char *text);

/**
 * Ask a component to be redrawn.
 *
 * @param self The component
 * @return The text content of the component.
 *
 * @warning This method should not be called outside of NGtk - it's for
 *          internal use only. Furthermore, it should not be needed
 *          outside of NGtk since it's invoked automatically whenever
 *          needed.
 *
 * @since 0.9
 */
NGTK_EXPORT void           ngtk_component_redraw      (NGtkComponent *self);

#endif
