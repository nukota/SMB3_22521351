#include "Destination.h"

void CDestination::Render()
{
	int aniId;
	switch (type) {
	case 1: aniId = ID_ANI_DESTINATION1; break;
	case 2: aniId = ID_ANI_DESTINATION2; break;
	case 3: aniId = ID_ANI_DESTINATION3; break;
	case 4: aniId = ID_ANI_DESTINATION4; break;
	case 5: aniId = ID_ANI_DESTINATION5; break;
	case 6: aniId = ID_ANI_DESTINATION6; break;
	case 7: aniId = ID_ANI_DESTINATION7; break;
	case 8: aniId = ID_ANI_DESTINATION8; break;
	case 9: aniId = ID_ANI_DESTINATION9; break;
	case 10: aniId = ID_ANI_DESTINATION10; break;
	case 11: aniId = ID_ANI_DESTINATION11; break;
	case 12: aniId = ID_ANI_DESTINATION12; break;
	case 13: aniId = ID_ANI_DESTINATION13; break;
	case 14: aniId = ID_ANI_DESTINATION14; break;
	case 15: aniId = ID_ANI_DESTINATION15; break;

	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CDestination::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - DESTINATION_BBOX_WIDTH / 2;
	t = y - DESTINATION_BBOX_HEIGHT / 2;
	r = l + DESTINATION_BBOX_WIDTH;
	b = t + DESTINATION_BBOX_HEIGHT;
}