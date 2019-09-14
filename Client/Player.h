#pragma once
#include "GameObject.h"
#include "TextureObject.h"
class CPlayer :
	public CTextureObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	// CTextureObject을(를) 통해 상속됨
	virtual int DoUpdate() override;
	virtual void DoLateUpdate() override;
	virtual void DoRender() override;
	virtual HRESULT DoInitialize() override;

	void LimitSpeed();

public:
	static CPlayer* Create();

	float m_fSpeedY;
	float m_fSpeedX;
	float m_fJumpForce;
	float m_fJumpAcc;
	float m_fGroundY;
	CollPair m_collpair;
public:
	CGameObject*		m_pPlayerEffect;

	vector<CGameObject*> m_pPlayerEffectVec;

	list<CGameObject*> m_pPlayerEffectLst;

	void Rect();
	RECT m_tRect;
	void Parabola();
	bool GroundCheck;
	bool CollCheck;

	void SetGroundCheck(bool b);
	void Physics();
	TILE_INFO GetPlayerPos();
	void LstDelete();

	void SetColCheck(bool set);
	void SetColData(CollPair _cp);


public:	
	TILE_INFO	CurPos; // 현재 지점을 포지션복사... 
	float fPlayerJumpMax;
	float fCurPlayerJumpMax;

	//bool aa;

	//void setaaa(bool a);


	D3DXVECTOR3 vDir;//충돌 후 필요한 방향벡터 
	D3DXVECTOR3    PreCrashPointPos;
	D3DXVECTOR3    CrashPointCurPlayerPos;
	void GetPreCrashPointPos();
	void GetCrashPointCurPlayerPos();


	CAlarm alarm;
	CAlarm Arrow;
	bool ArrowActive;
	CSceneMgr SceneChage;
	static int stagecount;

	
	bool GetStageCollsion();
	bool StageCollsion;
};

