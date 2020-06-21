#include "SettingScene.h"

using namespace CocosDenshion;

cocos2d::Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if (!Scene::create())
		return false;
	else
	{
		setResolutionScale();
		addGroupSelect();

		// add background
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

		//add button to go back
		auto homeItem = MenuItemImage::create(
			"icon/Home.png", "icon/Home.png",
			CC_CALLBACK_1(SettingScene::menuBackHomeCallback, this));
		if (homeItem == nullptr)
			problemLoading("'icon/home.png', 'icon/home.png'");
		else
		{
			homeItem->setScale(m_scaleRatioX, m_scaleRatioY);
			homeItem->setPosition(Vec2(
				m_origin.x + m_visibleSize.width - homeItem->getContentSize().width,
				m_origin.y + homeItem->getContentSize().height));
			auto homeMenu = Menu::create(homeItem, NULL);
			homeMenu->setPosition(Vec2::ZERO);
			this->addChild(homeMenu, 1);
		}

		//add button to control music
		addMusicControl();

		//add slider to contrl background music
		auto slider = ui::Slider::create();
		slider->loadBarTexture("button/Slider_Back.png"); // what the slider looks like
		slider->loadSlidBallTextures("button/SliderNode_Normal.png",
			"button/SliderNode_Press.png", "button/SliderNode_Disable.png");
		slider->loadProgressBarTexture("button/Slider_PressBar.png");

		/*int percent;
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();*/

		slider->addEventListener(CC_CALLBACK_1(SettingScene::sliderCallBack, this));
		/*percent = slider->getPercent();
		audio->setBackgroundMusicVolume(float(percent) / 100);
		UD_setFloat("musicPercent", percent);*/

		slider->setScale(m_scaleRatioX, m_scaleRatioY);
		slider->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2 + 20 * m_scaleRatioY));
		slider->setPercent(UD_getFloat("musicPercent"));
		this->addChild(slider);

		//add back button
		auto backItem = MenuItemImage::create(
			"icon/Back.png", "icon/Back.png",
			CC_CALLBACK_1(SettingScene::menuBackCallback, this));
		if (backItem == nullptr)
			problemLoading("'icon/Back.png', 'icon/Back.png'");
		else
		{
			backItem->setScale(m_scaleRatioX, m_scaleRatioY);
			backItem->setPosition(Vec2(
				m_origin.x + backItem->getContentSize().width,
				m_origin.y + backItem->getContentSize().height));
			auto backMenu = Menu::create(backItem, NULL);
			backMenu->setPosition(Vec2::ZERO);
			this->addChild(backMenu, 1);
		}
		return true;
	}
}

void SettingScene::setResolutionScale()
{
	auto const winSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_scaleRatioX = winSize.width / kDesignResolutionWidth;
	m_scaleRatioY = winSize.height / kDesignResolutionHeight;
}

void SettingScene::addMusicControl()
{
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

		MenuItemToggle* musicItemToggle =
			MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(SettingScene::audioMuteCallback, this),
				musicOn, musicOff, NULL);


		musicItemToggle->setScale(m_scaleRatioX, m_scaleRatioY);
		musicItemToggle->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2 + 70 * m_scaleRatioY));

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

		MenuItemToggle* musicItemToggle =
			MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(SettingScene::audioMuteCallback, this),
				musicOff, musicOn, NULL);


		musicItemToggle->setScale(m_scaleRatioX, m_scaleRatioY);
		musicItemToggle->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2 + 70 * m_scaleRatioY));

		auto menu = Menu::create(musicItemToggle, NULL);
		menu->setPosition(Vec2(0, 0));
		this->addChild(menu);
	}
}

