#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_NUMBER 131000 // 131000 - 131009 for number 0 - 9

#define	NUMBER_WIDTH 7
#define NUMBER_BBOX_WIDTH 8
#define NUMBER_BBOX_HEIGHT 8

class CNumber : public CGameObject {
protected:
	int num = 0;
public:
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	CNumber(float x, float y) : CGameObject(x, y) {}
	CNumber(float x, float y, int num) : CGameObject(x, y) { this->num = num; }
};