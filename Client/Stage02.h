#pragma once
#include "Scene.h"

class CStage02 :
	public CScene
{
private:
	CStage02();

public:
	virtual ~CStage02();

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage02* Create();
};

