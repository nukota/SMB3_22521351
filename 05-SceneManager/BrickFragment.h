#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICKFRAGMENT 37000

#define BRICKFRAGMENT_GRAVITY	0.002f;

#define BRICKFRAGMENT_WIDTH 8
#define BRICKFRAGMENT_BBOX_WIDTH 8
#define BRICKFRAGMENT_BBOX_HEIGHT 8

class CBrickFragment : public CGameObject {
protected: 
	float ax, ay;
public:
	CBrickFragment(float x, float y) : CGameObject(x, y) { ax = 0; ay = 0; }
	CBrickFragment(float x, float y, int type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};