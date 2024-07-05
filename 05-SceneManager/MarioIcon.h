#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MARIOICON 120000
#define MARIOICON_SPEED 0.1f;

#define FILE_PATH "mariopath.txt"
#define MARIOICON_WIDTH 14
#define MARIOICON_BBOX_WIDTH 14
#define MARIOICON_BBOX_HEIGHT 16

class CMarioIcon : public CGameObject {
protected:
	int type, posx = 0, posy = 0, direction = 0;
public:
	CMarioIcon(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b); 
	void SetState(int state);
	virtual int IsBlocking() { return 0; }
};
