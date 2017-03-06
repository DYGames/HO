#include "stdafx.h"

static int getRandom(int min, int max)
{
	random_device rad;
	mt19937 xEngine(rad());
	std::uniform_int_distribution<> xdist(min, max);
	return xdist(xEngine);
}

void EventMng::init(Node* parent, Interface* interfacee)
{
	_parent = parent;
	_interface = interfacee;

	_lifeLayer = Layer::create();
	parent->getParent()->addChild(_lifeLayer);

	for (int i = 0; i < 5; i++)
		_dt[i] = 0;

	_event_Type[0] = "FOOD SHORTAGE";
	_event_Type[1] = "WATER SHORTAGE";
	_event_Type[2] = "WAR";
	_event_Type[3] = "PLAGUE";
	_event_Type[4] = "TERROR";

	_country[0] = "NORTH KOREA";
	_country[1] = "SOMALIA";
	_country[2] = "KENYA";
	_country[3] = "BANGLADESH";
	_country[4] = "AFGHANISTAN";
	_country[5] = "SYRIA";
	_country[6] = "IRAQ";
	_country[7] = "ZAMBIA";
	_country[8] = "CONGO";
	_country[9] = "PARIS";
	_country[10] = "UK";
	_country[11] = "DENMARK";
	_country[12] = "BELGIUM";
	_country[13] = "USA";
	_country[14] = "BRAZIL";
	_country[15] = "MAXICO";
	
	_iconpos.insert(map<string, Vec2>::value_type(_country[0], Vec2(536, 420)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[1], Vec2(232, 720 - 444)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[2], Vec2(186, 720 - 488)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[3], Vec2(364, 720 - 343)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[4], Vec2(301, 720 - 334)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[5], Vec2(359, 420)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[6], Vec2(253, 720 - 326)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[7], Vec2(123, 720 - 395)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[8], Vec2(156, 720 - 536)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[9], Vec2(120, 720 - 307)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[10], Vec2(136, 720 - 230)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[11], Vec2(159, 720 - 242)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[12], Vec2(243, 720 - 261)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[13], Vec2(959, 720 - 280)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[14], Vec2(1070, 720 - 523)));
	_iconpos.insert(map<string, Vec2>::value_type(_country[15], Vec2(1027, 720 - 441)));

	_time[0] = getRandom(10, 15);
	_time[1] = getRandom(10, 15);
	_time[2] = getRandom(15, 20);
	_time[3] = getRandom(20, 25);
	_time[4] = getRandom(25, 30);

	memset(_onPin, false, sizeof(_onPin));

	refreshLife();
}

void EventMng::update(float dt)
{
	for (int i = 0; i < 5; i++)
	{
		_dt[i] += dt;
	}
	if (_time[0] <= _dt[0]){
		eventOccurred(EVENT_TYPE::FOOD, getRandom(0, 5));
		_time[0] = getRandom(10, 15);
		_dt[0] = 0;
	}
	if (_time[1] <= _dt[1]){
		eventOccurred(EVENT_TYPE::WATER, getRandom(0, 5));
		_time[1] = getRandom(10, 15);
		_dt[1] = 0;
	}
	if (_time[2] <= _dt[2]){
		eventOccurred(EVENT_TYPE::WAR, getRandom(5, 6));
		_time[2] = getRandom(15, 20);
		_dt[2] = 0;
	}
	if (_time[3] <= _dt[3]){
		eventOccurred(EVENT_TYPE::PLAGUE, getRandom(7, 8));
		_time[3] = getRandom(20, 25);
		_dt[3] = 0;
	}
	if (_time[4] <= _dt[4]){
		eventOccurred(EVENT_TYPE::TERROR, getRandom(9, 15));
		_time[4] = getRandom(25, 30);
		_dt[4] = 0;
	}
}

