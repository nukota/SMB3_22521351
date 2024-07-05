#include "Pipe2.h"

void CPipe2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPE2)->Render(x, y);
	//RenderBoundingBox();
}

void CPipe2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPE2_BBOX_WIDTH / 2;
	t = y - PIPE2_BBOX_HEIGHT / 2;
	r = l + PIPE2_BBOX_WIDTH;
	b = t + PIPE2_BBOX_HEIGHT;
}