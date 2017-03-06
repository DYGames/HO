#pragma once

#include "stdafx.h"

class GameOver : public Layer
{
private:

public:
	static Scene* createScene();

	virtual bool init();

	void gotomain();

	CREATE_FUNC(GameOver);
};