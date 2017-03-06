#pragma once

#include "stdafx.h"

class GameMng
{
private:
	static GameMng* _instance;

public:
	int _curwater;
	int _curfood;
	int _curmedicine;
	int _curmanpower;

	int _maxwater;
	int _maxfood;
	int _maxmedicine;
	int _maxmanpower;
public:
	static GameMng* getInstance();
	GameMng();
};