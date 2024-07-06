#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "MarioIcon.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->GetState() == MARIO_STATE_FLY)
			mario->SetState(MARIO_STATE_FLY);
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (CGame::GetInstance()->GetCurrentScene()->id == 2) 
			CGame::GetInstance()->InitiateSwitchScene(1);
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		mario->slowfall = false;
		mario->fly = false;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CMarioIcon* marioIcon = (CMarioIcon*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayerIcon();
	
	if (game->IsKeyDown(DIK_S) && mario->GetLevel() == MARIO_LEVEL_RACCOON && !mario->isOnPlatform) {
		if (abs(mario->GetVx()) >= MARIO_ACCEL_SPEED - 0.04f) 
			mario->SetState(MARIO_STATE_FLY);
			
		else if (mario->GetVy() > 0)
			mario->SetState(MARIO_STATE_SLOWFALL);
	}
		
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (marioIcon != NULL) marioIcon->SetState(2);
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (marioIcon != NULL) marioIcon->SetState(1);
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	
	else
		mario->SetState(MARIO_STATE_IDLE);
}