#include "stdafx.h"
#include "TextureObject.h"
#include "Texture.h"

CTextureObject::CTextureObject()
	:pTexInfo(nullptr) , index(0) , m_ObjectKey(L"") , m_StateKey(L"")
{
	ZeroMemory(&tileInfo, sizeof(TILE_INFO));
	ZeroMemory(&pTexInfo, sizeof(TEX_INFO));

}


CTextureObject::~CTextureObject()
{
}

int CTextureObject::Update()
{
//	CGameObject::LateInit();
	UpdateRECT();
	int  Event = DoUpdate();

	return Event;
}

void CTextureObject::LateUpdate()
{
	DoLateUpdate();
}

void CTextureObject::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale,
		tileInfo.vSize.x,
		tileInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans,
		tileInfo.vPos.x ,
		tileInfo.vPos.y ,
		0.f);

	matWorld = matScale * matTrans;

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), 
		nullptr, 
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//m_pDeviceMgr->GetSprite()->Draw(
	//	pTexInfo->pTexture,
	//	nullptr,
	//	&D3DXVECTOR3(pTexInfo->tImgInfo.Width*0.5f, pTexInfo->tImgInfo.Height*0.5f, 0.f),
	//	&tileInfo.vPos,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));
	DoRender();
}

HRESULT CTextureObject::Initialize()
{
	DoInitialize();
	return S_OK;
}

void CTextureObject::Release()
{
}

void CTextureObject::LoadTextureObject(wstring _ObjectKey , wstring _SdtateKey ,int _index)
{
	m_ObjectKey = _ObjectKey;
	m_StateKey = _SdtateKey;
	index = _index;
	pTexInfo = const_cast<TEX_INFO*>( m_pTextureMgr->GetTexInfo(
		_ObjectKey,
		_SdtateKey,
		_index));
}

void CTextureObject::SetDrawID(int _index)
{

	tileInfo.byDrawID = _index;
	pTexInfo = const_cast<TEX_INFO*>(m_pTextureMgr->GetTexInfo(
		m_ObjectKey,
		m_StateKey,
		tileInfo.byDrawID));
}

void CTextureObject::Translate(D3DXVECTOR3 vpos)
{
	tileInfo.vPos = vpos;
}

void CTextureObject::SetOption(int _option)
{
	tileInfo.byOption = _option;
}

void CTextureObject::SetSize(D3DXVECTOR3 vsize)
{
	tileInfo.vSize = vsize;
}



const TEX_INFO * CTextureObject::GetTexInfo()
{
	return pTexInfo;
}







