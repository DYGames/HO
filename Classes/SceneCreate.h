#pragma once
#include <cocos2d.h>
USING_NS_CC;

template<class Type>
class CreateScene
{
public:
	Type* create()
	{

	}

	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Type::create();
		scene->addChild(layer);

		return scene;
	}
};