#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Ground.h"

#include "SampleKeyEventHandler.h"

using namespace std;
CPlayScene* CPlayScene::__instance = NULL;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	playericon = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_MARIOICON: 
		if (playericon != NULL)
		{
			DebugOut(L"[ERROR] MARIOICON object was created before!\n");
			return;
		}
		obj = new CMarioIcon(x, y); 
		playericon = (CMarioIcon*)obj; 

		DebugOut(L"[INFO] PlayerIcon object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x,y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_MYSTERYBOX_COIN: obj = new CMysteryBox(x, y, 1); break;
	case OBJECT_TYPE_MYSTERYBOX_MUSHROOM: obj = new CMysteryBox(x, y, 2); break;
	case OBJECT_TYPE_MYSTERYBOX_LEAF: obj = new CMysteryBox(x, y, 3); break;
	case OBJECT_TYPE_TREE1: obj = new CTree(x, y, 1); break;
	case OBJECT_TYPE_TREE2: obj = new CTree(x, y, 2); break;
	case OBJECT_TYPE_TREE3: obj = new CTree(x, y, 3); break;
	case OBJECT_TYPE_TREE4: obj = new CTree(x, y, 4); break;
	case OBJECT_TYPE_BUSH: obj = new CBush(x, y); break;
	case OBJECT_TYPE_WARPPIPE: obj = new CWarpPipe(x, y); break;
	case OBJECT_TYPE_CLOUD: obj = new CCloud(x, y); break;
	case OBJECT_TYPE_COLORBOX0: obj = new CColorBox(x, y, 0); break;
	case OBJECT_TYPE_COLORBOX1: obj = new CColorBox(x, y, 1); break;
	case OBJECT_TYPE_COLORBOX2: obj = new CColorBox(x, y, 2); break;
	case OBJECT_TYPE_COLORBOX3: obj = new CColorBox(x, y, 3); break;
	case OBJECT_TYPE_COLORBOX4: obj = new CColorBox(x, y, 4); break;
	case OBJECT_TYPE_COLORBOX5: obj = new CColorBox(x, y, 5); break;
	case OBJECT_TYPE_COLORBOX6: obj = new CColorBox(x, y, 6); break;
	case OBJECT_TYPE_COLORBOX7: obj = new CColorBox(x, y, 7); break;
	case OBJECT_TYPE_COLORBOX8: obj = new CColorBox(x, y, 8); break;
	case OBJECT_TYPE_COLORBOX9: obj = new CColorBox(x, y, 9); break;
	case OBJECT_TYPE_COLORBOX10: obj = new CColorBox(x, y, 10); break;
	case OBJECT_TYPE_WOOD: obj = new CWood(x, y); break;
	case OBJECT_TYPE_PIPEBELOW: obj = new CPipeBelow(x, y); break;
	case OBJECT_TYPE_PIPEABOVE: obj = new CPipeAbove(x, y); break;
	case OBJECT_TYPE_BLACKBACKGROUND: obj = new CBlackBackground(x, y); break;
	case OBJECT_TYPE_PRIZE: obj = new CPrize(x, y); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(x, y); break;
	case OBJECT_TYPE_KOOPAS_1: obj = new CKoopas(x, y, x - 35, x + 35); break;
	case OBJECT_TYPE_KOOPAS_2: obj = new CKoopas(x, y, x - 10, x + 10); break;
	case OBJECT_TYPE_GREENKOOPAS: obj = new CGreenKoopas(x, y); break;
	case OBJECT_TYPE_WINGGOOMBA: obj = new CWingGoomba(x, y); break;
	case OBJECT_TYPE_WINGKOOPAS: obj = new CWingKoopas(x, y); break;
	case OBJECT_TYPE_CURTAIN: obj = new CCurtain(x, y); break;
	case OBJECT_TYPE_TITLE: obj = new CTitle(x, y); break;
	case OBJECT_TYPE_TITLENUMBER: obj = new CTitleNumber(x, y); break; 
	case OBJECT_TYPE_FLOOR: obj = new CFloor(x, y); break;
	case OBJECT_TYPE_BACKGROUND: obj = new CBackground(x, y); break;
	case OBJECT_TYPE_BACKGROUNDITEMS: obj = new CBackgroundItems(x, y); break;
	case OBJECT_TYPE_PAKKUNFLOWER1: obj = new CPakkun1(x, y); break;
	case OBJECT_TYPE_PAKKUNFLOWER2: obj = new CPakkun2(x, y); break;
	case OBJECT_TYPE_PAKKUNFLOWER3: obj = new CPakkun3(x, y); break;
	case OBJECT_TYPE_SPAWNER: obj = new CSpawner(x, y, 0); break;
	case OBJECT_TYPE_SPAWNER1: obj = new CSpawner(x, y, 1); break;
	case OBJECT_TYPE_SPAWNER2: obj = new CSpawner(x, y,	2); break;
	case OBJECT_TYPE_SPAWNER3: obj = new CSpawner(x, y, 3); break;
	case OBJECT_TYPE_SPAWNER4: obj = new CSpawner(x, y, 4); break;
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_BORDER: obj = new CBorder(x, y); break;
	case OBJECT_TYPE_MOVINGBUSH: obj = new CMovingBush(x, y); break;
	case OBJECT_TYPE_ROCK: obj = new CRock(x, y); break;
	case OBJECT_TYPE_PATH1: obj = new CPath(x, y, 1); break;
	case OBJECT_TYPE_PATH2: obj = new CPath(x, y, 2); break;
	case OBJECT_TYPE_PATH3: obj = new CPath(x, y, 3); break;
	case OBJECT_TYPE_PATH4: obj = new CPath(x, y, 4); break;
	case OBJECT_TYPE_PATH5: obj = new CPath(x, y, 5); break;
	case OBJECT_TYPE_PATH6: obj = new CPath(x, y, 6); break;
	case OBJECT_TYPE_RIVER1: obj = new CRiver(x, y, 1); break;
	case OBJECT_TYPE_RIVER2: obj = new CRiver(x, y, 2); break;
	case OBJECT_TYPE_RIVER3: obj = new CRiver(x, y, 3); break;
	case OBJECT_TYPE_RIVER4: obj = new CRiver(x, y, 4); break;
	case OBJECT_TYPE_RIVER5: obj = new CRiver(x, y, 5); break;
	case OBJECT_TYPE_RIVER6: obj = new CRiver(x, y, 6); break;
	case OBJECT_TYPE_RIVER7: obj = new CRiver(x, y, 7); break;
	case OBJECT_TYPE_RIVER8: obj = new CRiver(x, y, 8); break;
	case OBJECT_TYPE_RIVER9: obj = new CRiver(x, y, 9); break;
	case OBJECT_TYPE_RIVER10: obj = new CRiver(x, y, 10); break;
	case OBJECT_TYPE_RIVER11: obj = new CRiver(x, y, 11); break;
	case OBJECT_TYPE_RIVER12: obj = new CRiver(x, y, 12); break;
	case OBJECT_TYPE_RIVER13: obj = new CRiver(x, y, 13); break;
	case OBJECT_TYPE_RIVER14: obj = new CRiver(x, y, 14); break;
	case OBJECT_TYPE_RIVER15: obj = new CRiver(x, y, 15); break;
	case OBJECT_TYPE_RIVER16: obj = new CRiver(x, y, 16); break;
	case OBJECT_TYPE_DESTINATION1: obj = new CDestination(x, y, 1); break;
	case OBJECT_TYPE_DESTINATION2: obj = new CDestination(x, y, 2); break;
	case OBJECT_TYPE_DESTINATION3: obj = new CDestination(x, y, 3); break;
	case OBJECT_TYPE_DESTINATION4: obj = new CDestination(x, y, 4); break;
	case OBJECT_TYPE_DESTINATION5: obj = new CDestination(x, y, 5); break;
	case OBJECT_TYPE_DESTINATION6: obj = new CDestination(x, y, 6); break;
	case OBJECT_TYPE_DESTINATION7: obj = new CDestination(x, y, 7); break;
	case OBJECT_TYPE_DESTINATION8: obj = new CDestination(x, y, 8); break;
	case OBJECT_TYPE_DESTINATION9: obj = new CDestination(x, y, 9); break;
	case OBJECT_TYPE_DESTINATION10: obj = new CDestination(x, y, 10); break;
	case OBJECT_TYPE_DESTINATION11: obj = new CDestination(x, y, 11); break;
	case OBJECT_TYPE_DESTINATION12: obj = new CDestination(x, y, 12); break;
	case OBJECT_TYPE_DESTINATION13: obj = new CDestination(x, y, 13); break;
	case OBJECT_TYPE_DESTINATION14: obj = new CDestination(x, y, 14); break;
	case OBJECT_TYPE_DESTINATION15: obj = new CDestination(x, y, 15); break;
	case OBJECT_TYPE_DECO1: obj = new CDecoration(x, y, 1); break;
	case OBJECT_TYPE_DECO2: obj = new CDecoration(x, y, 2); break;
	case OBJECT_TYPE_DECO3: obj = new CDecoration(x, y, 3); break;
	case OBJECT_TYPE_BRICK2: obj = new CBrick2(x, y); break;
	case OBJECT_TYPE_SMILECLOUD: obj = new CSmileCloud(x, y); break;
	case OBJECT_TYPE_PIPE2: obj = new CPipe2(x, y); break;
	case OBJECT_TYPE_UI: obj = new CUI(x, y); break;
	case OBJECT_TYPE_NUMBER: obj = new CNumber(x, y); break;
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_GROUND:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CGround(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	
	if (CGame::GetInstance()->GetCurrentScene()->id == 5 || CGame::GetInstance()->GetCurrentScene()->id == 2) cx = 0;
	else {
		if (cx < 0) cx = 0;
		if (cx > 2545) cx = 2545;
	}
	if (CGame::GetInstance()->GetCurrentScene()->id == 1 && cy < -40) {
		CGame::GetInstance()->SetCamPos(cx, cy + 40);
	}

	else CGame::GetInstance()->SetCamPos(cx, 0);

	size_t i = 0;
	while (i < objects.size())
	{
		objects[i]->Update(dt, &coObjects);
		
		//delete objects that get out of camera
		//if (objects[i]->DeleteOffCamera()) {
		//	if (objects[i]->x - 150 < cx || objects[i]->x + 150 > cx) {  DebugOut(L"delete object %f\n", objects[i]->x); objects[i]->Delete(); }
		//}

		//spawn sub object
		if (objects[i]->CreateSubObject) {
			CGameObject* obj = NULL;
			obj = objects[i]->subObject;
			objects.push_back(obj);
			Render();
			objects[i]->CreateSubObject = false;
		}
		i++;
	}

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;
	playericon = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::SpawnGameObject(CGameObject* obj, float x, float y) {
	obj->SetPosition(x, y);
	objects.push_back(obj);
}
