#include "stdafx.h"
#include "Stage02.h"
#include "Terrain.h"
#include "Player.h"


CStage02::CStage02()
{
}


CStage02::~CStage02()
{
	Release();
}

void CStage02::Update()
{
	//if (m_pKeyMgr->KeyUp(KEY_RETURN))
	//{
	//	m_pSceneMgr->SceneChange(CSceneMgr::STAGE03);
	//	return;
	//}
	if (m_pPlayer->GetStageCollsion())
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE03);
		return;
	}


	reproducePlayer();

	m_pTerrain->Update();
	m_pPlayer->Update();
}

void CStage02::LateUpdate()
{
}

void CStage02::Render()
{
	m_pTerrain->Render();

	m_pPlayer->Render();
}

HRESULT CStage02::Initialize()
{
	HRESULT hr = 0;

	/*hr = m_pTextureMgr->LoadTexture(
		CTextureMgr::MULTI_TEXTURE, L"../Texture/Stage/Player/Player.png",
		L"Player", L"Player", 38);
	FAILED_CHECK_MSG_RETURN(hr, L"Player Texture Load Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		CTextureMgr::MULTI_TEXTURE, L"../Texture/Stage/Player/PlayerEffect.png",
		L"Player", L"Effect", 38);
	FAILED_CHECK_MSG_RETURN(hr, L"PlayerEffect Texture Load Failed", E_FAIL);*/

	// Terrain
	m_pTerrain = CTerrain::Create();
	m_pTerrain->SetFilePath(L"../Texture/Mapdata/Stage02/MapData02.dat");
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);
	// Player
	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);
	dynamic_cast<CTerrain*>(m_pTerrain)->SetPlayerPointer(dynamic_cast<CPlayer*>(m_pPlayer));

	return S_OK;
}

void CStage02::Release()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pPlayer);
}

CStage02 * CStage02::Create()
{
	CStage02* pInstance = new CStage02;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
