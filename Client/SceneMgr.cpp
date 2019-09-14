#include "stdafx.h"
#include "Logo.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pCurrentScene(nullptr), m_eCurSceneType(END), m_ePreSceneType(END),
	m_iEvent(NO_EVENT)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENE_TYPE eType)
{
	if (m_ePreSceneType != eType)
	{
		SafeDelete(m_pCurrentScene);

		switch (eType)
		{
		case LOGO:
			m_pCurrentScene = CLogo::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Logo Create Failed", E_FAIL);
			break;
		case STAGE01:
			m_pCurrentScene = CStage01::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Stage01 Create Failed", E_FAIL);
			break;
		case STAGE02:
			m_pCurrentScene = CStage02::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Stage02 Create Failed", E_FAIL);
			break;
		case STAGE03:
			m_pCurrentScene = CStage03::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Stage03 Create Failed", E_FAIL);
			break;
		case STAGE04:
			m_pCurrentScene = CStage04::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Stage04 Create Failed", E_FAIL);
			break;
		case STAGE05:
			m_pCurrentScene = CStage05::Create();
			NULL_CHECK_MSG_RETURN(m_pCurrentScene, L"Stage05 Create Failed", E_FAIL);
			break;

		}

		m_eCurSceneType = eType;
		m_ePreSceneType = m_eCurSceneType;
		m_iEvent = CHANGE_SCENE;
	}

	return S_OK;
}

void CSceneMgr::Update()
{
	m_iEvent = NO_EVENT;

	NULL_CHECK(m_pCurrentScene);
	m_pCurrentScene->Update();
}

void CSceneMgr::LateUpdate()
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	NULL_CHECK(m_pCurrentScene);
	m_pCurrentScene->LateUpdate();
}

void CSceneMgr::Render()
{

	if (CHANGE_SCENE == m_iEvent)
	{
		NullRender();
		return;
	}
		

	NULL_CHECK(m_pCurrentScene);
	m_pCurrentScene->Render();
}

void CSceneMgr::NullRender()
{
	D3DXMATRIX matWorld, matTrans;

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"NullRender");

	float fX = pTexInfo->tImgInfo.Width*0.5f;
	float fY = pTexInfo->tImgInfo.Height*0.5f;

	D3DXMatrixTranslation(
		&matTrans,
		WINCX*0.5f,
		WINCY*0.5f,
		0.f);

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSceneMgr::Release()
{
	SafeDelete(m_pCurrentScene);
}
