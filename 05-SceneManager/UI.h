#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "vector"
#include "Number.h"

#define ID_ANI_UI 130000
#define UI_WIDTH 305
#define UI_BBOX_WIDTH 305
#define UI_BBOX_HEIGHT 48

class CUI : public CGameObject {
protected:
	vector<CGameObject> number = {};
	int index = 0;
public:
	CUI(float x, float y) : CGameObject(x, y) {
		/*for (int i = 0; i < 13; i++) {
			CNumber *Num = new CNumber(x, y);
			number.push_back(*Num);
		}*/
	}
	
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};