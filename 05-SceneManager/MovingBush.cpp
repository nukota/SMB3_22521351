#include "MovingBush.h"

void CMovingBush::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MOVINGBUSH)->Render(x, y);

	//RenderBoundingBox();
}

void CMovingBush::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MOVINGBUSH_BBOX_WIDTH / 2;
	t = y - MOVINGBUSH_BBOX_HEIGHT / 2;
	r = l + MOVINGBUSH_BBOX_WIDTH;
	b = t + MOVINGBUSH_BBOX_HEIGHT;
}