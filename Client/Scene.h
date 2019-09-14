#pragma once

class CGameObject;
class CPlayer;
class CTerrain;

class CScene
{
protected:
	CScene();

public:
	virtual ~CScene();

public:
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

protected:
	void reproducePlayer();

protected:
	CDeviceMgr*			m_pDeviceMgr;
	CTextureMgr*		m_pTextureMgr;
	CKeyMgr*			m_pKeyMgr;
	CTimeMgr*			m_pTimeMgr;
	CSceneMgr*			m_pSceneMgr;

	CTerrain*		m_pTerrain;
	CPlayer*		m_pPlayer;
};
