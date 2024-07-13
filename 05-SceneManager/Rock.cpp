#include "Rock.h"

void CRock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_ROCK)->Render(x, y);

	//RenderBoundingBox();
}

void CRock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ROCK_BBOX_WIDTH / 2;
	t = y - ROCK_BBOX_HEIGHT / 2;
	r = l + ROCK_BBOX_WIDTH;
	b = t + ROCK_BBOX_HEIGHT;
}