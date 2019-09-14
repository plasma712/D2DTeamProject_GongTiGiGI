#include "stdafx.h"
#include "Stage03.h"
#include "Terrain.h"
#include "Player.h"


CStage03::CStage03()
{
}


CStage03::~CStage03()
{
	Release();
}

void CStage03::Update()
{
	//if (m_pKeyMgr->KeyUp(KEY_RETURN))
	//{
	//	m_pSceneMgr->SceneChange(CSceneMgr::STAGE04);
	//	return;
	//}

	if (m_pPlayer->GetStageCollsion())
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE04);
		return;
	}


	reproducePlayer();



	m_pTerrain->Update();
	m_pPlayer->Update();
}



void CStage03::LateUpdate()
{
}

void CStage03::Render()
{
	m_pTerrain->Render();

	m_pPlayer->Render();
}

HRESULT CStage03::Initialize()
{
	HRESULT hr = 0;
	
	// Terrain
	m_pTerrain = CTerrain::Create();
	m_pTerrain->SetFilePath(L"../Texture/Mapdata/Stage03/MapData03.dat");
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);
	// Player
	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);
	dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));

	return S_OK;
}

void CStage03::Release()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pPlayer);
}

CStage03 * CStage03::Create()
{
	CStage03* pInstance = new CStage03;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
