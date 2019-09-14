#pragma once
#include "Scene.h"
class CStage05 :
	public CScene
{
public:
	CStage05();
	virtual ~CStage05();
public:
	// CScene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage05* Create();
};

