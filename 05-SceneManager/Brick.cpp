#include "Brick.h"
#include "BrickFragment.h"
#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (settimer) {
		if (GetTickCount64() - timer > 50) 
			this->Delete();
		else if (index < 3 && !CreateSubObject) {
			index++;
			subObject = new CBrickFragment(x, y, index);
			CreateSubObject = true;
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CBrick::SetState(int state) 
{
	if (state == BRICK_STATE_DESTROYED) {
		if (!settimer) {
			settimer = true;
			timer = GetTickCount64();
		}
	}
}