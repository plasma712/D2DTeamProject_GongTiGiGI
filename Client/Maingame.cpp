#include "stdafx.h"
#include "Maingame.h"
#include "Terrain.h"
#include "Player.h"
#include "CollisionMgr.h"



float CMaingame::fps =0.f;
CMaingame::CMaingame()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pFrameMgr(CFrameMgr::GetInstance())
{
}


CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Update()
{
	m_pKeyMgr->Update();
	m_pTimeMgr->UpdateTime();
	m_pSceneMgr->Update();
}

void CMaingame::LateUpdate()
{
	m_pSceneMgr->LateUpdate();
}

void CMaingame::Render()
{
	m_pDeviceMgr->Render_Begin();

	// 앞으로 모든 오브젝트는 이 사이에서 렌더링 수행.
	m_pFrameMgr->RenderFPS();
	m_pSceneMgr->Render();

	m_pDeviceMgr->Render_End();
}

HRESULT CMaingame::Initialize()
{
	HRESULT hr = 0;

	hr = m_pDeviceMgr->InitDevice(CDeviceMgr::MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"장치초기화 실패", E_FAIL);

	hr = CTextureMgr::GetInstance()->LoadTexture(
		CTextureMgr::MULTI_TEXTURE, L"../Texture/Stage/Player/Player.png",
		L"Player", L"Player", 38);
	FAILED_CHECK_MSG_RETURN(hr, L"Player Texture Load Failed", E_FAIL);

	hr = CTextureMgr::GetInstance()->LoadTexture(
		CTextureMgr::MULTI_TEXTURE, L"../Texture/Stage/Player/PlayerEffect.png",
		L"Player", L"Effect", 38);
	FAILED_CHECK_MSG_RETURN(hr, L"PlayerEffect Texture Load Failed", E_FAIL);


	m_pTimeMgr->InitTime();

	m_pSceneMgr->SceneChange(CSceneMgr::LOGO);

	return S_OK;
}

void CMaingame::Release()
{
	m_pDeviceMgr->GetDevice()->Release();
	m_pSceneMgr->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
}

CMaingame* CMaingame::Create()
{
	CMaingame* pInstance = new CMaingame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
