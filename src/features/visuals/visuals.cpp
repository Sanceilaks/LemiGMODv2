#include "visuals.h"
#include <globals.h>
#include <interfaces.h>
#include <math/math.h>

CVisuals* Visuals = new CVisuals();

void CVisuals::draw_fov()
{
	if (!settings::visuals->draw_fov || !Interfaces->engine->is_in_game())
		return;

	int fov = settings::legit_bot->fov;
	int sw = globals->screen_width;
	int sh = globals->screen_height;
	fov = fov > 180 ? 180 : fov;

	Interfaces->surface->set_drawing_color(0, 0, 0);
	Interfaces->surface->draw_outlined_circle(sw / 2, sh / 2, tan(DEG2RAD(fov) / 2) / tan(DEG2RAD(globals->view.fov) / 2) * sw, 124);
}
