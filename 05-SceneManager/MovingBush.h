#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_MOVINGBUSH 76000
#define MOVINGBUSH_WIDTH 16
#define MOVINGBUSH_BBOX_WIDTH 16
#define MOVINGBUSH_BBOX_HEIGHT 16


class CMovingBush : public CGameObject {
protected:
	int type;
public:
	CMovingBush(float x, float y) : CGameObject(x, y) {}
	//CRock(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};