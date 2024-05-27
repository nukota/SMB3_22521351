#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_STAIR1 21000
#define STAIR1_WIDTH 48
#define STAIR1_BBOX_WIDTH 48
#define STAIR1_BBOX_HEIGHT 82

class CStair1 : public CGameObject {
public:
	CStair1(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};