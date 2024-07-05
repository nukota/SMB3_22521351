#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_RIVER1 75001
#define ID_ANI_RIVER2 75002
#define ID_ANI_RIVER3 75003
#define ID_ANI_RIVER4 75004
#define ID_ANI_RIVER5 75005
#define ID_ANI_RIVER6 75006
#define ID_ANI_RIVER7 75007
#define ID_ANI_RIVER8 75008
#define ID_ANI_RIVER9 75009
#define ID_ANI_RIVER10 75010
#define ID_ANI_RIVER11 75011
#define ID_ANI_RIVER12 75012
#define ID_ANI_RIVER13 75013
#define ID_ANI_RIVER14 75014
#define ID_ANI_RIVER15 75015
#define ID_ANI_RIVER16 75016

#define RIVER_WIDTH 8
#define RIVER_BBOX_WIDTH 8
#define RIVER_BBOX_HEIGHT 8


class CRiver : public CGameObject {
protected:
	int type;
public:
	CRiver(float x, float y) : CGameObject(x, y) {}
	CRiver(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};
