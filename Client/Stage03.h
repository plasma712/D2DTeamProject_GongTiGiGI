#pragma once
#include "Scene.h"
class CStage03 :
	public CScene
{
private:
	CStage03();

public:
	virtual ~CStage03();

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage03* Create();
};

