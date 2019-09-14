#pragma once
#include "TextureObject.h"

class CPlayer;
class CTile
	:public CTextureObject
{
public:
	CTile();
	virtual ~CTile();

	// CTextureObject��(��) ���� ��ӵ�
	virtual int DoUpdate() override;
	virtual void DoLateUpdate() override;
	virtual void DoRender() override;
	virtual HRESULT DoInitialize() override;
	void EnterTrigger(CPlayer * player);
};

