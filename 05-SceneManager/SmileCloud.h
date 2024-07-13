#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_SMILECLOUD 63000
#define SMILECLOUD_WIDTH 16
#define SMILECLOUD_BBOX_WIDTH 16
#define SMILECLOUD_BBOX_HEIGHT 15

class CSmileCloud : public CGameObject {
public:
	CSmileCloud(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};