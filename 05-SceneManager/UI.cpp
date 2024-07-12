#include "UI.h"
//#include "main.cpp"	
#include "debug.h"


void CUI::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_UI)->Render(x, y);
	//RenderBoundingBox();
}
void CUI::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - UI_BBOX_WIDTH / 2;
	t = y - UI_BBOX_HEIGHT / 2;
	r = l + UI_BBOX_WIDTH;
	b = t + UI_BBOX_HEIGHT;
}

void CUI::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	x = cx + 153;
	y = cy + 228;
	if (index <= 13 && !CreateSubObject) {
		CNumber* cnum = new CNumber(x + index * 15, y, 0);
		subObject = cnum;
		number.push_back(*cnum);
		//CreateSubObject = true;
		index++;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}