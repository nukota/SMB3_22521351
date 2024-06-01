#include "fireball.h"
#include "debug.h"

CFireBall::CFireBall(float x, float y, int direction) :CGameObject(x, y) {
	switch (direction) {
	case 1:
		vx = -0.08f;
		vy = -0.03f;
		break;
	case 2:
		vx = -0.08f;
		vy = 0.03f;
		break;
	case 3:
		vx = 0.08f;
		vy = -0.03f;
		break;
	case 4:
		vx = 0.08f;
		vy = 0.03f;
		break;
	}
}

void CFireBall::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);
	//RenderBoundingBox();
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}


void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}