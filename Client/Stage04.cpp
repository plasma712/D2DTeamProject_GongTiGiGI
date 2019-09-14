#include "stdafx.h"
#include "Stage04.h"
#include "Terrain.h"
#include "Player.h"


CStage04::CStage04()
{
}


CStage04::~CStage04()
{
	Release();

}

void CStage04::Update()
{

	//if (m_pKeyMgr->KeyUp(KEY_RETURN))
	//{
	//	m_pSceneMgr->SceneChange(CSceneMgr::STAGE05);
	//	return;
	//}

	if (m_pPlayer->GetStageCollsion())
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE05);
		return;
	}


	reproducePlayer();



	m_pTerrain->Update();
	m_pPlayer->Update();
}

void CStage04::LateUpdate()
{
}

void CStage04::Render()
{
	m_pTerrain->Render();

	m_pPlayer->Render();
}

HRESULT CStage04::Initialize()
{
	HRESULT hr = 0;

	// Terrain
	m_pTerrain = CTerrain::Create();
	m_pTerrain->SetFilePath(L"../Texture/Mapdata/Stage04/MapData04.dat");
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);
	// Player
	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);
	dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));

	return S_OK;
}

void CStage04::Release()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pPlayer);
}

CStage04 * CStage04::Create()
{
	CStage04* pInstance = new CStage04;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
