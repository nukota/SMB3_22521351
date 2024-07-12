#include "BrickFragment.h"

CBrickFragment::CBrickFragment(float x, float y, int type) : CGameObject(x, y) 
{
	switch (type) {
	case 0: vy = -0.5f; vx = -0.12f; break;
	case 1: vy = -0.3f; vx = -0.12f; break;
	case 2: vy = -0.5f; vx = 0.12f; break;
	case 3: vy = -0.3f; vx = 0.12f; break;
	}
	ay = BRICKFRAGMENT_GRAVITY;
	ax = 0;
}

void CBrickFragment::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICKFRAGMENT)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickFragment::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICKFRAGMENT_BBOX_WIDTH / 2;
	t = y - BRICKFRAGMENT_BBOX_HEIGHT / 2;
	r = l + BRICKFRAGMENT_BBOX_WIDTH;
	b = t + BRICKFRAGMENT_BBOX_HEIGHT;
}

void CBrickFragment::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}