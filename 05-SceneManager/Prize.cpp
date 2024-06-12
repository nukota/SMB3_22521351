#include "Prize.h"

void CPrize::Render()
{
	int aniId = ID_ANI_PRIZE_MUSHROOM;
	if (state == PRIZE_STATE_MUSHROOM)
		aniId = ID_ANI_PRIZE_MUSHROOM;
	else if (state == PRIZE_STATE_FLOWER)
		aniId = ID_ANI_PRIZE_FLOWER;
	else aniId = ID_ANI_PRIZE_STAR;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	if (!settimer) {
		settimer = true;
		timer = 0;
	}
	//RenderBoundingBox();
}

void CPrize::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PRIZE_BBOX_WIDTH / 2;
	t = y - PRIZE_BBOX_HEIGHT / 2;
	r = l + PRIZE_BBOX_WIDTH;
	b = t + PRIZE_BBOX_HEIGHT;
}

void CPrize::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timer < 150) {
		SetState(PRIZE_STATE_MUSHROOM);
		timer += dt;
	}
	else if (timer < 300) {
		SetState(PRIZE_STATE_FLOWER);
		timer += dt;
	}
	else if (timer < 450) {
		SetState(PRIZE_STATE_STAR);
		timer += dt;
	}
	else timer = 0;
	CGameObject::Update(dt, coObjects);
}

void CPrize::SetState(int state) 
{
	CGameObject::SetState(state);

}
