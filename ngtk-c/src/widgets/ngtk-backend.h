/*
 * ngtk-backend.h
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

#ifndef __NGtk_backend__
#define __NGtk_backend__

#include "ngtk-widgets.h"
#include <stdarg.h>

typedef struct _ngtk_backend_f {
	void                (*init)               (NGtkBackend *self);
	void                (*start_main_loop)    (NGtkBackend *self);
	void                (*quit_main_loop)     (NGtkBackend *self);
	void                (*quit)               (NGtkBackend *self);

	NGtkContainer*      (*create_root_window) (NGtkBackend *self, const char *title);
	NGtkComponent*      (*create_button)      (NGtkBackend *self, NGtkContainer* parent, const char *text);
	NGtkComponent*      (*create_label)       (NGtkBackend *self, NGtkContainer* parent, const char *text);
	NGtkComponent*      (*create_text_entry)  (NGtkBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

	NGtkEventGenerator* (*get_focus_holder)   (NGtkBackend *self);
	int                 (*set_focus_holder)   (NGtkBackend *self, NGtkComponent* new_focus);
	NGtkEventGenerator* (*focus_to_next)      (NGtkBackend *self);

	void                (*print)              (NGtkBackend *self, const char *format, va_list args);
	void                (*debug)              (NGtkBackend *self, const char *format, va_list args);
	void                (*error)              (NGtkBackend *self, const char *format, va_list args);
} NGtkBackendF;

#define NGTK_BACKEND_O2F(comp) NGTK_O2F_CAST(comp,NGTK_BACKEND_TYPE,NGtkBackendF)
#define NGTK_BACKEND_I2F(comp) NGTK_I2F_CAST(comp,NGTK_BACKEND_TYPE,NGtkBackendF)

/**
 * Initialize the backend
 *
 * @param self The backend to initialize
 *
 * @since 0.9
 */
void ngtk_backend_init (NGtkBackend *self);

/**
 * Start the main event loop
 *
 * @param self The backend which should start it's loop
 *
 * @warning This must be called only after the init function
 *
 * @since 0.9
 */
void ngtk_backend_start_main_loop (NGtkBackend *self);

/**
 * Quit the main event loop
 *
 * @param self The backend which should quit it's loop
 *
 * @since 0.9
 */
void ngtk_backend_quit_main_loop (NGtkBackend *self);

/**
 * Free all the resources that the backend allocated during it's `init`
 * function and during the main loop. THIS DOES NOT FREE THE
 * NGtkInterface OBJECT!
 *
 * @param self The backend to quit
 *
 * @warning This must be called outside of the main loop. Either before
 * or after.
 *
 * @since 0.9
 */
void ngtk_backend_quit (NGtkBackend *self);

/**
 * Create a new root window
 *
 * @param self The backend to use
 * @param title The title of the window
 * @return The root window
 *
 * @since 0.9
 */
NGtkContainer* ngtk_backend_create_root_window (NGtkBackend *self, const char *title);

/**
 * Create a new button
 *
 * @param self The backend to use
 * @param parent The parent container of this button
 * @param text The text that should appear on the button
 * @return The button
 *
 * @since 0.9
 */
NGtkComponent* ngtk_backend_create_button (NGtkBackend *self, NGtkContainer* parent, const char *text);

/**
 * Create a new label
 *
 * @param self The backend to use
 * @param parent The parent container of this label
 * @param text The text of the label
 * @return The label
 *
 * @since 0.9
 */
NGtkComponent* ngtk_backend_create_label (NGtkBackend *self, NGtkContainer* parent, const char *text);

/**
 * Create a new text entry
 *
 * @param self The backend to use
 * @param parent The parent container of this text entry
 * @param initial_text The initial text that should appear in the text-entry
 * @param max_text_len The maximal length of the text this text-entry
 *                     should be able to contain. In some backends it's
 *                     always unlimitied, and in some backends it will
 *                     follow this rule
 * @return The text entry
 *
 * @since 0.9
 */
NGtkComponent* ngtk_backend_create_text_entry (NGtkBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

/**
 * Return the current component which owns the focus
 *
 * @param self The backend to use
 * @return The current focus holder
 *
 * @since 0.9
 */
NGtkEventGenerator* ngtk_backend_get_focus_holder (NGtkBackend *self);

/**
 * Change the current component which owns the focus to a specified
 * component
 *
 * @param self The backend to use
 * @param self The new component that should own the focus
 * @return TRUE if the focus was set succesfully, FALSE if it's not a
 *         component that can hold the focus right now (and therefor the
 *         focus wasn't set).
 *
 * @since 0.9
 */
int ngtk_backend_set_focus_holder (NGtkBackend *self, NGtkComponent* new_focus);

/**
 * Transfer the focus to the next focusable component. This will
 * actually call set_focus_holder with the next component that should be
 * focused.
 *
 * @param self The backend to use
 * @return The new component to receive the focus
 *
 * @since 0.9
 */
NGtkEventGenerator* ngtk_backend_focus_to_next (NGtkBackend *self);

/**
 * Print a message to the user in a backend specific way
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
void ngtk_backend_print (NGtkBackend *self, const char *format, ...);
#define ngtk_print ngtk_backend_print

/**
 * Log a debugging message in a backend specific way
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
void ngtk_backend_debug (NGtkBackend *self, const char *format, ...);
#define ngtk_debug ngtk_backend_debug

/**
 * Report a fatal error message in a backend specific way and then quit
 * the program.
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
void ngtk_backend_error (NGtkBackend *self, const char *format, ...);
#define ngtk_error ngtk_backend_error

#endif
