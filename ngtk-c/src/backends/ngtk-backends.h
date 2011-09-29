#ifndef __NGtk_backends_h__
#define __NGtk_backends_h__

#include "../widgets/ngtk-widgets.h"

#ifdef     NGTK_USE_NC
#  include "nc/ngtk-nc.h"
#elif defined NGTK_USE_WINDOWS
#  include "windows/ngtk-windows-defs.h"
#elif defined NGTK_USE_XLIB
#  include "xlib/ngtk-xlib.h"
#else
#  error   "No backend selected for NGtk!"
#endif

#endif
