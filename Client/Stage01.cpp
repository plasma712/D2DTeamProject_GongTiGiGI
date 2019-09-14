#include "stdafx.h"
#include "Stage01.h"
#include "Terrain.h"
#include "Player.h"

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
	Release();
}

void CStage01::Update()
{
	//if (m_pKeyMgr->KeyUp(KEY_RETURN))
	//{
	//	m_pSceneMgr->SceneChange(CSceneMgr::STAGE02);
	//	return;
	//}
	if (m_pPlayer->GetStageCollsion())
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE02);
		return;
	}

	reproducePlayer();

	m_pTerrain->Update();
	m_pPlayer->Update();


}

void CStage01::LateUpdate()
{
	
}

void CStage01::Render()
{
	m_pTerrain->Render();

	m_pPlayer->Render();
}

HRESULT CStage01::Initialize()
{
	HRESULT hr = 0;
	// Terrain
	m_pTerrain = CTerrain::Create();
	m_pTerrain->SetFilePath(L"../Texture/Mapdata/Stage01/MapData01.dat");
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);
	// Player
	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);
	dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));

	return S_OK;
}

void CStage01::Release()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pPlayer);
}

CStage01* CStage01::Create()
{
	CStage01* pInstance = new CStage01;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
