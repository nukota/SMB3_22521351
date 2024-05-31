#pragma once
#include "GameObject.h"

#define PAKKUN1_BBOX_WIDTH 16
#define PAKKUN1_BBOX_HEIGHT 32

#define PAKKUN1_STATE_TOPLEFT 100
#define PAKKUN1_STATE_BOTLEFT 200
#define PAKKUN1_STATE_TOPRIGHT 300
#define PAKKUN1_STATE_BOTRIGHT 300

#define ID_ANI_PAKKUN1_TOPLEFT 41001
#define ID_ANI_PAKKUN1_BOTLEFT 41002
#define ID_ANI_PAKKUN1_TOPRIGHT 41003
#define ID_ANI_PAKKUN1_BOTRIGHT 41004

class CPakkun1 : public CGameObject
{
protected:

	ULONGLONG chargetime, risetime;
	float y0;
	bool settime = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void Rise();
	virtual void Fall();
	virtual void Shoot();

public:
	CPakkun1(float x, float y);
	virtual void SetState(int state);
};