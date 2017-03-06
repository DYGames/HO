#include "stdafx.h"

Scene* GameOver::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOver::create();

	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
		return false;

	Sprite* spr = Sprite::create("gameover.png");
	spr->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(spr);

	this->runAction(Sequence::create(
		DelayTime::create(6),
		CallFuncN::create(CC_CALLBACK_0(GameOver::gotomain, this)),
		NULL
		));

	return true;
}

void GameOver::gotomain()
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, MainMenu::createScene()));
}