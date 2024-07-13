#include "Decoration.h"

void CDecoration::Render()
{
	int aniId;
	switch (type) {
	case 1: aniId = ID_ANI_DECO1; break;
	case 2: aniId = ID_ANI_DECO2; break; 
	case 3: aniId = ID_ANI_DECO3; break;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CDecoration::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - DECO_BBOX_WIDTH / 2;
	t = y - DECO_BBOX_HEIGHT / 2;
	r = l + DECO_BBOX_WIDTH;
	b = t + DECO_BBOX_HEIGHT;
}