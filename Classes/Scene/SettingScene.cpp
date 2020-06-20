#include "SettingScene.h"

using namespace ui;


USING_NS_CC;

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


			float const x = origin.x + visibleSize.width / 2;
			float const y = origin.y + visibleSize.height / 2;
			musicItemToggle->setPosition(Vec2(x, y));

			auto menu = Menu::create(musicItemToggle, NULL);
			menu->setPosition(Vec2(0, 0));
			this->addChild(menu);
		}
		//add slider to contrl background music
		auto slider = Slider::create();
		slider->loadBarTexture("button/Slider_Back.png"); // what the slider looks like
		slider->loadSlidBallTextures("button/SliderNode_Normal.png",
			"button/SliderNode_Press.png", "button/SliderNode_Disable.png");
		slider->loadProgressBarTexture("button/Slider_PressBar.png");

		/*int percent;
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();*/

		slider->addEventListener(CC_CALLBACK_1(SettingScene::SliderCallBack, this));
			/*percent = slider->getPercent();
			audio->setBackgroundMusicVolume(float(percent) / 100);
			UD_setFloat("musicPercent", percent);*/

		float const x = origin.x + visibleSize.width / 2;
		float const y = origin.y + visibleSize.height / 2;
		slider->setPosition(Vec2(x, y - 50));
		slider->setPercent(UD_getFloat("musicPercent"));
		this->addChild(slider);
		/*auto music_slider = Slider::create();
		music_slider->loadBarTexture("sliderTrack.png");
		music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
		music_slider->loadProgressBarTexture("sliderProgress.png");
		//获取之前设置的音乐音量
		float musicPercent = UD_getFloat("musicPercent");

		//    //第一次默认100
		//    if(musicPercent == 0.0f){
		//        musicPercent = 100.0f;
		//    }

			//设置背景初始值
		music_slider->setPercent(musicPercent);
		music_slider->cocos2d::Node::setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.7));
		//添加监听器
		music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
			//当滑块的百分比发生变化的时候
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
				//获得滑动条的百分比
				int percent = music_slider->getPercent();
				auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
				audio->setBackgroundMusicVolume(float(percent) / 100);
				UD_setFloat("musicPercent", percent);
			}
			});
		this->addChild(music_slider);*/
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
			float percent = UD_getInt("musicPercent");
			audio->playBackgroundMusic("music/Olimpica.mp3", true);
			audio->setBackgroundMusicVolume(percent / 100.0);
		}
		
	}
}
void SettingScene::menuBackCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	Director::getInstance()->popScene();
}
void SettingScene::SliderCallBack(Ref* pSender)
{
	auto item = (Slider*)(pSender);
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