#include "LevelSelect.h"

cocos2d::Scene* LevelSelect::createScene()
{
	return LevelSelect::create();
}

bool LevelSelect::init()
{
	if (!Scene::init())
	{
		return false;
	}
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
		
		// add home menu
		auto homeItem = MenuItemImage::create(
												"icon/home.png", "icon/home.png",
												CC_CALLBACK_1(LevelSelect::menuBackCallback,this));
		if (homeItem == nullptr)
			problemLoading("'icon/home.png', 'icon/home.png'");
		else
		{
			float const x = origin.x + visibleSize.width - homeItem->getContentSize().width;
			float const y = origin.y + homeItem->getContentSize().height;
			homeItem->setPosition(Vec2(x, y));
			auto homeMenu = Menu::create(homeItem, NULL);
			homeMenu->setPosition(Vec2::ZERO);
			this->addChild(homeMenu,1);
		}

		// add game menu
		auto gameItem = MenuItemImage::create(
			"icon/Power.png", "icon/Power.png",
			CC_CALLBACK_1(LevelSelect::gameStartCallback, this));
		if (gameItem == nullptr)
			problemLoading("icon/Power.png");
		else
		{
			float const x = origin.x + visibleSize.width / 2;
			float const y = origin.y + visibleSize.height / 2;
			gameItem->setPosition(Vec2(x, y));
			auto gameMenu = Menu::create(gameItem, NULL);
			gameMenu->setPosition(Vec2::ZERO);
			this->addChild(gameMenu,2);
		}
		return true;
	}
}

void LevelSelect::menuBackCallback(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(kTransitionTime,scene));
}

void LevelSelect::gameStartCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(kTransitionTime, scene));
}
