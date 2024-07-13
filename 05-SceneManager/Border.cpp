#include "Border.h"

void CBorder::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BORDER)->Render(x, y);

	//RenderBoundingBox();
}

void CBorder::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BORDER_BBOX_WIDTH / 2;
	t = y - BORDER_BBOX_HEIGHT / 2;
	r = l + BORDER_BBOX_WIDTH;
	b = t + BORDER_BBOX_HEIGHT;
}