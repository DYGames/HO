#include "OptionPopup.h"

OptionPopup::OptionPopup(Layer* parent)
{
	baseLayer = LayerColor::create(Color4B(100, 100, 100, 100));
	baseLayer->setContentSize(Size(680, 400));
	baseLayer->setPosition(Vec2((1280 - baseLayer->getContentSize().width)/2,(720 - baseLayer->getContentSize().height)/2));
	parent->addChild(baseLayer);

	baseLayer->setVisible(false);

	Sprite* background = Sprite::create("OptionPopup/background.png");
	background->setPosition(Vec2(baseLayer->getContentSize().width / 2, baseLayer->getContentSize().height / 2));
	baseLayer->addChild(background);

	background_music = Sprite::create();
	effect_music = Sprite::create();

	if (UserDefault::getInstance()->getBoolForKey("Setting"))
	{
		if (UserDefault::getInstance()->getBoolForKey("Background"))
		{
			background_music->setTexture("OptionPopup/bgm_on.png");
			isBackground = true;
		}
		else
		{
			background_music->setTexture("OptionPopup/bgm_off.png");
			isBackground = false;
		}

		if (UserDefault::getInstance()->getBoolForKey("Effect"))
		{
			effect_music->setTexture("OptionPopup/effect_on.png");
			isEffect = true;
		}
		else
		{
			effect_music->setTexture("OptionPopup/effect_off.png");
			isEffect = false;
		}
	}
	else
	{
		isBackground = true;
		isEffect = true;
		background_music = Sprite::create("OptionPopup/bgm_on.png");
		effect_music = Sprite::create("OptionPopup/effect_on.png");

	}

	// --------------------------

	// background_music = Sprite::create("OptionPopup/bgm_on.png");
	// effect_music = Sprite::create("OptionPopup/effect_on.png");

	background_music->setPosition(baseLayer->getContentSize().width / 2 - 150, baseLayer->getContentSize().height / 2 + 50);
	baseLayer->addChild(background_music);

	effect_music->setPosition(baseLayer->getContentSize().width / 2 + 150, baseLayer->getContentSize().height / 2 + 50);
	baseLayer->addChild(effect_music);

	allVolume = Slider::create();
	allVolume->setScale(1.8f);
	allVolume->setPosition(Vec2(baseLayer->getContentSize().width/2,baseLayer->getContentSize().height/2 - 100));
	allVolume->loadBarTexture("OptionPopup/Slider_Back.png");
	allVolume->loadSlidBallTextures(
		"OptionPopup/SliderNode_Disable.png",
		"OptionPopup/SliderNode_Disable.png",
		"OptionPopup/SliderNode_Disable.png");
	allVolume->setPercent(100);

	baseLayer->addChild(allVolume);
}

void OptionPopup::On()
{
	baseLayer->setVisible(true);
}

void OptionPopup::Off()
{
	baseLayer->setVisible(false);
}

bool OptionPopup::SetOnTouch(Touch* touch)
{
	Vec2 basePosition = baseLayer->convertTouchToNodeSpace(touch);
	
	if (background_music->getBoundingBox().containsPoint(basePosition))
	{
		UserDefault::getInstance()->setBoolForKey("Setting",true);
		if (isBackground)
		{
			UserDefault::getInstance()->setBoolForKey("Background", false);
			background_music->setTexture("OptionPopup/bgm_off.png");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			isBackground = false;
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("Background", true);
			background_music->setTexture("OptionPopup/bgm_on.png");
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			isBackground = true;
		}
		return false;
	}

	else if (effect_music->getBoundingBox().containsPoint(basePosition))
	{
		UserDefault::getInstance()->setBoolForKey("Setting", true);
		if (isEffect)
		{
			UserDefault::getInstance()->setBoolForKey("Effect", false);
			SimpleAudioEngine::getInstance()->stopAllEffects();
			effect_music->setTexture("OptionPopup/effect_off.png");
			isEffect = false;
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("Effect", true);
			SimpleAudioEngine::getInstance()->resumeAllEffects();
			effect_music->setTexture("OptionPopup/effect_on.png");
			isEffect = true;
		}
		return false;
	}

	else if (
		0 > basePosition.x || 
		baseLayer->getContentSize().width < basePosition.x || 
		0 > basePosition.y ||
		baseLayer->getContentSize().height < basePosition.y)
	{
		return true;
	}
	return false;
}

void OptionPopup::update(float dt)
{
	float volumePerc = this->allVolume->getPercent();
	volumePerc *= 0.01;

	log("%.2f", volumePerc);

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volumePerc);
	SimpleAudioEngine::getInstance()->setEffectsVolume(volumePerc);
}