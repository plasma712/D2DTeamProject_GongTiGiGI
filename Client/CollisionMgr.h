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

	//벡터 타일, 플레이어, 충돌아이디

	CollPair TileCollision2(vector<CTile*>* vtile, CPlayer * player);



};

