/*
 * ngtk-backend.h - Part of the NGtk library
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

#ifndef __NGtk_backend__
#define __NGtk_backend__

#include "ngtk-widgets.h"
#include <stdarg.h>

typedef struct _ngtk_backend_f {
	void            (*init)               (NGtkBackend *self);
	void            (*start_main_loop)    (NGtkBackend *self);
	void            (*quit_main_loop)     (NGtkBackend *self);
	void            (*quit)               (NGtkBackend *self);

	NGtkContainer*  (*create_root_window) (NGtkBackend *self, const char *title);
	NGtkComponent*  (*create_button)      (NGtkBackend *self, NGtkContainer* parent, const char *text);
	NGtkComponent*  (*create_label)       (NGtkBackend *self, NGtkContainer* parent, const char *text);
	NGtkComponent*  (*create_text_entry)  (NGtkBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

	NGtkComponent*  (*get_focus_holder)   (NGtkBackend *self);
	int             (*set_focus_holder)   (NGtkBackend *self, NGtkComponent* new_focus);
	NGtkComponent*  (*focus_to_next)      (NGtkBackend *self);
	
	NGtkContainer*  (*get_root_window)    (NGtkBackend *self);
	const NGtkList* (*get_all_components) (NGtkBackend *self);

	void            (*print)              (NGtkBackend *self, const char *format, va_list args);
	void            (*debug)              (NGtkBackend *self, const char *format, va_list args);
	void            (*error)              (NGtkBackend *self, const char *format, va_list args);
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
NGTK_EXPORT void ngtk_backend_init (NGtkBackend *self);

/**
 * Start the main event loop
 *
 * @param self The backend which should start it's loop
 *
 * @warning This must be called only after the init function
 *
 * @since 0.9
 */
NGTK_EXPORT void ngtk_backend_start_main_loop (NGtkBackend *self);

/**
 * Quit the main event loop
 *
 * @param self The backend which should quit it's loop
 *
 * @since 0.9
 */
NGTK_EXPORT void ngtk_backend_quit_main_loop (NGtkBackend *self);

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
NGTK_EXPORT void ngtk_backend_quit (NGtkBackend *self);

/**
 * Create a new root window
 *
 * @param self The backend to use
 * @param title The title of the window
 * @return The root window
 *
 * @since 0.9
 */
NGTK_EXPORT NGtkContainer* ngtk_backend_create_root_window (NGtkBackend *self, const char *title);

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
NGTK_EXPORT NGtkComponent* ngtk_backend_create_button (NGtkBackend *self, NGtkContainer* parent, const char *text);

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
NGTK_EXPORT NGtkComponent* ngtk_backend_create_label (NGtkBackend *self, NGtkContainer* parent, const char *text);

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
NGTK_EXPORT NGtkComponent* ngtk_backend_create_text_entry (NGtkBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

/**
 * Return the current component which owns the focus
 *
 * @param self The backend to use
 * @return The current focus holder
 *
 * @since 0.9
 */
NGTK_EXPORT NGtkComponent* ngtk_backend_get_focus_holder (NGtkBackend *self);

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
NGTK_EXPORT int ngtk_backend_set_focus_holder (NGtkBackend *self, NGtkComponent* new_focus);

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
NGTK_EXPORT NGtkComponent* ngtk_backend_focus_to_next (NGtkBackend *self);

/**
 * Get the root window of this backend
 *
 * @param self The backend to use
 * @return The root window of this backend if already created, or NULL
 *         if no window was created yet
 *
 * @since 0.9
 */
NGTK_EXPORT NGtkContainer* ngtk_backend_get_root_window (NGtkBackend *self);

/**
 * Get a read-only list of the components that are currently allocated
 * in this backend. The read-only means that you may not modify the list
 * directly. However, you may trigger other functions of the backend and
 * it's widgets that will modify the list, and in these cases the list
 * you have will be updated.
 * 
 * Because of the ability to indirectly modify the list, you must be
 * extremly careful when iterating over it (and it's recommended that
 * you don't do so!).
 *
 * @param self The backend to use
 * @return An updating read-only list of the components allocated in
 *         this backend. This list includes the root window!
 *
 * @since 0.9
 */
NGTK_EXPORT const NGtkList* ngtk_backend_get_all_components (NGtkBackend *self);

/**
 * Print a message to the user in a backend specific way
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
NGTK_EXPORT void ngtk_backend_print (NGtkBackend *self, const char *format, ...);
#define ngtk_print ngtk_backend_print

/**
 * Log a debugging message in a backend specific way
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
NGTK_EXPORT void ngtk_backend_debug (NGtkBackend *self, const char *format, ...);
#define ngtk_debug ngtk_backend_debug

/**
 * Report a fatal error message in a backend specific way and then quit
 * the program.
 * 
 * @param self The backend to use
 * @param format The printing format (printf style)
 * @param ... The format string arguments
 */
NGTK_EXPORT void ngtk_backend_error (NGtkBackend *self, const char *format, ...);
#define ngtk_error ngtk_backend_error

#endif
