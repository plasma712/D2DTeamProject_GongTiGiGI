#include "stdafx.h"
#include "Terrain.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "GameObject.h"

CTerrain::CTerrain()
	:m_bIsData(false), m_pPlayer(nullptr)
	, CollMgr(CCollisionMgr::GetInstance())
{
}


CTerrain::~CTerrain()
{
	Release();
}

int CTerrain::Update()
{
	CGameObject::LateInit();

	IsPicking();


	if (m_pKeyMgr->KeyDown(KEY_A))
		LoadTile(L"../Texture/MapData/MapData.dat");
	if (m_pKeyMgr->KeyDown(KEY_S))
		SaveTile(L"../Texture/MapData/MapData.dat");


	////for (auto& tiles : m_vecTile2)
	//for (size_t i = 0; i < m_vecTile2.size(); i++)
	//{
	//	//drawID 는 BYTE 를 사용하기 때문에 0을 인식하지 못함 - 타일텍스쳐로 0번에 한개 더 추가해놓음
	//	//if (1== m_vecTile2[i]->GetTileInfo().byDrawID)//이거 지우고 사용하시면 됩니다
	//	
	//	int result = CollMgr->TileCollision(m_vecTile2[i], m_pPlayer);
	//	if (result <= BLACK_TILE)
	//	{
	//		m_vecTile2[i]->EnterTrigger(m_pPlayer);
	//	}
	//}

	CollPair temp= CollMgr->TileCollision2(&m_vecTile2,m_pPlayer);

	if (temp.second != nullptr)
	{
		m_pPlayer->SetColData(temp);
		temp.second->EnterTrigger(m_pPlayer);
	}

	return NO_EVENT;
}

void CTerrain::LateUpdate()
{
}

void CTerrain::Render()
{
	//for (size_t i = 0; i < m_vecTile.size(); i++)
	//{
	//	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(
	//		L"Terrain",
	//		L"Tile",
	//		m_vecTile[i]->byDrawID);

	//	m_pDeviceMgr->GetSprite()->Draw(
	//		pTexInfo->pTexture,
	//		nullptr,
	//		&D3DXVECTOR3(pTexInfo->tImgInfo.Width*0.5f, pTexInfo->tImgInfo.Height*0.5f, 0.f),
	//		&m_vecTile[i]->vPos,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	for (auto& obj : m_vecTile2)
	{
		obj->Render();
	}
}

void CTerrain::SetPlayerPointer(CPlayer * _player)
{
	m_pPlayer = _player;
}

HRESULT CTerrain::Initialize()
{
	m_pTextureMgr->LoadTexture(
		CTextureMgr::MULTI_TEXTURE,
		L"../Texture/Bound/%d.png",
		L"Terrain", L"Tile", 8);

	int iColEnd = WINCX / TILECX + 2;
	int iRowEnd = WINCY / TILECY + 2;

	for (int iRow = 0; iRow < iRowEnd; iRow++)
	{
		for (int iCol = 0; iCol < iColEnd; iCol++)
		{

			CTile * pTile = new CTile;
			pTile->SetDrawID(BLACK_TILE);
			pTile->SetOption(0);
			pTile->SetSize(D3DXVECTOR3(1.f, 1.f, 0.f));
			pTile->Translate(D3DXVECTOR3(
				TILECX*0.5f + iCol*TILECX,
				TILECY*0.5f + iRow*TILECY,
				0.f
			));
			pTile->Initialize();
			m_vecTile2.push_back(pTile);
			//TILE_INFO* pTile = new TILE_INFO;
			//pTile->byDrawID = BLACK_TILE;
			//pTile->byOption = 0;
			//pTile->vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
			//pTile->vPos = D3DXVECTOR3(
			//TILECX*0.5f + iCol*TILECX,
			//TILECY*0.5f + iRow*TILECY, 0, 0f);
			//m_vecTile.push_back(pTile);
		}
	}


	return S_OK;
}

HRESULT CTerrain::LateInit()
{
	LoadTile(m_wstrFilePath);
	return S_OK;
}

void CTerrain::Release()
{
	for (size_t i = 0; i < m_vecTile2.size(); i++)
		SafeDelete(m_vecTile2[i]);

	m_vecTile2.clear();
	m_vecTile2.shrink_to_fit();
}

