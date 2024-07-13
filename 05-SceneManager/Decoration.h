#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_DECO1 66100
#define ID_ANI_DECO2 66200
#define ID_ANI_DECO3 66300
#define DECO_WIDTH 16
#define DECO_BBOX_WIDTH 16
#define DECO_BBOX_HEIGHT 15

class CDecoration : public CGameObject {
protected: 
	int type;
public:
	CDecoration(float x, float y) : CGameObject(x, y) {}
	CDecoration(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};