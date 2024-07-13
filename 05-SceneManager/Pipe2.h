#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE2 65000
#define PIPE2_WIDTH 32
#define PIPE2_BBOX_WIDTH 32
#define PIPE2_BBOX_HEIGHT 32

class CPipe2: public CGameObject {
public:
	CPipe2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};