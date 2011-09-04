#include <cstdio>
#include <cstdarg>

#include "WindowsBackend.h"

/**
 * This function is called when the DLL is un/loaded by a thread/process.
 *
 * @hinstDLL:            Handle to the DLL module
 * @ul_reason_for_call: The reason for the call to this function
 * @lpReserved:         Reserved windows stuff we don't use
 */
extern "C" BOOL APIENTRY
DllMain (
         HINSTANCE hinstDLL,
         DWORD ul_reason_for_call,
         LPVOID lpReserved
         )
{
  Ngtk::Backends::Windows::WindowsBackend::hinstance = hinstDLL;

  switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
      break;

    default:
      break;
    }
  return TRUE;
}

namespace Ngtk
{
  namespace Backends
  {
    namespace Windows
    {
      WindowsBackend* WindowsBackend::instance = NULL;
      HINSTANCE WindowsBackend::hinstance = NULL;

      WindowsBackend::WindowsBackend ()
      : AbstractBackend (FatalWarnings = true)
      {
        if (WindowsBackend::instance == NULL)
          WindowsBackend::instance = this;
        Debug ("WindowsBackend initialized");
      }

      WindowsBackend::~WindowsBackend ()
      {
        Debug ("WindowsBackend destroyed");
      }

      void
      WindowsBackend::StartMainLoop ()
      {
        MSG Msg;
        /* The Message Loop. Receive messages and continue as long as there is no
         * error (the return code is non negative) and as long as the message isn't
         * a QUIT message (return code 0).
         *
         * We don't want to limit to a specific window, so pass NULL as the HWND
         *
         * Finally, for now we don't limit to just specific events, so both min and
         * max of the message range are 0
         */
        while (GetMessage (&Msg, NULL, 0, 0) > 0)
          {
            /* Do some processing of the message. TODO: what exactly? */
            TranslateMessage (&Msg);
            /* Send the message forward. TODO: how does this work with TranslateMessage? */
            DispatchMessage (&Msg);
          }

        /* TODO: free all the widgets that may still be open in this backend */
      }

      void
      WindowsBackend::QuitMainLoop ()
      {
        PostQuitMessage (0); /* Send a WM_QUIT message, to stop the main loop */
      }

      void
      WindowsBackend::Debug (const char* format, ...)
      {
        fprintf (stderr, "Ngtk::Debug: ");

        va_list args;
        va_start (args, format);
        vfprintf (stdout, format, args);
        va_end (args);

        fprintf (stderr, "\n");
      }

      void
      WindowsBackend::Error (const char* format, ...)
      {
        fprintf (stderr, "Ngtk::Error: ");

        va_list args;
        va_start (args, format);
        vfprintf (stderr, format, args);
        va_end (args);

        fprintf (stderr, "\n");
        exit (EXIT_FAILURE);
      }

      void
      WindowsBackend::Warn (const char* format, ...)
      {
        fprintf (stderr, "Ngtk::Warn: ");

        va_list args;
        va_start (args, format);
        vfprintf (stderr, format, args);
        va_end (args);

        fprintf (stderr, "\n");
        if (FatalWarnings) exit (EXIT_FAILURE);
      }

    }
  }
}
