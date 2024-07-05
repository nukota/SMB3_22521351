#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_BORDER 70000

#define BORDER_WIDTH 400
#define BORDER_BBOX_WIDTH 400
#define BORDER_BBOX_HEIGHT 250


class CBorder : public CGameObject {
protected:
	int type;
public:
	CBorder(float x, float y) : CGameObject(x, y) {}
	//CBorder(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};
