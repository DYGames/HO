#include "Interface.h"

Interface* Interface::create(Node* parent)
{
	Interface* iinterface = new Interface;
	if (iinterface && iinterface->initWithFile("interface.png"))
	{
		iinterface->_isOn = false;
		iinterface->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, -iinterface->getContentSize().height));
		iinterface->setAnchorPoint(Vec2(0.5, 0));

		iinterface->_button = Sprite::create("button.png");
		iinterface->_button->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 0));
		iinterface->_button->setAnchorPoint(Vec2(0.5f, 0));
		parent->addChild(iinterface->_button);

		iinterface->autorelease();
		return iinterface;
	}
	delete iinterface;
	return nullptr;
}

void Interface::Init()
{
	_water_back = Sprite::create("Interface/interface_water.png");
	_water_back->setPosition(this->getContentSize().width / 4, this->getContentSize().height - 50);
	//_water_back->setScale(1.5f);

	_food_back = Sprite::create("Interface/interface_food.png");
	_food_back->setPosition(40 + this->getContentSize().width /1.5, this->getContentSize().height - 50);
	//_food_back->setScale(1.5f);

	_human_back = Sprite::create("Interface/interface_human.png");
	_human_back->setPosition(this->getContentSize().width /4, this->getContentSize().height - 70 - _water_back->getContentSize().height);
	//_human_back->setScale(1.5f);

	_medicine_back = Sprite::create("Interface/interface_medicine.png");
	_medicine_back->setPosition(40 + this->getContentSize().width / 1.5, this->getContentSize().height - 70 - _water_back->getContentSize().height);
	//_medicine_back->setScale(1.5f);

	this->addChild(_food_back);
	this->addChild(_human_back);
	this->addChild(_water_back);
	this->addChild(_medicine_back);

	// ---------------------------

	water_gage = CCProgressTimer::create(CCSprite::create("Interface/water.png"));
	if (water_gage != NULL)
	{
		water_gage->setType(kCCProgressTimerTypeBar);
		water_gage->setMidpoint(ccp(0, 0.5));
		//water_gage->setScale(1.5f);
		water_gage->setBarChangeRate(ccp(1, 0));
		water_gage->setPercentage(100);
		water_gage->setPosition(_water_back->getPosition() + Vec2(25, 0));
		this->addChild(water_gage);
	}

	food_gage = CCProgressTimer::create(CCSprite::create("Interface/food.png"));
	if (food_gage != NULL)
	{
		food_gage->setType(kCCProgressTimerTypeBar);
		food_gage->setMidpoint(ccp(0, 0.5));
		//food_gage->setScale(1.5f);
		food_gage->setBarChangeRate(ccp(1, 0));
		food_gage->setPercentage(100);
		food_gage->setPosition(_food_back->getPosition() + Vec2(25, 0));
		this->addChild(food_gage);
	}

	human_gage = CCProgressTimer::create(CCSprite::create("Interface/human.png"));
	if (human_gage != NULL)
	{
		human_gage->setType(kCCProgressTimerTypeBar);
		human_gage->setMidpoint(ccp(0, 0.5));
		//human_gage->setScale(1.5f);
		human_gage->setBarChangeRate(ccp(1, 0));
		human_gage->setPercentage(100);
		human_gage->setPosition(_human_back->getPosition() + Vec2(25, 0));
		this->addChild(human_gage);
	}

	medicine_gage = CCProgressTimer::create(CCSprite::create("Interface/medicine.png"));
	if (medicine_gage != NULL)
	{
		medicine_gage->setType(kCCProgressTimerTypeBar);
		medicine_gage->setMidpoint(ccp(0, 0.5));
		//medicine_gage->setScale(1.5f);
		medicine_gage->setBarChangeRate(ccp(1, 0));
		medicine_gage->setPercentage(100);
		medicine_gage->setPosition(_medicine_back->getPosition() + Vec2(25, 0));
		this->addChild(medicine_gage);
	}

	// -----------------

	_water_label = Label::create("100/100", "Arial", 20);
	//_water_label->setPosition(_water_back->getPosition() + Vec2((_water_back->getContentSize().width - 70), 0));
	_water_label->setPosition(_water_back->getPosition() + Vec2(0, 28));
	this->addChild(_water_label);

	_food_label = Label::create("100/100", "Arial", 20);
	//_food_label->setPosition(_food_back->getPosition() + Vec2((_water_back->getContentSize().width - 70), 0));
	_food_label->setPosition(_food_back->getPosition() + Vec2(0, 28));
	this->addChild(_food_label);

	_medicine_label = Label::create("100/100", "Arial", 20);
	//_medicine_label->setPosition(_medicine_back->getPosition() + Vec2((_water_back->getContentSize().width - 70), 0));
	_medicine_label->setPosition(_medicine_back->getPosition() + Vec2(0, 28));
	this->addChild(_medicine_label);

	_human_label = Label::create("100/100", "Arial", 20);
	//_human_label->setPosition(_human_back->getPosition() + Vec2((_water_back->getContentSize().width - 70), 0));
	_human_label->setPosition(_human_back->getPosition() + Vec2(0, 28));
	this->addChild(_human_label);
}

void Interface::OnOff()
{
	if (_isOn)
	{
		_button->setFlippedY(false);
		_button->runAction(MoveBy::create(0.2f, Vec2(0, -this->getContentSize().height)));
		this->runAction(MoveBy::create(0.2f, Vec2(0, -this->getContentSize().height)));
		_isOn = false;
	}
	else if (!_isOn)
	{
		_button->setFlippedY(true);
		_button->runAction(MoveBy::create(0.2f, Vec2(0, this->getContentSize().height)));
		this->runAction(MoveBy::create(0.2f, Vec2(0, this->getContentSize().height)));
		_isOn = true;
	}
}


void Interface::SetOnTouch(Touch* touch)
{
	if (_button->getBoundingBox().containsPoint(touch->getLocation()))
	{
		OnOff();
	}
}

void Interface::SetWater(float curValue = 100, float maxValue = 100)
{
	float div = curValue / maxValue;
	water_gage->setPercentage((curValue / maxValue)*100);
	_water_label->setString(StringUtils::format("%.f/%.f", curValue, maxValue));
}

void Interface::SetFood(float curValue=100, float maxValue=100)
{
	food_gage->setPercentage((curValue / maxValue) * 100);
	_food_label->setString(StringUtils::format("%.f/%.f", curValue, maxValue));
}

void Interface::SetHuman(float curValue=100, float maxValue=100)
{
	human_gage->setPercentage((curValue / maxValue) * 100);
	_human_label->setString(StringUtils::format("%.f/%.f", curValue, maxValue));
}

void Interface::SetMedicine(float curValue=100, float maxValue = 100)
{
	medicine_gage->setPercentage((curValue / maxValue) * 100);
	_medicine_label->setString(StringUtils::format("%.f/%.f", curValue, maxValue));
}