void EventMng::eventOccurred(int eventtype, int country)
{
	if (_onPin[country])
		return;

	Vec2 pos = _iconpos.at(_country[country]);

	pin::Sprite* icon = pin::Sprite::create(_event_Type[eventtype] + ".png");
	icon->setName(_country[country]);
	icon->setPosition(pos);
	icon->setAnchorPoint(Vec2(0.5, 0));
	icon->On();
	icon->runAction(Sequence::create(
		DelayTime::create(getRandom(5, 7)),
		CallFuncN::create(CC_CALLBACK_0(EventMng::removePin, this, country, true)),
		NULL
		));
	_parent->addChild(icon);

	_onPin[country] = true;

	HelpEvent eventt;
	eventt.numcountry = country;
	eventt.country = _country[country];
	eventt.eventtype = _event_Type[eventtype];
	
	switch (eventtype)
	{
	case FOOD:
		eventt.need1 = getRandom(19, 28);
		eventt.need2 = getRandom(10, 18);
		break;
	case WATER:
		eventt.need1 = getRandom(19, 28);
		eventt.need2 = getRandom(10, 18);
		break;
	case WAR:
		eventt.need1 = getRandom(22, 32);
		eventt.need2 = getRandom(13, 23);
		break;
	case PLAGUE:
		eventt.need1 = getRandom(25, 40);
		eventt.need2 = getRandom(15, 27);
		break;
	case TERROR:
		eventt.need1 = getRandom(28, 37);
		eventt.need2 = getRandom(17, 30);
		break;
	}

	_hevent.insert(map<string, HelpEvent>::value_type(_country[country], eventt));

	string str = _event_Type[eventtype] + " occurred at " + _country[country];
	CCLOG("%s", str.c_str());
}

void EventMng::opentooltip(string country)
{
	if (_tooltipon)
		return;

	string mainneed;
	string subneed;

	_tooltip = pin::Sprite::create("tooltip.png");
	_tooltip->setPosition(_iconpos.at(country) + Vec2(-5, 104));
	_tooltip->On();
	_tooltip->setAnchorPoint(Vec2(0.5, 0));
	_parent->getParent()->addChild(_tooltip);

	auto hevent = _hevent.at(country);

	Label* label1 = Label::create(hevent.country.c_str(), "", 15);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(Vec2(110, 155));

	Label* label2 = Label::create(hevent.eventtype.c_str(), "", 15);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(Vec2(110, 135));

	if (hevent.eventtype == "WATER SHORTAGE")
	{
		hevent.mainneed = "WATER";
		hevent.subneed = "FOOD";
	}
	else if (hevent.eventtype == "FOOD SHORTAGE")
	{
		hevent.mainneed = "FOOD";
		hevent.subneed = "WATER";
	}
	else if (hevent.eventtype == "WAR")
	{
		hevent.mainneed = "MANPOWER";
		hevent.subneed = "MEDICINE";
	}
	else if (hevent.eventtype == "PLAGUE")
	{
		hevent.mainneed = "MEDICINE";
		hevent.subneed = "MANPOWER";
	}
	else if (hevent.eventtype == "TERROR")
	{
		hevent.mainneed = "MANPOWER";
		hevent.subneed = "MEDICINE";
	}

	Label* label3 = Label::create(String::createWithFormat("%s : %d\n%s : %d", hevent.mainneed.c_str(), hevent.need1, hevent.subneed.c_str(), hevent.need2)->getCString(), "", 15);
	label3->setColor(Color3B::BLACK);
	label3->setPosition(Vec2(110, 105));

	_tooltip->addChild(label1);
	_tooltip->addChild(label2);
	_tooltip->addChild(label3);

	MenuItemImage* help = MenuItemImage::create("help.png", "help.png", CC_CALLBACK_1(EventMng::menucallback, this, hevent));
	help->setPosition(Vec2(110, 60));
	Menu* menu = Menu::create(help, NULL);
	menu->setPosition(Vec2());
	_tooltip->addChild(menu);

	_tooltipon = true;
}

