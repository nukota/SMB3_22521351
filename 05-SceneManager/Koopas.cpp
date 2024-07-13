#include "Koopas.h"
#include "Goomba.h"
#include "WingGoomba.h"
#include "WingKoopas.h"
#include "MysteryBox.h"
#include "Brick.h"
#include "Brick2.h"
#include "debug.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = x - KOOPAS_BBOX_WIDTH / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	if (state == KOOPAS_STATE_WALKING) 
	{
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else 
	{
		top = y - KOOPAS_BBOX_HEIGHT / 2 + 12;
		bottom = top + KOOPAS_BBOX_HEIGHT - 12;
	}
		
}

void CKoopas::OnNoCollision(DWORD dt)
{	
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0 && e->obj->IsStair())
	{
		vy = 0;
		isOnPlatform = true;
	}
	bool kt = false;
	if (state == KOOPAS_STATE_SPINNING) 
	{
		if (dynamic_cast<CKoopas*>(e->obj)) 
			OnCollisionWithKoopas(e);
		else if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CWingGoomba*>(e->obj))
			OnCollisionWithWingGoomba(e);
		else if (dynamic_cast<CWingKoopas*>(e->obj))
			OnCollisionWithWingKoopas(e);
		else if (dynamic_cast<CMysteryBox*>(e->obj))
			OnCollisionWithMysteryBox(e);
		else if (dynamic_cast<CBrick*>(e->obj)) {
			OnCollisionWithBrick(e);
			kt = true;
		}
			
		else if (dynamic_cast<CBrick2*>(e->obj))
			OnCollisionWithBrick2(e);
	}
	if (e->obj->IsBlocking()) {
		if (e->ny != 0)
		{
			vy = 0;
			isOnPlatform = true;
		}
		else if (e->nx != 0 && !kt)
		{
			vx = -vx;
		}
	}	
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e) 
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE_2);
	}
}
void CKoopas::OnCollisionWithWingGoomba(LPCOLLISIONEVENT e)
{
	CWingGoomba* Winggoomba = dynamic_cast<CWingGoomba*>(e->obj);
	Winggoomba->SetState(WINGGOOMBA_STATE_DIE_2);
}
void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e) 
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_IDLE)
	{
		koopas->SetState(KOOPAS_STATE_DIE_2);
	}
}
void CKoopas::OnCollisionWithWingKoopas(LPCOLLISIONEVENT e)
{
	CWingKoopas* wingkoopas = dynamic_cast<CWingKoopas*>(e->obj);
	wingkoopas->SetState(WINGKOOPAS_STATE_DIE_2);
}
void CKoopas::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{
	CMysteryBox* mysterybox = (CMysteryBox*)(e->obj);
	if (e->ny == 0 && mysterybox->GetState() == MYSTERYBOX_STATE_FIRST) {
		mysterybox->SetState(MYSTERYBOX_STATE_TAKEN);
	}
}
void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if (e->ny == 0) {
		brick->SetState(BRICK_STATE_DESTROYED);
		vx = -vx;
	}
}
void CKoopas::OnCollisionWithBrick2(LPCOLLISIONEVENT e)
{
	CBrick2* brick2 = (CBrick2*)(e->obj);
	if (e->ny == 0) {
		//brick2->Delete();
		vx = -vx;
	}
}


void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y > 250) this->Delete();
	vy += ay * dt;
	vx += ax * dt;

	if (y > 186)
		SetState(KOOPAS_STATE_DIE);

	if (state == KOOPAS_STATE_IDLE && GetTickCount64() - standuptimer > 5000) {
		SetState(KOOPAS_STATE_WALKING);
	}
	if (state == KOOPAS_STATE_WALKING && !settimer && vy > 0.05f)
	{
		y -= 2;
		x -= 4 * vx / abs(vx);
		vx = -vx;
		settimer = true;
		timer = GetTickCount64();
	}
	if (GetTickCount64() - timer > 50) settimer = false;
	isOnPlatform = false;
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId;
	if (vx < 0) aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	else aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	if (state == KOOPAS_STATE_IDLE)
	{
		aniId = ID_ANI_KOOPAS_IDLE;
	} 
	else if (state == KOOPAS_STATE_SPINNING) {
		aniId = ID_ANI_KOOPAS_SPINNING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		if (state == KOOPAS_STATE_IDLE)
			y -= 6;
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SPINNING:
		y -= 4;
		break;
	case KOOPAS_STATE_IDLE:
		standuptimer = GetTickCount64();
		y -= 6;
		vx = 0;
		break;
	case KOOPAS_STATE_DIE:
		y += 10;
		vy = 0.05f;
		break;
	case KOOPAS_STATE_DIE_2:
		y -= 10;
		vy = -0.05f;
		vx = 0;
		ax = 0;
		break;
	}
}

void CKoopas::SpinLeft() {
	vx = KOOPAS_SPINNING_SPEED;
}

void CKoopas::SpinRight() {
	vx = -KOOPAS_SPINNING_SPEED;
}
