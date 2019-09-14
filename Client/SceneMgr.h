#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENE_TYPE { LOGO, STAGE01, STAGE02, STAGE03, STAGE04, STAGE05, END };

public:
	CSceneMgr();
	~CSceneMgr();

public:
	HRESULT SceneChange(SCENE_TYPE eType);
	void Update();
	void LateUpdate();
	void Render();
	void NullRender();

private:
	void Release();

private:
	CScene*		m_pCurrentScene;
	SCENE_TYPE	m_eCurSceneType;
	SCENE_TYPE	m_ePreSceneType;

	int			m_iEvent;
};

