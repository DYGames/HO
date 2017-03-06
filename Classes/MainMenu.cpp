#include "MainMenu.h"

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if ( !LayerColor::initWithColor(Color4B::BLACK)) {
        return false;
    }
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	Sprite* background = Sprite::create("MainMenu/background.png");
	background->setPosition(Vec2(1280 / 2, 720 / 2));
	this->addChild(background);

	MenuItemImage* start = MenuItemImage::create("MainMenu/start.png", "MainMenu/start_press.png", [=](Ref* sender) {
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f,InGame::createScene()));
	});

	start->setPosition(Vec2(1280 / 2 - 200, 720 / 2 - 180));

	MenuItemImage* option = MenuItemImage::create("MainMenu/option.png", "MainMenu/option_press.png", [=](Ref* sender){
		optionPopup->On();
		isOption = true;
		menuButton->setEnabled(false);
	});

	option->setPosition(Vec2(1280 - 60, 720 - 60));

	MenuItemImage* exit = MenuItemImage::create("MainMenu/exit.png", "MainMenu/exit_press.png", [=](Ref* sender) {
		UserDefault::getInstance()->setBoolForKey("Setting", false);
		UserDefault::getInstance()->setBoolForKey("Background", true);
		UserDefault::getInstance()->setBoolForKey("Effect", true);

		Director::getInstance()->end();
	});

	exit->setPosition(Vec2(1280 / 2 + 200, 720 / 2 - 180));

	menuButton = Menu::create(start, option, exit, nullptr);
	menuButton->setPosition(Vec2::ZERO);
	this->addChild(menuButton);

	// -------------------
	
	optionPopup = new OptionPopup(this);
	isOption = false;

	// -------------------
	if (!UserDefault::getInstance()->getBoolForKey("Stting"))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3");
	}

	//_interface->SetWater(400, 700);
	//this->menuButton->setEnabled(false);
	
	this->schedule(schedule_selector(MainMenu::update));
    return true;
}

bool MainMenu::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (isOption) {
		if (optionPopup->SetOnTouch(touch)) {
			isOption = false;
			optionPopup->Off();
			menuButton->setEnabled(true);
		}
	}
	return true;
}

void MainMenu::update(float dt)
{
	if (isOption)
	{
		optionPopup->update(dt);
	}
}