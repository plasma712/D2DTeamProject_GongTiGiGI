#include "stdafx.h"
#include "Tile.h"
#include "Player.h"


CTile::CTile()
	: CTextureObject()
{
	this->LoadTextureObject(L"Terrain", L"Tile", 1);
	tileInfo.vPos = { 0.f,0.f,0.f };
	tileInfo.vSize = { 1.f,1.f,0.f };
}


CTile::~CTile()
{
}

int CTile::DoUpdate()
{
	return 0;
}

void CTile::DoLateUpdate()
{
}

void CTile::DoRender()
{
}

HRESULT CTile::DoInitialize()
{
	UpdateRECT();
	return E_NOTIMPL;
}

void CTile::EnterTrigger(CPlayer * player)
{
	//Sleep(1000);
	//cout << tileInfo.byDrawID << endl;
	//switch (tileInfo.byDrawID)
	//{
	//case NORMAL_TILE:
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	player->GetCrashPointCurPlayerPos();
	//	return;
	//case BOMB_TILE:	//�÷��̾� �ı�	//�ʱ� ��ġ�� �̵�
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	return;
	//case JUMP_TILE:	//���� �ι�	
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	return;
	//case LEFT_TILE:	//�������� 1�ʵ��� �̵�	
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	return;
	//case RIGHT_TILE://�����ʤ�,�� //
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	return;
	//case BROKEN_TILE:
	//	player->SetGroundCheck(true);
	//	player->SetColCheck(true);
	//	return;
	//case BLACK_TILE:
	//	return;
	//default:
	//	return;
	//}
}
