#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_ROCK 74000
#define ROCK_WIDTH 16
#define ROCK_BBOX_WIDTH 16
#define ROCK_BBOX_HEIGHT 16


class CRock : public CGameObject {
protected:
	int type;
public:
	CRock(float x, float y) : CGameObject(x, y) {}
	//CRock(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};