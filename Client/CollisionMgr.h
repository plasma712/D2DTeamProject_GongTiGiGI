#pragma once
class CGameObject;
class CTile;
class CPlayer;


class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
public:
	CCollisionMgr();
	~CCollisionMgr();

	//���� Ÿ��, �÷��̾�, �浹���̵�

	CollPair TileCollision2(vector<CTile*>* vtile, CPlayer * player);



};

