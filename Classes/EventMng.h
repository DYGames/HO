#pragma once

#include "stdafx.h"

namespace pin
{
	class Sprite : public cocos2d::Sprite
	{
	public:
		static pin::Sprite* pin::Sprite::create(const std::string& filename)
		{
			pin::Sprite *sprite = new (std::nothrow) pin::Sprite();
			if (sprite && sprite->initWithFile(filename))
			{
				sprite->setVisible(false);
				sprite->setScale(0.8f);
				sprite->autorelease();
				return sprite;
			}
			CC_SAFE_DELETE(sprite);
			return nullptr;
		}
	public:
		void On()
		{
			this->setVisible(true);
			this->runAction(Sequence::create(ScaleTo::create(0.1f, 1.3f), ScaleTo::create(0.1f, 1.0f), nullptr));
		}

		void Off()
		{
			this->runAction(Sequence::create(ScaleTo::create(0.1, 1.3f), ScaleTo::create(0.1f, 0.7f), RemoveSelf::create(), nullptr));
		}
	};
}

namespace news
{
	class Sprite : public cocos2d::Sprite
	{
	public:
		static news::Sprite* news::Sprite::create()
		{
			news::Sprite *sprite = new (std::nothrow) news::Sprite();
			if (sprite && sprite->initWithFile("news.png"))
			{
				sprite->setPosition(Vec2(1280 / 2, 720 + sprite->getContentSize().height));
				sprite->setOpacity(168);
				sprite->autorelease();
				return sprite;
			}
			CC_SAFE_DELETE(sprite);
			return nullptr;
		}
	public:
		void On(const string& news_str, int num)
		{
			this->runAction(Sequence::create(
				MoveTo::create(0.18f, Vec2(1280 / 2, 720 - (this->getContentSize().height / 2) - 3)),
				MoveBy::create(0.1f, Vec2(0, 3)), CallFuncN::create([=](Node* node)
			{
				for (int i = 1; i <= num; i++)
				{
					auto news_label = Label::create(news_str, "Arial", 30);
					news_label->setColor(Color3B::WHITE);
					news_label->setPosition(Vec2(1280 * i, 720 - 40));
					news_label->runAction(Sequence::create(
						MoveTo::create(4.f * i, Vec2(-30, 720 - (this->getContentSize().height / 2))),
						RemoveSelf::create(), nullptr));
					node->getParent()->addChild(news_label);
				}
			}), DelayTime::create(4.f * num + 1), MoveBy::create(0.1f, Vec2(0, -10)),
				MoveTo::create(0.1f, Vec2(1280 / 2, 720 + 40)), RemoveSelf::create(), nullptr));
		}
	};
}

enum EVENT_TYPE
{
	FOOD,
	WATER,
	WAR,
	PLAGUE,
	TERROR,
};

enum COUNTRY
{
	NORTH_KOREA,//FOOD, WATER
	SOMALIA,
	KENYA,
	BANGLADESH,
	AFGHANISTAN,

	SYRIA,//WAR
	IRAQ,

	ZAMBIA,//PLAGUE
	CONGO,

	PARIS,//TERROR
	UK,
	DENMARK,
	BELGIUM,
	USA,
	BRAZIL,
	MAXICO,

};

typedef struct tagEvent
{
	int numcountry;
	string country;
	string eventtype;
	string mainneed;
	string subneed;
	int need1;
	int need2;
}HelpEvent;

class Interface;

class EventMng
{
private:
	string _event_Type[5];
	string _country[16];


	Node* _parent;

	Interface* _interface;

	std::map<string, HelpEvent> _hevent;

	std::map<string, Vec2> _iconpos;

	pin::Sprite* _tooltip;

	void eventOccurred(int, int);

	float _dt[5];
	float _time[5];
	bool _onPin[16];

	bool _tooltipon = false;

	Layer* _lifeLayer;
	int _life = 7;
public:
	void refreshLife();

	void removePin(int, bool);

	void menucallback(Ref*, HelpEvent);

	void init(Node* parent, Interface* interfacee);

	void update(float dt);

	void opentooltip(string);
	void closetooltip();
};