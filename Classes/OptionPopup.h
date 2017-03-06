#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;

class OptionPopup
{
private:
	LayerColor* baseLayer;

	Sprite* background_music;
	Sprite* effect_music;
	
	Slider* allVolume;

	bool isBackground;
	bool isEffect;

public:
	OptionPopup(Layer* parent);

	void update(float dt);
	void On();
	void Off();

	bool SetOnTouch(Touch* touch);
};