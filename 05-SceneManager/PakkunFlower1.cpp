#include "PakkunFlower1.h"
#include "debug.h"

CPakkun1::CPakkun1(float x, float y) :CGameObject(x, y)
{
	SetState(PAKKUN1_STATE_TOPLEFT);
	//risetime = 0;
}

void CPakkun1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PAKKUN1_BBOX_WIDTH / 2;
	top = y - PAKKUN1_BBOX_HEIGHT / 2;
	right = left + PAKKUN1_BBOX_WIDTH;
	bottom = top + PAKKUN1_BBOX_HEIGHT;
}

void CPakkun1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (risetime > 6000) {
		Fall();
		risetime = 0;
	}
	else if (risetime > 4000) {
		Shoot();
	}
	else if (risetime > 2000) {
		Rise();
	}
	else risetime += dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);*/
}


void CPakkun1::Render()
{
	int aniId = ID_ANI_PAKKUN1_TOPLEFT;
	if (state == PAKKUN1_STATE_TOPLEFT)
	{
		aniId = ID_ANI_PAKKUN1_TOPLEFT;
	} 
	else if (state == PAKKUN1_STATE_BOTLEFT)
	{
		aniId = ID_ANI_PAKKUN1_BOTLEFT;
	}
	else if (state == PAKKUN1_STATE_TOPRIGHT)
	{
		aniId = ID_ANI_PAKKUN1_TOPRIGHT;
	}
	else if (state == PAKKUN1_STATE_BOTRIGHT)
	{
		aniId = ID_ANI_PAKKUN1_BOTRIGHT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPakkun1::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPakkun1::Rise() {

}
void CPakkun1::Fall() {

}
void CPakkun1::Shoot() {

}
