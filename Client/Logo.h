#pragma once
#include "Scene.h"
class CLogo : public CScene
{
private:
	bool m_bIsDead;

	int m_iAmbient;

	float m_fDeltaTime;

private:
	CLogo();

public:
	virtual ~CLogo();

public:
	// CScene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CLogo* Create();

private:
	void FadeAway();
};

