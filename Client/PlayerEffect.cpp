#include "stdafx.h"
#include "PlayerEffect.h"
#include "ScrollMgr.h"


CPlayerEffect::CPlayerEffect()
{
}


CPlayerEffect::~CPlayerEffect()
{
}

int CPlayerEffect::Update()
{
	return NO_EVENT;
}

void CPlayerEffect::LateUpdate()
{
}

void CPlayerEffect::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	const TEX_INFO* pTexInfo = nullptr;


	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f);


	matWorld = matScale * matTrans;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Effect", 0);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));




}

HRESULT CPlayerEffect::Initialize()
{
	//m_tInfo.vPos = { 400.f,300.f,0.f };
	//m_tInfo.vSize = { 0.02f,0.02f,0.f };
	m_fSpeedX = 3.f;

	return S_OK;
}

void CPlayerEffect::Release()
{
}

CPlayerEffect * CPlayerEffect::Create()
{
	CPlayerEffect* pInstance = new CPlayerEffect;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

CPlayerEffect * CPlayerEffect::Create(TILE_INFO _m_tInfo)
{
	CPlayerEffect* pInstance = new CPlayerEffect;
	pInstance->m_tInfo = _m_tInfo;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
