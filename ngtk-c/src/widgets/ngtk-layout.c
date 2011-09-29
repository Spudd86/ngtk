#include "ngtk-layout.h"

void ngtk_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height)
{
	NGTK_LAYOUT_O2F (self) -> pack (self, cont, width, height);
}
