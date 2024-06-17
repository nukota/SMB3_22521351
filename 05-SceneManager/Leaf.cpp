#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y) {}

void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_LEFT;
	if (state == LEAF_STATE_RIGHT) aniId = ID_ANI_LEAF_RIGHT;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
	if (!setAppear) {
		start = GetTickCount64();
		setAppear = true;
	}
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (GetTickCount64() - start > 500) {
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CLeaf*>(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	else return;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (vx < 0)
		SetState(LEAF_STATE_LEFT);
	else if (vx > 0) 
		SetState(LEAF_STATE_RIGHT);

	if (GetTickCount64() - start < 500) {
		vy = -LEAF_FLYUP_SPEED;
		ax = 0;
		ay = 0;
		vx = 0;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}