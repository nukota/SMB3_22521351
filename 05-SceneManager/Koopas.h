#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SPINNING_SPEED 0.25f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 26

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_IDLE 200
#define KOOPAS_STATE_SPINNING 300
#define KOOPAS_STATE_DIE 400
#define KOOPAS_STATE_DIE_2 500

#define ID_ANI_KOOPAS_WALKING_LEFT 37001
#define ID_ANI_KOOPAS_WALKING_RIGHT 37002
#define ID_ANI_KOOPAS_IDLE 37100
#define ID_ANI_KOOPAS_SPINNING 37200

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	float border_left = 0;
	float border_right = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return !(state == KOOPAS_STATE_DIE_2); }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual bool DeleteOffCamera() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithWingGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithWingKoopas(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	CKoopas(float x, float y, float border_left, float border_right);
	virtual void SpinLeft();
	virtual void SpinRight();
	virtual void SetState(int state);
};