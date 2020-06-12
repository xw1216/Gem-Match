#include "SettingScene.h"


cocos2d::Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if(!Scene::create())
		return false;
	else
	{
		auto const visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 const origin = Director::getInstance()->getVisibleOrigin();

		// add background
		auto background = Sprite::create("Background.png");
		if (background == nullptr)
		{
			problemLoading("Background.png");
		}
		else
		{
			background->setPosition(Vec2::ZERO);
			this->addChild(background, -20);
		}

		//add button to exit
		auto homeItem = MenuItemImage::create(
			"icon/home.png", "icon/home.png",
			CC_CALLBACK_1(SettingScene::menuBackHomeCallback, this));
		if (homeItem == nullptr)
			problemLoading("'icon/home.png', 'icon/home.png'");
		else
		{
			float const x = origin.x + visibleSize.width - homeItem->getContentSize().width;
			float const y = origin.y + homeItem->getContentSize().height;
			homeItem->setPosition(Vec2(x, y));
			auto homeMenu = Menu::create(homeItem, NULL);
			homeMenu->setPosition(Vec2::ZERO);
			this->addChild(homeMenu, 1);
		}

		//add button to control music
		if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
		{
			auto musicOn = MenuItemImage::create("icon/Volume.png", "icon/Volume.png");
			if (musicOn == nullptr)
			{
				problemLoading("icon/Volume");
			}

			auto musicOff = MenuItemImage::create("icon/Mute.png", "icon/Mute.png");
			if (musicOff == nullptr)
			{
				problemLoading("icon/Mute");
			}

			MenuItemToggle* musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::audioMuteCallback, this), musicOn, musicOff, NULL);
			//musicItemToggle->setPosition(Vec2(320, 457));

			float const x = origin.x + visibleSize.width / 2;
			float const y = origin.y + visibleSize.height / 2;
			musicItemToggle->setPosition(Vec2(x, y));

			auto menu = Menu::create(musicItemToggle, NULL);
			menu->setPosition(Vec2(0, 0));
			this->addChild(menu);
		}
		else
		{
			auto musicOn = MenuItemImage::create("icon/Volume.png", "icon/Volume.png");
			if (musicOn == nullptr)
			{
				problemLoading("icon/Volume");
			}

			auto musicOff = MenuItemImage::create("icon/Mute.png", "icon/Mute.png");
			if (musicOff == nullptr)
			{
				problemLoading("icon/Mute");
			}

			MenuItemToggle* musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::audioMuteCallback, this), musicOff, musicOn, NULL);
			//musicItemToggle->setPosition(Vec2(320, 457));

			float const x = origin.x + visibleSize.width / 2;
			float const y = origin.y + visibleSize.height / 2;
			musicItemToggle->setPosition(Vec2(x, y));

			auto menu = Menu::create(musicItemToggle, NULL);
			menu->setPosition(Vec2(0, 0));
			this->addChild(menu);
		}
		//add back button
		auto backItem = MenuItemImage::create(
			"icon/Back.png", "icon/Back.png",
			CC_CALLBACK_1(SettingScene::menuBackCallback, this));
		if (backItem == nullptr)
			problemLoading("'icon/Back.png', 'icon/Back.png'");
		else
		{
			float const x = backItem->getContentSize().width;
			float const y = backItem->getContentSize().height;
			backItem->setPosition(Vec2(x, y));
			auto backMenu = Menu::create(backItem, NULL);
			backMenu->setPosition(Vec2::ZERO);
			this->addChild(backMenu, 1);
		}
	}
}

void SettingScene::menuBackHomeCallback(Ref* pSender)
{
	auto scene = HelloWorld::create();
	Director::getInstance()->replaceScene(scene);
}

void SettingScene::audioMuteCallback(Ref* pSender)
{
	MenuItemToggle* temp = (CCMenuItemToggle*)pSender;

	if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey(MUSIC_KEY, false);
		CCUserDefault::sharedUserDefault()->flush();
		audio->pauseBackgroundMusic();
	}
	else
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey(MUSIC_KEY, true);
		CCUserDefault::sharedUserDefault()->flush();
		audio->resumeBackgroundMusic();
	}
}
void SettingScene::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
