#include <ncurses.h>
#include "ngtk-nc-defs.h"

static int                 ngtk_nc_should_quit  = FALSE;
static NGtkComponentList*  ngtk_nc_components   = NULL;
static NGtkContainer*      ngtk_nc_root_window  = NULL;
static int                 ngtk_nc_initialized  = FALSE;
static NGtkEventGenerator* ngtk_nc_focus_holder = NULL;

void ngtk_nc_init ()
{
	/* Prevent double initialization */
	ngtk_assert (! ngtk_nc_initialized);
	
	/* Start CURSES mode */
	initscr ();

	/* Initialize the use of color pairs */
	start_color ();

	/* Disable line bufferring, but do generate signals from control
	 * characters */
	cbreak ();

	/* Do not show typed characters */
	noecho ();

	/* A list of all the components that were created during runtime.
	 * This will allow us to do easy garbage collection later */
	ngtk_nc_components = ngtk_list_new ();

	/* Finally, marked as initialized */
	ngtk_nc_initialized = TRUE;
}

void ngtk_nc_start_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	while (ngtk_nc_should_quit)
	{
		int ch = getchar ();
		
	}
}

void ngtk_nc_quit_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	ngtk_nc_should_quit = TRUE;
}

void ngtk_nc_quit ()
{
	NGtkListNode *iter;

	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	/* Release the allocated components */
	if (ngtk_nc_components)
	{
		/* If there are any components that were still not freed, free them
		 * before we quit, to make sure we don't leak memory */
		ngtk_list_foreach (iter, ngtk_nc_components)
		{
			NGtkComponent *comp = (NGtkComponent*) iter->data;
			ngtk_object_free (comp);
		}

		/* Now free the component list */
		ngtk_list_free (ngtk_nc_components);
		
		ngtk_nc_components = NULL;
	}

	/* Free the root window */
	if (ngtk_nc_root_window)
	{
		ngtk_object_free (ngtk_nc_root_window);
		ngtk_nc_root_window = NULL;
	}

	/* Leave curses mode */
	endwin ();
}

NGtkContainer* ngtk_nc_create_root_window (const char* title)
{
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
	return NULL;
}

NGtkComponent* ngtk_nc_create_button (const char* text)
{
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
	return NULL;
}

NGtkComponent* ngtk_nc_create_label (const char* text)
{
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
	return NULL;
}

NGtkComponent* ngtk_nc_create_text_entry (const char* text)
{
	return NULL;
}

void ngtk_nc_set_focus_holder (NGtkEventGenerator* eg)
{
	ngtk_nc_focus_holder = eg;
}

NGtkEventGenerator* ngtk_nc_get_focus_holder ()
{
	return ngtk_nc_focus_holder;
}
