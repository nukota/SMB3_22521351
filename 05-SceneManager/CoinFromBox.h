#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COINFROMBOX 35000

#define	COINFROMBOX_WIDTH 10
#define COINFROMBOX_BBOX_WIDTH 10
#define COINFROMBOX_BBOX_HEIGHT 16

class CCoinFromBox : public CGameObject {
protected:
	bool setAppear = false;
	ULONGLONG appear;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }

public:
	CCoinFromBox(float x, float y) : CGameObject(x, y) {}
	
};