#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_UI 130000
#define UI_WIDTH 305
#define UI_BBOX_WIDTH 305
#define UI_BBOX_HEIGHT 48

class CUI : public CGameObject {
public:
	CUI(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};