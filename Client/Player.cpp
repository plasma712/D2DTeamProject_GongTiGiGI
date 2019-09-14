#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "PlayerEffect.h"
#include "Tile.h"
#include "Alarm.h"

int CPlayer::stagecount = 0;

CPlayer::CPlayer()
	:CTextureObject(),GroundCheck(false) , m_fSpeedX(0.f) , m_fJumpForce(0.f)
	, m_fJumpAcc(0.f) , m_fGroundY(0.f) , CollCheck(false) , m_fSpeedY(0.f)
	, ArrowActive(false)
{
	this->LoadTextureObject(L"Player", L"Player", 0);
	NULL_CHECK(pTexInfo);
}


CPlayer::~CPlayer()
{
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Rect()
{
	m_tRect.left = static_cast<LONG>(tileInfo.vPos.x - 32 * 0.5f);
	m_tRect.top = static_cast<LONG>(tileInfo.vPos.y - 32 * 0.5f);
	m_tRect.right = static_cast<LONG>(tileInfo.vPos.x + 32 * 0.5f);
	m_tRect.bottom = static_cast<LONG>(tileInfo.vPos.y + 32 * 0.5f);
}



void CPlayer::Parabola()
{
	if (alarm.Alarm_check())
	{
		m_pPlayerEffect = CPlayerEffect::Create(tileInfo);
		//m_pPlayerEffectVec.push_back(m_pPlayerEffect);
		m_pPlayerEffectLst.push_back(m_pPlayerEffect);
	}
}


void CPlayer::SetGroundCheck(bool b)
{
	GroundCheck = b;

	if (GroundCheck)
	{

	}
}


void CPlayer::Physics()
{


	//#define NORMAL_TILE	1
	//#define BOMB_TILE	2
	//#define JUMP_TILE	3
	//#define LEFT_TILE	4
	//#define RIGHT_TILE	5
	//#define BROKEN_TILE	6
	//#define BLACK_TILE	7
	if (!ArrowActive)
	{
		if (CollCheck)
		{
			CollCheck = false;
			m_fSpeedY = 0.f;

			if (m_collpair.second->GetTileInfo().byDrawID == BROKEN_TILE)
			{
				//	m_collpair.second->GetTileInfo().byDrawID = BLACK_TILE;
				m_collpair.second->SetDrawID(BLACK_TILE);
			}
			else if (m_collpair.second->GetTileInfo().byDrawID == JUMP_TILE)
			{
				if (m_collpair.first == Left ||
					m_collpair.first == Right)
				{
					m_fSpeedX *= -1;	// 벽에 충돌시 X속도 반전
					cout << "LR" << endl;
				}
				else if (m_collpair.first == Up)
				{
					m_fSpeedY = -1;	//바닥에 부딫혔을때..
					cout << "UP" << endl;
				}
				else if (m_collpair.first == Down)
				{
					m_fSpeedY = -m_fJumpForce*1.5;	//바닥에 부딫혔을때..
					cout << "Down" << endl;
				}
			}
			else if (m_collpair.second->GetTileInfo().byDrawID == NEXTSTAGE_TILE)
			{
				StageCollsion = true;
			}
			else if (m_collpair.second->GetTileInfo().byDrawID == RIGHT_TILE)
			{
				tileInfo.vPos.x = m_collpair.second->GetTileInfo().vPos.x + TILECX;
				tileInfo.vPos.y = m_collpair.second->GetTileInfo().vPos.y;
				Arrow.Alarm_set(1.f);
				ArrowActive = true;
			}

			else//노멀타일
			{
				if (m_collpair.first == Left ||
					m_collpair.first == Right)
				{
					m_fSpeedX *= -1;	// 벽에 충돌시 X속도 반전
					cout << "LR" << endl;
				}
				else if (m_collpair.first == Up)
				{

					m_fSpeedY = -1;	//바닥에 부딫혔을때..
					cout << "UP" << endl;
				}
				else if (m_collpair.first == Down)
				{
					m_fSpeedY = -m_fJumpForce;	//바닥에 부딫혔을때..
					cout << "Down" << endl;
				}
			}
		}

		if (!CollCheck)		//중력적용
		{
			m_fSpeedY += 20.f;
		}

		LimitSpeed();
	}
	else
	{
		if (Arrow.Alarm_check() || CollCheck)
			ArrowActive = false;

		m_fSpeedY = 0;
		m_fSpeedX = 200.f;

	}

	tileInfo.vPos.y += m_fSpeedY* m_pTimeMgr->GetDeltaTime()*2;
	tileInfo.vPos.x += m_fSpeedX* m_pTimeMgr->GetDeltaTime()*2;
}



TILE_INFO CPlayer::GetPlayerPos()
{
	return tileInfo;
}

void CPlayer::LstDelete()
{
	m_pPlayerEffectLst.pop_front();
}

void CPlayer::SetColCheck(bool set)
{
	CollCheck = set;
}

void CPlayer::GetPreCrashPointPos()
{
	PreCrashPointPos = tileInfo.vPos;
}

void CPlayer::GetCrashPointCurPlayerPos()
{
}

bool CPlayer::GetStageCollsion()
{
	return StageCollsion;
}

void CPlayer::SetColData(CollPair _cp)
{
	CollCheck = true;
	m_collpair.first = _cp.first;
	m_collpair.second = _cp.second;
}

int CPlayer::DoUpdate()
{
	//m_fSpeedX = 0.f;

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	{
		m_fSpeedX -= 3.f;
		//m_pPlayerEffect = CPlayerEffect::Create(tileInfo);
		//m_pPlayerEffectLst.push_back(m_pPlayerEffect);
	}
	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	{
		m_fSpeedX += 3.f;
		//m_pPlayerEffect = CPlayerEffect::Create(tileInfo);
		//m_pPlayerEffectLst.push_back(m_pPlayerEffect);
	}

	Parabola();
	Physics();


	return NO_EVENT;
}

void CPlayer::DoLateUpdate()
{
}

void CPlayer::DoRender()
{
	Rect();

	list<CGameObject*>::iterator iter;
	if (m_pPlayerEffectLst.size() > 10)
	{
		LstDelete();
	}

	for (iter = m_pPlayerEffectLst.begin(); iter != m_pPlayerEffectLst.end(); ++iter)
	{
		(*iter)->Render();
	}
}

HRESULT CPlayer::DoInitialize()
{
	tileInfo.vPos = { 70.f,200.f,0.f };
	tileInfo.vSize = { 0.010f,0.010f,0.f };
	m_fSpeedX = 0.f;
	m_fJumpForce = 350.f;
	m_fGroundY = 300.f;

	m_pPlayerEffect = CPlayerEffect::Create(tileInfo);
	alarm.Alarm_set(0.01, true);

	StageCollsion = false;
	//PlayerEffectNumber = 0;
	return S_OK;
}


void CPlayer::LimitSpeed()
{
	if (abs(m_fSpeedY) > 10.f)	//속도 제한
	{
		if (m_fSpeedY < 0)
			m_fSpeedY++;
		else
			m_fSpeedY--;
	}

	if (abs(m_fSpeedX) > 8.f)
	{
		if (m_fSpeedX < 0)
			m_fSpeedX++;
		else
			m_fSpeedX--;
	}


	if (m_fSpeedX < 0)
		m_fSpeedX += 0.5f * m_pTimeMgr->GetDeltaTime();
	else
		m_fSpeedX -= 0.5f * m_pTimeMgr->GetDeltaTime();

	if (abs(m_fSpeedX) <= 0.1f)
		m_fSpeedX = 0.0f;
}


