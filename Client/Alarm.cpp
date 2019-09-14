#include "stdafx.h"


CAlarm::CAlarm()
	:Alarm_On(false) , isLoop(false) , AccmulTime(0.f)
{

}


CAlarm::~CAlarm()
{
}

void CAlarm::Alarm_set(float Time, bool loop)
{
	isLoop = loop;
	Times = Time;
	AccmulTime = 0.f;
	Alarm_On = true;
}

bool CAlarm::Alarm_check()
{
	AccmulTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if (Alarm_On) 
	{
		if (AccmulTime >= Times)
		{
			if (isLoop)	//루프일경우 자동으로 Time셋.
			{
				Alarm_On = true;
				Alarm_set(Times, true);
			}
			else
			{
				Alarm_On = false;
			}
			return true;
		}
	}
	return false;
}

void CAlarm::Alarm_Stop()
{
	Alarm_On = false;
}
