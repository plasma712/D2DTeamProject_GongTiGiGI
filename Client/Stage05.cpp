#include "stdafx.h"
#include "Stage05.h"
#include "Terrain.h"
#include "Player.h"


CStage05::CStage05()
{
}


CStage05::~CStage05()
{
	Release();

}

void CStage05::Update()
{
	if (m_pPlayer->GetStageCollsion())
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE01);
		return;
	}


	reproducePlayer();



	m_pTerrain->Update();
	m_pPlayer->Update();
}

void CStage05::LateUpdate()
{
}

void CStage05::Render()
{
	m_pTerrain->Render();

	m_pPlayer->Render();

}

HRESULT CStage05::Initialize()
{
	HRESULT hr = 0;

	// Terrain
	m_pTerrain = CTerrain::Create();
	m_pTerrain->SetFilePath(L"../Texture/Mapdata/Stage05/MapData05.dat");
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);
	// Player
	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);
	dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));

	return S_OK;
}

void CStage05::Release()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pPlayer);
}

CStage05 * CStage05::Create()
{
	CStage05* pInstance = new CStage05;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
