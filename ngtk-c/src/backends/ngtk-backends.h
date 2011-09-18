#ifndef __NGtk_backends_h__
#define __NGtk_backends_h__

#include "../widgets/ngtk-widgets.h"

#ifdef     NGTK_USE_NC
#  include "nc/ngtk-nc.h"
#elseifdef NGTK_USE_WINDOWS
#  include "windows/ngtk-windows-defs.h"
#else
#  error   "No backend selected for NGtk!"
#endif

#endif
