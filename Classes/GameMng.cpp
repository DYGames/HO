#include "stdafx.h"

GameMng* GameMng::_instance = NULL;
GameMng* GameMng::getInstance()
{
	if (!_instance)
		_instance = new GameMng;
	return _instance;
}

GameMng::GameMng()
{
	_curwater = _maxwater = 100;
	_curfood = _maxfood = 100;
	_curmedicine = _maxmedicine = 100;
	_curmanpower = _maxmanpower = 100;
}