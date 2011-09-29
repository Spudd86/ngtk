/*
 * ngtk-component.h
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

#ifndef __NGtk_component_h__
#define __NGtk_component_h__

#include "ngtk-widget-types.h"

typedef struct _NGtkComponentF {
	NGtkContainer* (*get_parent)  (NGtkComponent *self);

	int            (*get_enabled) (NGtkComponent *self);
	void           (*set_enabled) (NGtkComponent *self, int enabled);

	int            (*get_visible) (NGtkComponent *self);
	void           (*set_visible) (NGtkComponent *self, int visible);

	const char*    (*get_text)    (NGtkComponent *self);
	void           (*set_text)    (NGtkComponent *self, const char *text);

	void           (*redraw)      (NGtkComponent *self);
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
NGtkContainer* ngtk_component_get_parent  (NGtkComponent *self);

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
int            ngtk_component_get_enabled (NGtkComponent *self);

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
void           ngtk_component_set_enabled (NGtkComponent *self, int enabled);

/**
 * Check whether a component is visible. Note that a visible component
 * inside a hidden parent will not be shown since the parent is hidden.
 *
 * @param self The component
 * @return Whether this component is visible
 *
 * @since 0.9
 */
int            ngtk_component_get_visible (NGtkComponent *self);

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
void           ngtk_component_set_visible (NGtkComponent *self, int visible);

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
const char*    ngtk_component_get_text    (NGtkComponent *self);

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
void           ngtk_component_set_text    (NGtkComponent *self, const char *text);

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
void           ngtk_component_redraw      (NGtkComponent *self);

#endif
