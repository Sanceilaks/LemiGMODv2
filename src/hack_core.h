#pragma once




class CHackCore
{
private:
	void* dll;
public:
	void init(void* dll);
};

extern CHackCore* HackCore;