#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
	:m_bIsDead(false),
	m_iAmbient(255),
	m_fDeltaTime(0.f)
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Update()
{
	if (m_pKeyMgr->KeyUp(KEY_RETURN) && !m_bIsDead)
		m_bIsDead = true;

	FadeAway();
}

void CLogo::LateUpdate()
{

}

void CLogo::Render()
{
	D3DXMATRIX matWorld, matTrans;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Logo");

	float fX = pTexInfo->tImgInfo.Width*0.5f;
	float fY = pTexInfo->tImgInfo.Height*0.5f;

	D3DXMatrixTranslation(
		&matTrans,
		WINCX*0.5f,
		WINCY*0.5f,
		0.f);

	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);
	m_pDeviceMgr->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_iAmbient, 255, 255, 255));
}

HRESULT CLogo::Initialize()
{
	m_pTextureMgr->LoadTexture(
		m_pTextureMgr->SINGLE_TEXTURE,
		L"../Texture/Logo/Logo.png",
		L"Logo");

	m_pTextureMgr->LoadTexture(
		m_pTextureMgr->SINGLE_TEXTURE,
		L"../Texture/Logo/Logo.png",
		L"NullRender");

	return S_OK;
}

void CLogo::Release()
{
}

CLogo* CLogo::Create()
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLogo::FadeAway()
{
	if (!m_bIsDead)
		return;

	m_fDeltaTime += m_pTimeMgr->GetDeltaTime();
	
	if (m_fDeltaTime >= 1.f / 60.f)
	{
		m_iAmbient -= 1;
		m_fDeltaTime = 0.f;
	}
	

	if (m_iAmbient <= 0)
	{
		m_pSceneMgr->SceneChange(CSceneMgr::STAGE01);
		return;
	}
}
