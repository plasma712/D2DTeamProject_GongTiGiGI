#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "Terrain.h"
#include "Player.h"


CScene::CScene()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pTerrain(nullptr),
	m_pPlayer(nullptr)
{
}


CScene::~CScene()
{
}

void CScene::reproducePlayer()
{
	if (m_pPlayer->GetTileInfo().vPos.y > WINCY)
	{
		SafeDelete(m_pPlayer);

		m_pPlayer = CPlayer::Create();
		dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));
	}
}
