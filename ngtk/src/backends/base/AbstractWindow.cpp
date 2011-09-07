#include <string>

#include "AbstractWindow.h"

namespace Ngtk
{
	namespace Backends
	{
		namespace Base
		{
			AbstractWindow::AbstractWindow (std::string title, WindowCloseBehaviour OnClose)
				: OnClose (OnClose)
			{
			}

			AbstractWindow::~AbstractWindow ()
			{
			}
		}
	}
}
