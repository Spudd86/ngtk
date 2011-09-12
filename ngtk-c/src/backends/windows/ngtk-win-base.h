#ifndef __NGtk_win_base_h__
#define __NGtk_win_base_h__

#include <Windows.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-win-widget-types.h"

//typedef struct _ngtk_winbase_f {
//	HWND (*get_hwnd)      (NGtkWinBase *self);
//	void (*set_hwnd)      (NGtkWinBase *self, HWND hwnd);
//	void (*destroy_hwnd)  (NGtkWinBase *self, HWND hwnd);
//} NGtkWinBaseF;
//
//#define NGTK_WINBASE_O2F(comp) NGTK_O2F_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseF)
//#define NGTK_WINBASE_I2F(comp) NGTK_I2F_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseF)
//

typedef struct _ngtk_win_base_d {
	HWND    hwnd;
	WNDPROC base_wndproc;
} NGtkWinBaseD;

#define NGTK_WINBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseD,0)
#define NGTK_WINBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseD,0)

NGtkWinBaseI*  ngtk_win_base_create_interface  ();
void           ngtk_win_base_d_free            (void *d);

///* The following functions only wrap calls instead of doing them
// * directly from the NGtkContainerF object */
//
//HWND   ngtk_winbase_get_hwnd      (NGtkWinBase *self)
//HWND   ngtk_winbase_set_hwnd      (NGtkWinBase *self, HWND hwnd);
//HWND   ngtk_winbase_destroy_hwnd  (NGtkWinBase *self, HWND hwnd);
//
//HWND   ngtk_winbase_get_hwnd_imp  (NGtkWinBase *self)
//HWND   ngtk_winbase_set_hwnd_imp  (NGtkWinBase *self, HWND hwnd);
//HWND   ngtk_winbase_destroy_hwnd  (NGtkWinBase *self, HWND hwnd);

#endif