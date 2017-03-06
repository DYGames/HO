#pragma once
#include <cocos2d.h>
USING_NS_CC;

#include "OptionPopup.h"
#include "Interface.h"

class MainMenu : public LayerColor
{
private:
	bool isOption;
	OptionPopup* optionPopup;
	Menu* menuButton;
public:
	bool onTouchBegan(Touch *touch, Event *unused_event) override;
	void update(float dt);

    static Scene* createScene();
    bool init() override;
	CREATE_FUNC(MainMenu);
};