#include "SmileCloud.h"

void CSmileCloud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SMILECLOUD)->Render(x, y);
	//RenderBoundingBox();
}

void CSmileCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SMILECLOUD_BBOX_WIDTH / 2;
	t = y - SMILECLOUD_BBOX_HEIGHT / 2;
	r = l + SMILECLOUD_BBOX_WIDTH;
	b = t + SMILECLOUD_BBOX_HEIGHT;
}