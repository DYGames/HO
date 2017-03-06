#pragma once

#include "stdafx.h"

namespace cloud
{
	class Layer : public cocos2d::Layer
	{
	public:
		static cloud::Layer *cloud::Layer::create()
		{
			cloud::Layer *ret = new cloud::Layer();
			if (ret && ret->init())
			{
				ret->autorelease();
				return ret;
			}
			else
			{
				CC_SAFE_DELETE(ret);
				return nullptr;
			}
		}
	public:
		void On()
		{
			srand(time(NULL));
			this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(rand() % 7 + 4), CallFunc::create([=]()
			{
				Sprite* c1 = Sprite::create("cloud1.png");
				c1->setPosition(Vec2(-200, rand() % 800 + 100));
				c1->setOpacity(150);
				c1->runAction(Sequence::create(MoveTo::create(rand() % 20 + 10, Vec2(1280 + 150, c1->getPosition().y)), nullptr));
				this->addChild(c1);

				Sprite* c2 = Sprite::create("cloud2.png");
				c2->setPosition(Vec2(-200, rand() % 800 + 100));
				c2->setOpacity(150);
				c2->runAction(Sequence::create(MoveTo::create(rand() % 20 + 10, Vec2(1280 + 150, c2->getPosition().y)), nullptr));
				this->addChild(c2);

				Sprite* c3 = Sprite::create("cloud3.png");
				c3->setPosition(Vec2(-200, rand() % 800 + 100));
				c3->setOpacity(150);
				c3->runAction(Sequence::create(MoveTo::create(rand() % 30 + 10.0f, Vec2(1280 + 150, c3->getPosition().y)), nullptr));
				this->addChild(c3);

			}), nullptr)));
		}
	};
}

class Interface;

class InGame : public Layer
{
private:
	EventMng* _eventMng;
	Layer* _pinLayer;
	Interface* _interface;
public:
	~InGame(){
		delete _eventMng;
	}

    static Scene* createScene();

	virtual bool init();

	void menucallback(Ref* sender);
    
	void EventMngUpdate(float dt);
	void resourceFill(float dt);

	bool onTouchBegan(Touch*, Event*) override;

	CREATE_FUNC(InGame);
};