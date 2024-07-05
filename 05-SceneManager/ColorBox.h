#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_COLOLRBOX0 20000
#define ID_ANI_COLOLRBOX1 21000
#define ID_ANI_COLOLRBOX2 22000
#define ID_ANI_COLOLRBOX3 23000
#define ID_ANI_COLOLRBOX4 24000
#define ID_ANI_COLOLRBOX5 25000
#define ID_ANI_COLOLRBOX6 26000
#define ID_ANI_COLOLRBOX7 27000
#define ID_ANI_COLOLRBOX8 28000
#define ID_ANI_COLOLRBOX9 29000

#define COLOLRBOX0_WIDTH 48
#define COLOLRBOX0_BBOX_WIDTH 48
#define COLOLRBOX0_BBOX_HEIGHT 47

#define COLOLRBOX1_WIDTH 48
#define COLOLRBOX1_BBOX_WIDTH 48
#define COLOLRBOX1_BBOX_HEIGHT 79

#define COLOLRBOX2_WIDTH 80
#define COLOLRBOX2_BBOX_WIDTH 80
#define COLOLRBOX2_BBOX_HEIGHT 47

#define COLOLRBOX3_WIDTH 64
#define COLOLRBOX3_BBOX_WIDTH 64
#define COLOLRBOX3_BBOX_HEIGHT 79

#define COLOLRBOX4_WIDTH 96
#define COLOLRBOX4_BBOX_WIDTH 96
#define COLOLRBOX4_BBOX_HEIGHT 31

#define COLOLRBOX5_WIDTH 64
#define COLOLRBOX5_BBOX_WIDTH 64
#define COLOLRBOX5_BBOX_HEIGHT 111

#define COLOLRBOX6_WIDTH 112
#define COLOLRBOX6_BBOX_WIDTH 112
#define COLOLRBOX6_BBOX_HEIGHT 31

#define COLOLRBOX7_WIDTH 112
#define COLOLRBOX7_BBOX_WIDTH 112
#define COLOLRBOX7_BBOX_HEIGHT 63

#define COLOLRBOX8_WIDTH 112
#define COLOLRBOX8_BBOX_WIDTH 112
#define COLOLRBOX8_BBOX_HEIGHT 95

#define COLOLRBOX9_WIDTH 48
#define COLOLRBOX9_BBOX_WIDTH 48
#define COLOLRBOX9_BBOX_HEIGHT 143


class CColorBox : public CGameObject {
protected: 
	int type;
public:
	CColorBox(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsStair() { return 1; }
};