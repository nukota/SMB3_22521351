#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF 61000
#define ID_ANI_LEAF_LEFT 61100
#define ID_ANI_LEAF_RIGHT 61200

#define LEAF_FLYUP_SPEED 0.15f
#define LEAF_FALL_SPEED_X 0.1f
#define LEAF_FALL_SPEED_Y 0.085f
#define	LEAF_FALL_AIR_RESISTANT 0.000075f
#define LEAF_GRAVITY 0.00045f
#define LEAF_GRAVITY_2 0.00029f

#define LEAF_STATE_LEFT 1
#define LEAF_STATE_RIGHT 2

#define	LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

class CLeaf : public CGameObject {
protected:
	float ax;
	float ay;
	bool setAppear = false;

	ULONGLONG start, phasetimer = 0;

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);

};