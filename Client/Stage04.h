#pragma once
#include "Scene.h"
class CStage04 :
	public CScene
{
public:
	CStage04();
	virtual ~CStage04();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage04* Create();

};

