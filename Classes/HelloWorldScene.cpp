#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{
    setResolutionScale();
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{

    // initailize the father class.
    if (!Scene::init())
    {
        return false;
    }

    if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
    {
        float percent = UD_getInt("musicPercent");
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playBackgroundMusic("music/Olimpica.mp3", true);
        audio->setBackgroundMusicVolume(percent / 100.0);
        UD_setFloat("musicPercent", percent);
    }

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "icon/Power.png", "icon/Power.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'icon/Power.png' and 'icon/Power.png'");
    }
    else
    {
        closeItem->setScale(m_scaleRatioX, m_scaleRatioY);
        closeItem->setPosition(Vec2(
            m_origin.x + m_visibleSize.width - closeItem->getContentSize().width,
            m_origin.y + closeItem->getContentSize().height));
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
        startItem->setScale(m_scaleRatioX, m_scaleRatioY);
        float const x = m_origin.x + m_visibleSize.width / 2;
        float const y = m_origin.y + m_visibleSize.height / 5;
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
        label->setScale(m_scaleRatioX, m_scaleRatioY);
        label->setPosition(Vec2(m_origin.x + m_visibleSize.width / 2,
            m_origin.y + m_visibleSize.height - 4 * (label->getContentSize().height)));
        label->setColor(Color3B::BLACK);

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //add background
    auto background = Sprite::create("Background.png");
    if (background == nullptr)
    {
        problemLoading("Background.png");
    }
    else
    {
        background->setScale(m_scaleRatioX, m_scaleRatioY);
        background->setPosition(Vec2(
            m_visibleSize.width / 2 + m_origin.x,
            m_visibleSize.height / 2 + m_origin.y));
        this->addChild(background, -20);
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
        sprite->setScale(m_scaleRatioX, m_scaleRatioY);
        sprite->setPosition(Vec2(
            m_visibleSize.width / 2 + m_origin.x,
            m_visibleSize.height / 2 + m_origin.y));
        auto seq = Sequence::create(delay, dwindle, nullptr);
        sprite->runAction(seq);
        this->addChild(sprite, 0);
    }

    //add setting button
    auto settingItem = MenuItemImage::create(
        "icon/Setting.png", "icon/Setting.png",
        CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
    if (settingItem == nullptr)
        problemLoading("'icon/Setting.png', 'icon/Setting.png'");
    else
    {
        settingItem->setScale(m_scaleRatioX, m_scaleRatioY);
        float const x = m_origin.x + settingItem->getContentSize().width;
        float const y = m_origin.y + settingItem->getContentSize().height;
        settingItem->setPosition(Vec2(x, y));
        auto homeMenu = Menu::create(settingItem, NULL);
        homeMenu->setPosition(Vec2::ZERO);
        this->addChild(homeMenu, 1);
    }
    return true;
}

void HelloWorld::setResolutionScale()
{
    auto const winSize = CCDirector::sharedDirector()->getWinSize();
    m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
    m_scaleRatioX = winSize.width / kDesignResolutionWidth;
    m_scaleRatioY = winSize.height / kDesignResolutionHeight;
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