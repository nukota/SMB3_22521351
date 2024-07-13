#include "River.h"

void CRiver::Render()
{
	int aniId;
	switch (type) {
	case 1: aniId = ID_ANI_RIVER1; break;
	case 2: aniId = ID_ANI_RIVER2; break;
	case 3: aniId = ID_ANI_RIVER3; break;
	case 4: aniId = ID_ANI_RIVER4; break;
	case 5: aniId = ID_ANI_RIVER5; break;
	case 6: aniId = ID_ANI_RIVER6; break;
	case 7: aniId = ID_ANI_RIVER7; break;
	case 8: aniId = ID_ANI_RIVER8; break;
	case 9: aniId = ID_ANI_RIVER9; break;
	case 10: aniId = ID_ANI_RIVER10; break;
	case 11: aniId = ID_ANI_RIVER11; break;
	case 12: aniId = ID_ANI_RIVER12; break;
	case 13: aniId = ID_ANI_RIVER13; break;
	case 14: aniId = ID_ANI_RIVER14; break;
	case 15: aniId = ID_ANI_RIVER15; break;
	case 16: aniId = ID_ANI_RIVER16; break;

	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CRiver::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - RIVER_BBOX_WIDTH / 2;
	t = y - RIVER_BBOX_HEIGHT / 2;
	r = l + RIVER_BBOX_WIDTH;
	b = t + RIVER_BBOX_HEIGHT;
}