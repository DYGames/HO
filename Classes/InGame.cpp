#include "stdafx.h"

static int getRandom(int min, int max)
{
	random_device rad;
	mt19937 xEngine(rad());
	std::uniform_int_distribution<> xdist(min, max);
	return xdist(xEngine);
}

Scene* InGame::createScene()
{
	auto scene = Scene::create();

	auto layer = InGame::create();

	scene->addChild(layer);

	return scene;
}

bool InGame::init()
{
	if (!Layer::init())
		return false;

	srand(time(NULL));

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	Sprite* worldmap = Sprite::create("worldmap.png");
	worldmap->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(worldmap);

	_pinLayer = Layer::create();
	this->addChild(_pinLayer);

	_interface = Interface::create(this);
	_interface->Init();
	this->addChild(_interface);

	_eventMng = new EventMng;
	_eventMng->init(_pinLayer, _interface);

	cloud::Layer* cloudlayer = cloud::Layer::create();
	cloudlayer->On();
	this->addChild(cloudlayer);

	this->runAction(Sequence::create(
		DelayTime::create(1),
		CallFunc::create([=](){
		news::Sprite* startnews = news::Sprite::create();
		startnews->On("Hello, Wait For The First Event", 1);
		this->addChild(startnews);
	}), NULL));

	pin::Sprite* diplo = pin::Sprite::create("diplo.png");
	diplo->setPosition(Vec2(55, 55));
	diplo->setVisible(true);
	diplo->setTag(99);
	this->addChild(diplo);

	schedule(schedule_selector(InGame::EventMngUpdate));
	schedule(schedule_selector(InGame::resourceFill), 2);

	return true;
}

void InGame::resourceFill(float dt)
{
	GameData->_curwater += getRandom(1, 3);
	if (GameData->_curwater >= GameData->_maxwater)
		GameData->_curwater = GameData->_maxwater;
	GameData->_curfood += getRandom(1, 3);
	if (GameData->_curfood >= GameData->_maxfood)
		GameData->_curfood = GameData->_maxfood;
	GameData->_curmanpower += getRandom(1, 3);
	if (GameData->_curmanpower >= GameData->_maxmanpower)
		GameData->_curmanpower = GameData->_maxmanpower;
	GameData->_curmedicine += getRandom(1, 3);
	if (GameData->_curmedicine >= GameData->_maxmedicine)
		GameData->_curmedicine = GameData->_maxmedicine;

	_interface->SetWater(GameData->_curwater, GameData->_maxwater);
	_interface->SetFood(GameData->_curfood, GameData->_maxfood);
	_interface->SetHuman(GameData->_curmanpower, GameData->_maxmanpower);
	_interface->SetMedicine(GameData->_curmedicine, GameData->_maxmedicine);
}

void InGame::EventMngUpdate(float dt)
{
	_eventMng->update(dt);
}

void InGame::menucallback(Ref* sender)
{

}

bool InGame::onTouchBegan(Touch* touch, Event*)
{
	Vec2 location = touch->getLocation();

	for (auto it : _pinLayer->getChildren())
	{
		if (it->getBoundingBox().containsPoint(location))
		{
			_eventMng->closetooltip();
			_eventMng->opentooltip(it->getName());
			CCLOG("%s", it->getName().c_str());
			return true;
		}
	}

	_interface->SetOnTouch(touch);
	
	if (getChildByTag(99)->getBoundingBox().containsPoint(location))
	{
		((pin::Sprite*)getChildByTag(99))->On();

		GameData->_curfood -= getRandom(0, 50);
		GameData->_curmanpower -= getRandom(0, 50);
		GameData->_curmedicine -= getRandom(0, 50);
		GameData->_curwater -= getRandom(0, 50);

		if (GameData->_curfood <= 0)
			GameData->_curfood = 0;
		if (GameData->_curmanpower <= 0)
			GameData->_curmanpower = 0;
		if (GameData->_curmedicine <= 0)
			GameData->_curmedicine = 0;
		if (GameData->_curwater <= 0)
			GameData->_curwater = 0;

		GameData->_curfood += getRandom(0, 50);
		GameData->_curmanpower += getRandom(0, 50);
		GameData->_curmedicine += getRandom(0, 50);
		GameData->_curwater += getRandom(0, 50);

		if (GameData->_curfood >= 100)
			GameData->_curfood = 100;
		if (GameData->_curmanpower >= 100)
			GameData->_curmanpower = 100;
		if (GameData->_curmedicine >= 100)
			GameData->_curmedicine = 100;
		if (GameData->_curwater >= 100)
			GameData->_curwater = 100;

		news::Sprite* startnews = news::Sprite::create();
		startnews->On("Diplomacy Success", 1);
		this->addChild(startnews);

		_interface->SetWater(GameData->_curwater, GameData->_maxwater);
		_interface->SetFood(GameData->_curfood, GameData->_maxfood);
		_interface->SetHuman(GameData->_curmanpower, GameData->_maxmanpower);
		_interface->SetMedicine(GameData->_curmedicine, GameData->_maxmedicine);
	}

	{
		_eventMng->closetooltip();
	}

	return true;
}