bool CTerrain::IsPicking()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//for (size_t i = 0; i < m_vecTile.size(); i++)
	//{
	//	//포인트가 타일 안에 있다면
	//	if (CheckInOut(pt, i))
	//	{
	//		m_vecTile[i]->byDrawID += 1;

	//		if (m_vecTile[i]->byDrawID >= 6)
	//			m_vecTile[i]->byDrawID = 0;
	//	}
	//}
	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
	{
		for (size_t i = 0; i < m_vecTile2.size(); i++)
		{
			//포인트가 타일 안에 있다면
			if (CheckInOut(pt, (int)i))
			{
				if (m_vecTile2[i]->GetTileInfo().byDrawID >= 6)
					m_vecTile2[i]->SetDrawID(1);
				else
					m_vecTile2[i]->SetDrawID(m_vecTile2[i]->GetTileInfo().byDrawID + 1);
			}
		}
	}

	if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
	{
		for (size_t i = 0; i < m_vecTile2.size(); i++)
		{
			//포인트가 타일 안에 있다면
			if (CheckInOut(pt, (int)i))
				m_vecTile2[i]->SetDrawID(BLACK_TILE);
		}
	}
	

	return true;
}

bool CTerrain::CheckInOut(const POINT & pt, const int iIndex)
{
	const TEX_INFO* pTexInfo =
		m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_vecTile2[iIndex]->GetTileInfo().byDrawID);

	//float left = m_vecTile[iIndex]->vPos.x - pTexInfo->tImgInfo.Width*0.5f;
	//float right = m_vecTile[iIndex]->vPos.x + pTexInfo->tImgInfo.Width*0.5f;
	//float top = m_vecTile[iIndex]->vPos.y - pTexInfo->tImgInfo.Height*0.5f;
	//float bottom = m_vecTile[iIndex]->vPos.y + pTexInfo->tImgInfo.Height*0.5f;

	float left = m_vecTile2[iIndex]->GetTileInfo().vPos.x - pTexInfo->tImgInfo.Width*0.5f;
	float right = m_vecTile2[iIndex]->GetTileInfo().vPos.x + pTexInfo->tImgInfo.Width*0.5f;
	float top = m_vecTile2[iIndex]->GetTileInfo().vPos.y - pTexInfo->tImgInfo.Height*0.5f;
	float bottom = m_vecTile2[iIndex]->GetTileInfo().vPos.y + pTexInfo->tImgInfo.Height*0.5f;


	if (pt.x >= left &&
		pt.x <= right &&
		pt.y >= top &&
		pt.y <= bottom)
		return true;
	else
		return false;
}

void CTerrain::SaveTile(const wstring& wstrFilePath)
{
	/*HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Save Tile Failed", L"System Error", MB_OK);
		return;
	}

	DWORD dwBytes = 0;

	for (size_t i = 0; i < m_vecTile.size(); i++)
		WriteFile(hFile, m_vecTile[i], sizeof(TILE_INFO), &dwBytes, nullptr);

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Save Tile Success", L"System Ok", MB_OK);*/
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Save Tile Failed", L"System Error", MB_OK);
		return;
	}

	DWORD dwBytes = 0;

	for (size_t i = 0; i < m_vecTile2.size(); i++)
		WriteFile(hFile, &m_vecTile2[i]->GetTileInfo(), sizeof(TILE_INFO), &dwBytes, nullptr);


	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Save Tile Success", L"System Ok", MB_OK);
}

void CTerrain::LoadTile(const wstring& wstrFilePath)
{
	/*HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Tile Failed", L"System Error", MB_OK);
		return;
	}

	if (!m_vecTile.empty())
	{
		for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
		m_vecTile.clear();
		m_vecTile.shrink_to_fit();
	}

	DWORD dwBytes = 0;
	TILE_INFO tTileInfo = {};

	while (1)
	{
		ReadFile(hFile, &tTileInfo, sizeof(TILE_INFO), &dwBytes, nullptr);

		if (0 == dwBytes)
			break;

		m_vecTile.push_back(new TILE_INFO(tTileInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Load Tile Success", L"System Ok", MB_OK);*/
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Tile Failed", L"System Error", MB_OK);
		return;
	}

	if (!m_vecTile2.empty())
	{
		for_each(m_vecTile2.begin(), m_vecTile2.end(), SafeDelete<CTile*>);
		m_vecTile2.clear();
		m_vecTile2.shrink_to_fit();
	}

	DWORD dwBytes = 0;
	TILE_INFO tTileInfo = {};
	while (1)
	{
		ReadFile(hFile, &tTileInfo, sizeof(TILE_INFO), &dwBytes, nullptr);


		if (0 == dwBytes)
			break;

		CTile* pTile = new CTile;
		
		pTile->SetDrawID(tTileInfo.byDrawID);
		pTile->SetOption(tTileInfo.byOption);
		pTile->SetSize(tTileInfo.vSize);
		pTile->Translate(tTileInfo.vPos);

		m_vecTile2.push_back(pTile);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Load Tile Success", L"System Ok", MB_OK);
}

CTerrain* CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTerrain::SetFilePath(const wstring & wstrFilePath)
{
	m_wstrFilePath = wstrFilePath;
}


