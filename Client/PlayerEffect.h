#pragma once
#include "GameObject.h"
class CPlayerEffect :
	public CGameObject
{
public:
	CPlayerEffect();
	virtual ~CPlayerEffect();

	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CPlayerEffect* Create();
	static CPlayerEffect* Create(TILE_INFO _m_tInfo);

	TILE_INFO m_tInfo;

	float m_fSpeedX;
};