void EventMng::closetooltip()
{
	if (!_tooltipon)
		return;

	_tooltip->Off();
	_tooltipon = false;
}
void EventMng::menucallback(Ref* sender, HelpEvent hevent)
{
	if (hevent.mainneed == "WATER")
	{
		GameData->_curmanpower += getRandom(5, 10);
		if (GameData->_curmanpower > GameData->_maxmanpower)
			GameData->_maxmanpower = GameData->_curmanpower;

		if (GameData->_curwater > hevent.need1)
			GameData->_curwater -= hevent.need1;
		else
		{
			GameData->_curwater = 0;
			_life--; 
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Water", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.subneed == "WATER")
	{
		GameData->_curmanpower += getRandom(5, 10);
		if (GameData->_curmanpower > GameData->_maxmanpower)
			GameData->_maxmanpower = GameData->_curmanpower;

		if (GameData->_curwater > hevent.need2)
			GameData->_curwater -= hevent.need2;
		else
		{
			GameData->_curwater = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Water", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.mainneed == "FOOD")
	{
		GameData->_curmedicine += getRandom(5, 10);
		if (GameData->_curmedicine > GameData->_maxmedicine)
			GameData->_maxmedicine = GameData->_curmedicine;

		if (GameData->_curfood > hevent.need1)
			GameData->_curfood -= hevent.need1;
		else
		{
			GameData->_curfood = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Food", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.subneed == "FOOD")
	{
		GameData->_curmedicine += getRandom(5, 10);
		if (GameData->_curmedicine > GameData->_maxmedicine)
			GameData->_maxmedicine = GameData->_curmedicine;
		if (GameData->_curfood > hevent.need2)
			GameData->_curfood -= hevent.need2;
		else
		{
			GameData->_curfood = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Food", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.mainneed == "MANPOWER")
	{
		GameData->_curwater += getRandom(5, 10);
		if (GameData->_curwater > GameData->_maxwater)
			GameData->_maxwater = GameData->_curwater;
		if (GameData->_curmanpower > hevent.need1)
			GameData->_curmanpower -= hevent.need1;
		else
		{
			GameData->_curmanpower = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Manpower", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.subneed == "MANPOWER")
	{
		GameData->_curwater += getRandom(5, 10);
		if (GameData->_curwater > GameData->_maxwater)
			GameData->_maxwater = GameData->_curwater;
		if (GameData->_curmanpower > hevent.need2)
			GameData->_curmanpower -= hevent.need2;
		else
		{
			GameData->_curmanpower = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Manpower", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.mainneed == "MEDICINE")
	{
		GameData->_curfood += getRandom(5, 10);
		if (GameData->_curfood > GameData->_maxfood)
			GameData->_maxfood = GameData->_curfood;
		if (GameData->_curmedicine > hevent.need1)
			GameData->_curmedicine -= hevent.need1;
		else
		{
			GameData->_curmedicine = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Medicine", 1);
			_parent->getParent()->addChild(startnews);
		}
	}
	if (hevent.subneed == "MEDICINE")
	{
		GameData->_curfood += getRandom(5, 10);
		if (GameData->_curfood > GameData->_maxfood)
			GameData->_maxfood = GameData->_curfood;
		if (GameData->_curmedicine > hevent.need2)
			GameData->_curmedicine -= hevent.need2;
		else
		{
			GameData->_curmedicine = 0;
			_life--;
			news::Sprite* startnews = news::Sprite::create();
			startnews->On("Lose Life Due to Not Enough Medicine", 1);
			_parent->getParent()->addChild(startnews);
		}
	}

	refreshLife();

	removePin(hevent.numcountry, false);
	
	_interface->SetWater(GameData->_curwater, GameData->_maxwater);
	_interface->SetFood(GameData->_curfood, GameData->_maxfood);
	_interface->SetMedicine(GameData->_curmedicine, GameData->_maxmedicine);
	_interface->SetHuman(GameData->_curmanpower, GameData->_maxmanpower);
}

void EventMng::removePin(int numc, bool force)
{
	if (force){
		news::Sprite* startnews = news::Sprite::create();
		startnews->On("Lose Life Due to Pin autoremoved", 1);
		_parent->getParent()->addChild(startnews);
		_life--;
		refreshLife();
	}
	closetooltip();
	_onPin[numc] = false;
	if (_parent->getChildByName(_country[numc]))
		((pin::Sprite*)_parent->getChildByName(_country[numc]))->Off();
}

void EventMng::refreshLife()
{
	_lifeLayer->removeAllChildrenWithCleanup(true);
	Sprite* back = Sprite::create("lifebar.png");
	back->setPosition(Vec2(155, 680));
	_lifeLayer->addChild(back);


	for (int i = 0; i < _life; i++)
	{
		pin::Sprite* life = pin::Sprite::create("lifekey.png");
		life->setPosition(Vec2(48 + 36 * i, 680));
		life->On();
		_lifeLayer->addChild(life);
	}

	if (_life <= 0)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameOver::createScene()));
	}
}