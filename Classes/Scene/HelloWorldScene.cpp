#include "HelloWorldScene.h"


using namespace ui;
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{

    // initailize the father class.
    if ( !Scene::init() )
    {
        return false;
    }

	auto const visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();
	UD_setBool("music_paused", false);


	if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
	{
		float percent = UD_getInt("musicPercent");
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playBackgroundMusic("music/Olimpica.mp3", true);
		audio->setBackgroundMusicVolume(percent/100.0);
		UD_setFloat("musicPercent", percent);
	}



    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "icon/PowerNormal.png",
        "icon/PowerSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'icon/Power.png' and 'icon/Power.png'");
    }
    else
    {
       float const x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
       float const y = origin.y + closeItem->getContentSize().height/2;
       closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menuClose = Menu::create(closeItem, NULL);
    menuClose->setPosition(Vec2::ZERO);
    this->addChild(menuClose, 1);

    // add a "start" menu.
    auto startItem = MenuItemImage::create(
        "button/StartNormal.png",
        "button/StartSelected.png",
        CC_CALLBACK_1(HelloWorld::menuStartCallback, this));

    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("button/StartNormal.png and button/StartSelected.png");
    }
    else
    {
        float const x = origin.x + visibleSize.width / 2;
        float const y = origin.y + visibleSize.height / 5;
        startItem->setPosition(Vec2(x, y));
    }

    auto menuStart = Menu::create(startItem, NULL);
    menuStart->setPosition(Vec2::ZERO);
    this->addChild(menuStart, 2);


    // create and initialize a label
    auto label = Label::createWithTTF("GemMatch!", "fonts/FZCHSJW.ttf", 40);
    if (label == nullptr)
    {
        problemLoading("'fonts/FZCHSJW.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - 4*(label->getContentSize().height )));
        label->setColor(Color3B::Color3B(89, 91, 179));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

	//add background
	auto HelloBack = Sprite::create("Hello_background.jpg");
	if (HelloBack == nullptr)
	{
		problemLoading("Hello_Back.png");
	}
	else
	{
		HelloBack->setPosition(Vec2(kDesignResolutionWidth / 2, kDesignResolutionHeight / 2));
		this->addChild(HelloBack, -20);
	}

    // add a logo on the center.
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        auto delay = DelayTime::create(kTransitionTime);
        auto dwindle = ScaleBy::create(1, 0.25f, 0.25f);
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        auto seq = Sequence::create(delay, dwindle,nullptr);
        sprite->runAction(seq);

        this->addChild(sprite, 0);
    }

	//add settin button
	auto settingItem = MenuItemImage::create(
		"icon/setting.png", "icon/setting.png",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
	if (settingItem == nullptr)
		problemLoading("'icon/setting.png', 'icon/setting.png'");
	else
	{
		float const x = settingItem->getContentSize().width;
		float const y = origin.y + settingItem->getContentSize().height;
		settingItem->setPosition(Vec2(x, y));
		auto homeMenu = Menu::create(settingItem, NULL);
		homeMenu->setPosition(Vec2::ZERO);
		this->addChild(homeMenu, 1);
	}

	//add loadingbar
	/*auto loadingBar = LoadingBar::create("load_bar.png");

	// set the direction of the loading bars progress
	loadingBar->setDirection(LoadingBar::Direction::LEFT);
	float const x = origin.x + visibleSize.width / 2;
	float const y = origin.y + visibleSize.height / 5 + 90;
	loadingBar->setPosition(Vec2(x, y));

	this->addChild(loadingBar, 3);*/
    return true;
}


void HelloWorld::menuStartCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
    auto scene = LevelSelect::createScene();
    Director::getInstance()->replaceScene(TransitionMoveInR::create(kTransitionTime, scene));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    //To navigate back to native iOS screen(if present) without quitting the application 
    //instead trigger a custom event created in RootViewController.mm as below
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
void HelloWorld::menuSettingCallback(cocos2d::Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = SettingScene::createScene();
	Director::getInstance()->pushScene(TransitionMoveInR::create(kTransitionTime, scene));

}