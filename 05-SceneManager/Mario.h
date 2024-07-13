#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_ACCEL_SPEED	0.22f
#define MARIO_SLOWFALL_SPEED	0.005f
#define MARIO_SLOWFALL_TIME		1000
#define MARIO_FLY_SPEED	0.1f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0002f

#define MARIO_JUMP_SPEED_Y		0.55f
#define MARIO_JUMP_RUN_SPEED_Y	0.7f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_SLOWFALL		700
#define MARIO_STATE_FLY				701
#define MARIO_STATE_FLYDOWN				702

#define MARIO_STATE_TELEPORT1	800
#define MARIO_STATE_TELEPORT2	801

#define MARIO_STATE_SPIN	802

#pragma region ANIMATION_ID

//BIG MARIO
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_TELEPORT 1003

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_TELEPORT 1700

// RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 2010
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 2020

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 2110
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 2120

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 2210
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 2220

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2310
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2320

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_UP 2411
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_DOWN 2412
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_UP 2421
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_DOWN 2422

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2510
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2520

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2610
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2620

#define ID_ANI_MARIO_RACCOON_SLOWFALL_RIGHT 2710
#define ID_ANI_MARIO_RACCOON_SLOWFALL_LEFT 2720

#define ID_ANI_MARIO_RACCOON_SPIN 2800
#define ID_ANI_MARIO_RACCOON_TELEPORT 2900

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACCOON_BBOX_WIDTH  18
#define MARIO_RACCOON_BBOX_HEIGHT 26
#define MARIO_RACCOON_SITTING_BBOX_WIDTH  16
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_RACCOON_BBOX_HEIGHT-MARIO_RACCOON_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 13


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
protected:
	BOOLEAN isSitting;
	bool teleport = false, incave = false, inspin = false, teleporting = false, settimer = false;
	float tx, ty;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start, timer;
	
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPrize(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithStair(LPCOLLISIONEVENT e);
	void OnCollisionWithMysteryBox(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithWingGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithWingKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPipeAbove(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe2(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick2(LPCOLLISIONEVENT e);
	void LoseLife(LPCOLLISIONEVENT e = NULL);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	BOOLEAN isOnPlatform, slowfall = false, fly = false;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	//void StopAccelerate();

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE && !teleport); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	bool AtMaxSpeed() { return (abs(vx) >= MARIO_ACCEL_SPEED); } 
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	float GetLevel() { return level; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};