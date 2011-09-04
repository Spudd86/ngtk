#ifndef __Ngtk_Utils_DynamicLibrary_h__
#define __Ngtk_Utils_DynamicLibrary_h__

#ifdef NGTK_USER
#define NGTK_DLL_CLASS __declspec(dllimport)
#define NGTK_DLL_FUNC __declspec(dllimport)
#else
#define NGTK_DLL_CLASS __declspec(dllexport)
#define NGTK_DLL_FUNC __declspec(dllexport)

#endif
#endif