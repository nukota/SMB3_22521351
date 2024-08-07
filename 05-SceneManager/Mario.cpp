#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBox.h"
#include "MushRoom.h"
#include "Koopas.h"
#include "WingGoomba.h"
#include "WingKoopas.h"
#include "PakkunFlower1.h"
#include "PakkunFlower2.h"
#include "PakkunFlower3.h"
#include "fireball.h"
#include "Prize.h"
#include "Spawner.h"
#include "Leaf.h"
#include "PipeAbove.h"
#include "Pipe2.h"
#include "Brick.h"
#include "Brick2.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame::GetInstance()->GetCurrentScene()->xMario = x;
	CGame::GetInstance()->GetCurrentScene()->yMario = y;
	if (!teleport) {
		vy += ay * dt;
		vx += ax * dt;
	}
	

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	if (teleport && GetTickCount64() - timer > 2000) 
	{
		teleport = false;
		incave = !incave;
		x = tx; y = ty;
	}
	if (CGame::GetInstance()->GetCurrentScene()->id == 1 && y > 192 && !incave) 
		SetState(MARIO_STATE_DIE);

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0 && e->obj->IsStair())
	{
		vy = 0;
		isOnPlatform = true;
		fly = false;
	}
	else
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
			fly = false;
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPrize*>(e->obj))
		OnCollisionWithPrize(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMysteryBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CWingGoomba*>(e->obj))
		OnCollisionWithWingGoomba(e);
	else if (dynamic_cast<CWingKoopas*>(e->obj))
		OnCollisionWithWingKoopas(e);
	else if (dynamic_cast<CPakkun1*>(e->obj))
		LoseLife();
	else if (dynamic_cast<CPakkun2*>(e->obj))
		LoseLife();
	else if (dynamic_cast<CPakkun3*>(e->obj))
		LoseLife();
	else if (dynamic_cast<CFireBall*>(e->obj))
		LoseLife(e);
	else if (dynamic_cast<CPipeAbove*>(e->obj))
		OnCollisionWithPipeAbove(e);
	else if (dynamic_cast<CPipe2*>(e->obj))
		OnCollisionWithPipe2(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CBrick2*>(e->obj))
		OnCollisionWithBrick2(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG) 
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPrize(LPCOLLISIONEVENT e)
{
	CPrize* prize = (CPrize*)(e->obj);
	if (prize->GetState() == PRIZE_STATE_MUSHROOM)
		prize->SetState(PRIZE_STATE_MUSHROOM_FLYUP);
	else if (prize->GetState() == PRIZE_STATE_FLOWER)
		prize->SetState(PRIZE_STATE_FLOWER_FLYUP);
	else if (prize->GetState() == PRIZE_STATE_STAR)
		prize->SetState(PRIZE_STATE_STAR_FLYUP);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{
	CMysteryBox* mysterybox = (CMysteryBox*)(e->obj);
	if (e->ny > 0 && mysterybox->GetState() == MYSTERYBOX_STATE_FIRST) {
		mysterybox->SetState(MYSTERYBOX_STATE_TAKEN);
	}
}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e) 
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_SMALL)
	{
		y -= 8;
		level = MARIO_LEVEL_BIG;
		StartUntouchable();
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_BIG)
	{
		y -= 2;
		level = MARIO_LEVEL_RACCOON;
		StartUntouchable();
	}
	else {

	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (koopas->GetState() == KOOPAS_STATE_WALKING) 
	{
		if (e->ny < 0) 
		{
			koopas->SetState(KOOPAS_STATE_IDLE);
			y -= 10;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			return;
		} 
		else if (untouchable == 0)
		{
			if (level == MARIO_LEVEL_RACCOON)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
			else if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
	else if (koopas->GetState() == KOOPAS_STATE_IDLE)
	{
		if (e->ny < 0)
		{
			koopas->SetState(KOOPAS_STATE_SPINNING);
			koopas->SpinLeft();
			y -= 10;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			return;
		}
		else if (e->nx < 0) {
			y -= 10;
			koopas->SetState(KOOPAS_STATE_SPINNING);
			koopas->SpinLeft();
		}
		else {
			y -= 10;
			koopas->SetState(KOOPAS_STATE_SPINNING);
			koopas->SpinRight();
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (level == MARIO_LEVEL_RACCOON)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
			else if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithWingGoomba(LPCOLLISIONEVENT e)
{
	CWingGoomba* winggoomba = dynamic_cast<CWingGoomba*>(e->obj);

	// jump on top >> kill WingGoomba and deflect a bit 
	if (e->ny < 0)
	{
		winggoomba->SetState(WINGGOOMBA_STATE_DIE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by WingGoomba
	{
		if (untouchable == 0)
		{
			if (level == MARIO_LEVEL_RACCOON)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
			else if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithWingKoopas(LPCOLLISIONEVENT e)
{
	CWingKoopas* wingkoopas = dynamic_cast<CWingKoopas*>(e->obj);
	if (e->ny < 0)
	{
		wingkoopas->SetState(WINGKOOPAS_STATE_DIE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by WingKoopas
	{
		if (untouchable == 0)
		{
			if (level == MARIO_LEVEL_RACCOON)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
			else if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithPipeAbove(LPCOLLISIONEVENT e)
{
	if (e->ny < 0 && isSitting)
	{
		SetState(MARIO_STATE_TELEPORT1);
	}
}

void CMario::OnCollisionWithPipe2(LPCOLLISIONEVENT e)
{
	if (e->ny > 0 && state == MARIO_STATE_JUMP)
	{
	DebugOut(L"done this\n");
		SetState(MARIO_STATE_TELEPORT2);
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0 && state == MARIO_STATE_JUMP && level > MARIO_LEVEL_SMALL)
	{
		vx = -vx;
		brick->SetState(BRICK_STATE_DESTROYED);
	}
}

void CMario::OnCollisionWithBrick2(LPCOLLISIONEVENT e)
{
	CBrick2* brick2 = dynamic_cast<CBrick2*>(e->obj);
	if (e->ny > 0 && state == MARIO_STATE_JUMP && level > MARIO_LEVEL_SMALL)
	{
		vx = -vx;
		brick2->Delete();
	}
}

void CMario::LoseLife(LPCOLLISIONEVENT e)
{
	if (e != NULL) {
		e->obj->Delete();
	}
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

// Get animation ID for small Mario
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

// Get animdation ID for big Mario
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (teleport)
		aniId = ID_ANI_MARIO_TELEPORT;
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (abs(vx) >= MARIO_ACCEL_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (abs(vx) >= MARIO_ACCEL_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//Ger aniId for Racoon Mario
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (teleport)
		aniId = ID_ANI_MARIO_RACCOON_TELEPORT;
	else
	if (!isOnPlatform)
	{
		if (abs(vx) >= MARIO_ACCEL_SPEED)
		{
			if (nx >= 0) {
				if (vy >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_DOWN;
				else if (!slowfall) aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_UP;
			}
			else
			{
				if (vy >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_DOWN;
				else if (!slowfall) aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_UP;
			}
		}
		else
		{

			if (nx >= 0) {
				if (slowfall) 
					aniId = ID_ANI_MARIO_RACCOON_SLOWFALL_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
					
			}
			else {
				if (slowfall)
					aniId = ID_ANI_MARIO_RACCOON_SLOWFALL_LEFT;
				else aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (abs(vx) >= MARIO_ACCEL_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (abs(vx) >= MARIO_ACCEL_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting || teleport) break;
		maxVx = MARIO_ACCEL_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting || teleport) break;
		maxVx = -MARIO_ACCEL_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting || teleport) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting || teleport) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting || teleport) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_ACCEL_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			vy = 0.05f;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{	
			y += MARIO_SIT_HEIGHT_ADJUST - 2;
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting || teleport)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_SLOWFALL:
		if (isSitting || teleport) break;
		slowfall = true;
		vy = MARIO_SLOWFALL_SPEED;
		break;
	case MARIO_STATE_FLY:
		if (isSitting || teleport) break;
		if (vy > -MARIO_FLY_SPEED)
			vy = -MARIO_FLY_SPEED;
		fly = true;
		break;
	case MARIO_STATE_FLYDOWN:
		if (isSitting || teleport) break;
		vy = MARIO_FLY_SPEED;
		fly = true;
		break;
	
	case MARIO_STATE_TELEPORT1:
		if (teleport) break;
		teleport = true;
		timer = GetTickCount64();
		vy = 0.02f;
		tx = 2144;
		ty = 300;
		break;
	case MARIO_STATE_TELEPORT2:
		if (teleport) break;
		teleport = true;
		timer = GetTickCount64();
		vy = -0.05f;
		tx = 2450;
		ty = 120;
		break;
	}
	if (state != MARIO_STATE_SLOWFALL && state != MARIO_STATE_FLY && state != MARIO_STATE_FLYDOWN && state != MARIO_STATE_TELEPORT1 && state != MARIO_STATE_TELEPORT2)
		ay = MARIO_GRAVITY;
	else ay = 0;
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON) 
	{
		if (isSitting)
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (l == MARIO_LEVEL_RACCOON) y -= 10;
	level = l;
}

