#include "ngtk-grid-layout.h"

static NGtkLayoutF NGtkGridLayoutFunctionsF = { ngtk_grid_layout_pack };

static void ngtk_grid_layout_destroy (NGtkGridLayout *self);

NGtkLayout* ngtk_grid_layout_new (NGtkContainer *cont, int xSize, int ySize)
{
	NGtkObject      *obj = ngtk_object_new ();
	NGtkLayoutI     *li  = ngtk_interface_new (obj, NGTK_LAYOUT_TYPE);
	NGtkGridLayoutD *gld = ngtk_new (NGtkGridLayoutD);

	li->imp_data[0] = gld;
	ngtk_list_init (& gld->areas);
	ngtk_list_init (& gld->comps);
	gld->cont = cont;
	gld->xSize = xSize;
	gld->ySize = ySize;
	li->imp_data_free[0] = ngtk_free;

	li->functions      = & NGtkGridLayoutFunctionsF;
	li->functions_free = NULL;

	ngtk_object_push_destructor (obj, ngtk_grid_layout_destroy);

	return obj;
}

void ngtk_grid_layout_destroy (NGtkGridLayout *self)
{
	ngtk_list_clear (& NGTK_GRID_LAYOUT_O2D (self) -> areas);
	ngtk_list_clear (& NGTK_GRID_LAYOUT_O2D (self) -> comps);

	ngtk_interface_detach_and_free (ngtk_object_cast (self, NGTK_LAYOUT_TYPE));
}

int ngtk_grid_layout_add  (NGtkLayout *self, NGtkComponent *comp, const NGtkRectangle *area)
{
	NGtkGridLayoutD *gld = NGTK_GRID_LAYOUT_O2D (self);
	NGtkRectangle   *rect;
	NGtkListNode    *iter;

	if (! (area->x >= 0 && area->y >= 0))
		return FALSE;
	else if (! (area->x + area->w <= gld->xSize && area->y + area->h <= gld->ySize))
		return FALSE;
	else ngtk_list_foreach (iter, & gld->areas)
		if (ngtk_rect_interesects ((NGtkRectangle*)iter->data, area))
			return FALSE;

	rect = ngtk_new (NGtkRectangle);
	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

	ngtk_list_append (& gld -> areas, rect);
	ngtk_list_append (& gld -> comps, comp);

	return TRUE;
}

void ngtk_grid_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height)
{
	NGtkGridLayoutD *gld = NGTK_GRID_LAYOUT_O2D (self);
	NGtkListNode *area_iter, *comp_iter;

	ngtk_list_2foreach (area_iter, &gld->areas, comp_iter, & gld->comps)
	{
		NGtkRectangle *rect = (NGtkRectangle*) area_iter->data;
		NGtkComponent *comp = (NGtkComponent*) comp_iter->data;
		NGtkRectangle  new_area;

		int ymax_p1, xmax_p1;

		/* Warning: if you don't want to skip "pixels", don't "optimize" the
		 * math below. xmax and ymax should be computed individually of the
		 * width and height due to integer division problems that may arise */
		new_area.x = rect->x * width / gld->xSize;
		new_area.y = rect->y * height / gld->ySize;
		xmax_p1 = (rect->x + rect->w) * width / gld->xSize;
		ymax_p1 = (rect->y + rect->h) * height / gld->ySize;
		new_area.w = xmax_p1 - new_area.x;
		new_area.h = ymax_p1 - new_area.y;

		ngtk_container_place_child (cont, comp, &new_area);
	}
}
