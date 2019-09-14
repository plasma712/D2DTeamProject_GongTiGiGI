#pragma once

class CTerrain;
class CGameObject;
class CPlayer;
class CCollisionMgr;
class CMaingame
{
private:
	CMaingame();

public:
	~CMaingame();

public:	
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMaingame* Create();

	static float fps;
private:
	CDeviceMgr*			m_pDeviceMgr;
	CSceneMgr*			m_pSceneMgr;
	CKeyMgr*			m_pKeyMgr;
	CTimeMgr*			m_pTimeMgr;
	CFrameMgr*			m_pFrameMgr;

};

