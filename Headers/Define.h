#pragma once

#ifndef __DEFINE_H__

#define WINCX 800
#define WINCY 600

#define TILECX 32
#define TILECY 32

#define MIN_STR 64
#define MID_STR 128
#define MAX_STR 256

#define NO_EVENT		0
#define DEAD_OBJ		1
#define CHANGE_SCENE	2

#define NULL_CHECK(ptr)	\
if(nullptr == (ptr)) { return; }

#define NULL_CHECK_MSG(ptr, msg)	\
if(nullptr == (ptr)) { MessageBox(0, msg, L"System Error", MB_OK); return; }

#define NULL_CHECK_RETURN(ptr, val)	\
if(nullptr == (ptr)) { return val; }

#define NULL_CHECK_MSG_RETURN(ptr, msg, val)	\
if(nullptr == (ptr)) { MessageBox(0, msg, L"System Error", MB_OK); return val; }

#define FAILED_CHECK(hr)	\
if(FAILED(hr)) { return; }

#define FAILED_CHECK_MSG(hr, msg)	\
if(FAILED(hr)) { MessageBox(0, msg, L"System Error", MB_OK); return; }

#define FAILED_CHECK_RETURN(hr, val)	\
if(FAILED(hr)) { return val; }

#define FAILED_CHECK_MSG_RETURN(hr, msg, val)	\
if(FAILED(hr)) { MessageBox(0, msg, L"System Error", MB_OK); return val; }

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName&);				\
	ClassName& operator=(const ClassName&);

#define DECLARE_SINGLETON(ClassName)			\
		NO_COPY(ClassName)						\
public:											\
	static ClassName* GetInstance();			\
	void DestroyInstance();						\
private:										\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()				\
{												\
	if(nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
void ClassName::DestroyInstance()				\
{												\
	if(m_pInstance)								\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}


#define NONE_TILE	0
#define NORMAL_TILE	1
#define BOMB_TILE	2
#define JUMP_TILE	3
#define NEXTSTAGE_TILE	4
#define RIGHT_TILE	5
#define BROKEN_TILE	6
#define BLACK_TILE	7



#define __DEFINE_H__
#endif