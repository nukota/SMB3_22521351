#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK2 65000
#define BRICK2_WIDTH 16
#define BRICK2_BBOX_WIDTH 16
#define BRICK2_BBOX_HEIGHT 15

class CBrick2 : public CGameObject {
public:
	CBrick2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};