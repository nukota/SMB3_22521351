#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_DESTINATION1 71001
#define ID_ANI_DESTINATION2 71002
#define ID_ANI_DESTINATION3 71003
#define ID_ANI_DESTINATION4 71004
#define ID_ANI_DESTINATION5 71005
#define ID_ANI_DESTINATION6 71006
#define ID_ANI_DESTINATION7 71007
#define ID_ANI_DESTINATION8 71008
#define ID_ANI_DESTINATION9 71009
#define ID_ANI_DESTINATION10 71010
#define ID_ANI_DESTINATION11 71011
#define ID_ANI_DESTINATION12 71012
#define ID_ANI_DESTINATION13 71013
#define ID_ANI_DESTINATION14 71014
#define ID_ANI_DESTINATION15 71015

#define DESTINATION_WIDTH 16
#define DESTINATION_BBOX_WIDTH 16
#define DESTINATION_BBOX_HEIGHT 16


class CDestination : public CGameObject {
protected:
	int type;
public:
	CDestination(float x, float y) : CGameObject(x, y) {}
	CDestination(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};
