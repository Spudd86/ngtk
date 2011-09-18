#ifndef __NGtk_event_codes_h__
#define __NGtk_event_codes_h__

typedef enum {
	NGTK_MBUT_L,
	NGTK_MBUT_R,
	NGTK_MBUT_M,
	NGTK_MBUT_W
} NGtkMouseEventButton;

typedef enum {
	NGTK_MET_UP,
	NGTK_MET_DOWN
} NGtkMouseEventType;

typedef enum {
	NGTK_KKEY_MIN_CHAR     = 0x000,
	
	NGTK_KKEY_MAX_CHAR     = 0xff,

	NGTK_KKEY_ARROW_MIN    = 0x100,
	NGTK_KKEY_ARROW_LEFT,
	NGTK_KKEY_ARROW_RIGHT,
	NGTK_KKEY_ARROW_UP,
	NGTK_KKEY_ARROW_DOWN,
	NGTK_KKEY_ARROW_MAX    = 0x199,

	NGTK_KKEY_SPACERS_MIN  = 0x200,
	NGTK_KKEY_ENTER,
	NGTK_KKEY_SPACE,
	NGTK_KKEY_BACKSPACE,
	NGTK_KKEY_SPACERS_MAX  = 0x299,

	NGTK_KKEY_OTHER        = 0xffff
} NGtkKeyboardEventKey;

typedef struct _ngtk_mouse_event {
	NGtkMouseEventType   type;
	NGtkMouseEventButton button;
} NGtkMouseEvent;

typedef struct _ngtk_keyboard_event {
	NGtkKeyboardEventKey key;
} NGtkKeyboardEvent;

#endif
