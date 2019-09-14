#pragma once
class CAlarm
{
private:
	bool isLoop;
	float Times;
	float AccmulTime;
public:
	CAlarm();
	~CAlarm();

public:
	void Alarm_set(float Time , bool loop = false);
	bool Alarm_check();
	void Alarm_Stop();

private:
	bool	Alarm_On;
};