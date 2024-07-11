#include "Number.h"

void CNumber::Render()
{
	int aniId;
	aniId = ID_ANI_NUMBER + num;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CNumber::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - NUMBER_BBOX_WIDTH / 2;
	t = y - NUMBER_BBOX_HEIGHT / 2;
	r = l + NUMBER_BBOX_WIDTH;
	b = t + NUMBER_BBOX_HEIGHT;
}