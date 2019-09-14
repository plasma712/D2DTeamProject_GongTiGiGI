#pragma once
#include "Scene.h"
class CStage01 :
	public CScene
{
private:
	CStage01();

public:
	virtual ~CStage01();

public:
	// CScene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage01* Create();
};