void SettingScene::addGroupSelect()
{
	UD_setInt("Group", 1);
	m_selector = Sprite::create("icon/Select.png");
	m_selector->setPosition(Vec2(
		m_visibleSize.width / 2 - kSpriteWidth * 1.5,
		m_visibleSize.height / 2 - kSpriteHeight * 2.5));
	this->addChild(m_selector);

	auto label = Label::create("Choose your group", "fonts/FZCHSJW.ttf", 35);
	label->setPosition(Vec2(
		m_visibleSize.width / 2, 
		m_visibleSize.height / 2 - label->getContentSize().height));
	label->setColor(Color3B::BLACK);
	this->addChild(label);

	auto content = Label::create("(Useless while gaming)", "fonts/FZCHSJW.ttf", 25);
	content->setPosition(Vec2(
		m_visibleSize.width / 2,
		m_visibleSize.height / 2 - label->getContentSize().height - content->getContentSize().height));
	content->setColor(Color3B::BLACK);
	this->addChild(content);


	auto aGroup = MenuItemImage::create("button/BlockC.png", "button/BlockC.png", 
		CC_CALLBACK_1(SettingScene::groupASelectCallback, this));
	aGroup->setPosition(Vec2(
		m_visibleSize.width / 2 - kSpriteWidth * 1.5,
		m_visibleSize.height / 2 - kSpriteHeight * 1.8));
	auto bGroup = MenuItemImage::create("button/BlockG.png", "button/BlockG.png",
		CC_CALLBACK_1(SettingScene::groupBSelectCallback, this));
	bGroup->setPosition(Vec2(m_visibleSize.width / 2,
		m_visibleSize.height / 2 - kSpriteHeight * 1.8));
	auto cGroup = MenuItemImage::create("button/BlockK.png", "button/BlockK.png",
		CC_CALLBACK_1(SettingScene::groupCSelectCallback, this));
	cGroup->setPosition(Vec2(
		m_visibleSize.width / 2 + kSpriteWidth * 1.5,
		m_visibleSize.height / 2 - kSpriteHeight * 1.8));
	auto menu = Menu::create(aGroup, bGroup, cGroup, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
}

void SettingScene::menuBackHomeCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = HelloWorld::create();
	Director::getInstance()->replaceScene(scene);
}

void SettingScene::audioMuteCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/musicset.mp3", false);
	MenuItemToggle* temp = (CCMenuItemToggle*)pSender;

	if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey(MUSIC_KEY, false);
		CCUserDefault::sharedUserDefault()->flush();
		audio->pauseBackgroundMusic();
		UD_setBool("music_paused", true);
	}
	else
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey(MUSIC_KEY, true);
		CCUserDefault::sharedUserDefault()->flush();
		if (UD_getBool("music_paused"))
		{
			audio->resumeBackgroundMusic();
		}
		else
		{
			float const percent = UD_getInt("musicPercent");
			audio->playBackgroundMusic("music/Olimpica.mp3", true);
			audio->setBackgroundMusicVolume(percent / 100.0);
		}
	}
}

void SettingScene::menuBackCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	this->removeFromParent();
	Director::getInstance()->popScene();
}

void SettingScene::sliderCallBack(Ref* pSender)
{
	auto item = (ui::Slider*)(pSender);
	log("%i", item->getPercent());
	if (item->getPercent() == 100) {
		item->setEnabled(false);
	}
	else {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->setBackgroundMusicVolume(item->getPercent() / 100.0);
		UD_setFloat("musicPercent", item->getPercent());
	}
}

void SettingScene::groupASelectCallback(Ref* pSender)
{
	if (!pSender)
		assert("Null Pointer!");
	UD_setInt("Group", 1);
	m_selector->runAction(MoveTo::create(0.25, Vec2(
		m_visibleSize.width / 2 - kSpriteWidth * 1.5,
		m_visibleSize.height / 2 - kSpriteHeight * 2.5)));
}

void SettingScene::groupBSelectCallback(Ref* pSender)
{
	if (!pSender)
		assert("Null Pointer!");
	UD_setInt("Group", 2);
	m_selector->runAction(MoveTo::create(0.25, Vec2(
		m_visibleSize.width / 2,
		m_visibleSize.height / 2 - kSpriteHeight * 2.5)));
}

void SettingScene::groupCSelectCallback(Ref* pSender)
{
	if (!pSender)
		assert("Null Pointer!");
	UD_setInt("Group", 3);
	m_selector->runAction(MoveTo::create(0.25, Vec2(
		m_visibleSize.width / 2 + kSpriteWidth * 1.5,
		m_visibleSize.height / 2 - kSpriteHeight * 2.5)));
}
