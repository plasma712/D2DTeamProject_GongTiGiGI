#pragma once
#include "GameObject.h"
class CTexture;


class CTextureObject :
	public CGameObject
{

protected:
	TEX_INFO* pTexInfo;
	int index;
	wstring m_ObjectKey;
	wstring m_StateKey;
public:
	CTextureObject();
	virtual ~CTextureObject();

	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

	void LoadTextureObject(wstring _ObjectKey, wstring _SdtateKey, int _index);

	void SetDrawID(int _index);


	virtual int DoUpdate() = 0;
	virtual void DoLateUpdate() = 0;
	virtual void DoRender() = 0;
	virtual HRESULT DoInitialize() = 0;


	/*
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
	*/


	void Translate(D3DXVECTOR3 vpos);
	void SetOption(int _option);
	void SetSize(D3DXVECTOR3 vsize);
	const TEX_INFO * GetTexInfo();
	//void Translate(D3DXVECTOR3 vpos);
	//void Translate(D3DXVECTOR3 vpos);


	



};

