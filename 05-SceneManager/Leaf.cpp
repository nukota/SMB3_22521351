#include "Leaf.h"
#include "debug.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y) {
	SetState(LEAF_STATE_LEFT);
}

void CLeaf::Render()
{
	int aniId;
	if (state == LEAF_STATE_RIGHT) 
		aniId = ID_ANI_LEAF_RIGHT;
	else aniId = ID_ANI_LEAF_LEFT;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
	if (!setAppear) {
		start = GetTickCount64();
		setAppear = true;
		vy = -LEAF_FLYUP_SPEED;
		vx = 0;
		ax = 0;
		ay = LEAF_GRAVITY;
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
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	phasetimer += dt;	
	if (setAppear && GetTickCount64() - start > 400)
	{
		ay = 0;
		ay = -LEAF_GRAVITY_2;
		if (phasetimer < 500) {
			if (state == LEAF_STATE_RIGHT) {
				vx = -LEAF_FALL_SPEED_X;
				vy = LEAF_FALL_SPEED_Y;
				SetState(LEAF_STATE_LEFT);
			}
			ax = LEAF_FALL_AIR_RESISTANT;
		}
		else if (phasetimer < 1000) {
			if (state == LEAF_STATE_LEFT) {
				vx = LEAF_FALL_SPEED_X;
				vy = LEAF_FALL_SPEED_Y;
				SetState(LEAF_STATE_RIGHT);
			}
			ax = -LEAF_FALL_AIR_RESISTANT;
		}
		else phasetimer = 0;
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}