#include "Path.h"
#include "debug.h"

void CPath::Render()
 {
	int aniId = ID_ANI_PATH1;
	 switch (type) {
	 case 1: aniId = ID_ANI_PATH1; break;
	 case 2: aniId = ID_ANI_PATH2; break;
	 case 3: aniId = ID_ANI_PATH3; break;
	 case 4: aniId = ID_ANI_PATH4; break;
	 case 5: aniId = ID_ANI_PATH5; break;
	 case 6: aniId = ID_ANI_PATH6; break;
	 }
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPath::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PATH_BBOX_WIDTH / 2;
	t = y - PATH_BBOX_HEIGHT / 2;
	r = l + PATH_BBOX_WIDTH;
	b = t + PATH_BBOX_HEIGHT;
}