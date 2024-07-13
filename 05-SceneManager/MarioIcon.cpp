#include "MarioIcon.h"
#include "fstream"
#include "string"
#include "debug.h"

void CMarioIcon::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MARIOICON)->Render(x, y);

	//RenderBoundingBox();
}

void CMarioIcon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIOICON_BBOX_WIDTH / 2;
	t = y - MARIOICON_BBOX_HEIGHT / 2;
	r = l + MARIOICON_BBOX_WIDTH;
	b = t + MARIOICON_BBOX_HEIGHT;
}

void CMarioIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	x += vx * dt;
	y += vy * dt;
	if (x > 97 && vx > 0) {
		vx = 0; 
		x = 97;
	}
	else if (x < 65 && vx < 0) {
		vx = 0;
		x = 65;
	}
	else if (y > 100 && vy > 0) {
		vy = 0;
		y = 100;
	}
	else if (y < 68 && vy < 0) {
		vy = 0;
		y = 68;
	}
	CMarioIcon::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioIcon::SetState(int state) 
{
	
	CMarioIcon::SetState(state);
}