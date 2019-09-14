#pragma once
#include "GameObject.h"

class CTile;
class CCollisionMgr;
class CPlayer;

class CTerrain :
	public CGameObject
{
private:
	bool m_bIsData;
	CCollisionMgr * CollMgr;
	CPlayer * m_pPlayer;

	wstring m_wstrFilePath;

private:
	CTerrain();

public:
	virtual ~CTerrain();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	const vector<CTile *> GetTile();
	void SetPlayerPointer(CPlayer * _player);
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT LateInit() override;
	virtual void Release() override;

private:
	bool IsPicking();

	bool CheckInOut(const POINT& pt, const int iIndex);

private:
	void SaveTile(const wstring& wstrFilePath);
	void LoadTile(const wstring& wstrFilePath);

public:
	static CTerrain* Create();

	void SetFilePath(const wstring& wstrFilePath);

private:
	vector<CTile *>  m_vecTile2;
};

