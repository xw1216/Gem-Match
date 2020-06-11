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
	}
}

void SettingScene::menuBackCallback(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SettingScene::audioMuteCallback(Ref* pSender)
{

}
