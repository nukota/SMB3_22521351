#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_PATH1 73001
#define ID_ANI_PATH2 73002
#define ID_ANI_PATH3 73003
#define ID_ANI_PATH4 73004
#define ID_ANI_PATH5 73005
#define ID_ANI_PATH6 73006
#define PATH_WIDTH 16
#define PATH_BBOX_WIDTH 16
#define PATH_BBOX_HEIGHT 16


class CPath : public CGameObject {
protected:
	int type;
public:
	CPath(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};