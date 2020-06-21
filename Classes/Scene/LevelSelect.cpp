#include "LevelSelect.h"
#include "RankScene.h"

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

		// add home menu
		addButtonItem("icon/Home.png", Vec2(
			m_origin.x + m_visibleSize.width - kIconlength,
			m_origin.y + kIconlength),
			CC_CALLBACK_1(LevelSelect::menuBackCallback, this));

		// add different game mode start menu
		auto clock = addButtonItem("icon/Clock.png", Vec2(
			m_origin.x + m_visibleSize.width / 2 - 2 * m_scaleRatioX * kIconlength,
			m_origin.y + m_visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::timeModeCallback, this));
		auto steps = addButtonItem("icon/Play.png", Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::stepModeCallback, this));
		auto times = addButtonItem("icon/Refresh.png", Vec2(
			m_origin.x + m_visibleSize.width / 2 + 2 * m_scaleRatioX * kIconlength,
			m_origin.y + m_visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::creativeModeCallback, this));

		//add ranklist button
		addButtonItem("icon/Menu.png", Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 4),
			CC_CALLBACK_1(LevelSelect::gameRankCallback, this));

		return true;
	}
}

Menu* LevelSelect::addButtonItem(const char* image, Vec2 position,
	const ccMenuCallback& callback)
{
	auto menuItem = MenuItemImage::create(image, image, callback);
	if (menuItem == nullptr)
		assert("Menu create failed!");
	else
	{
		menuItem->setScale(m_scaleRatioX, m_scaleRatioY);
		menuItem->setPosition(position);
		auto menu = Menu::create(menuItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 2);
		return menu;
	}
}

void LevelSelect::popDialog(GameMode mode, SEL_CallFuncN callfunc)
{
	int tag = 0;
	std::string title, firstButton, secondButton;
	if (mode == Steps)
	{
		tag = 1;
		title = "Step Mode";
		firstButton = "More pts in 20 steps";
		secondButton = "More pts in 15 steps";
	}
	else if (mode == Times)
	{
		tag = 3;
		title = "Time Mode";
		firstButton = "More pts in 60s";
		secondButton = "More pts in 90s";
	}
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	Dialog* dialog = Dialog::create();
	dialog->setTitle(title.c_str(), 45);
	dialog->setBackground("button/DialogBackground.png");
	dialog->setContent("Easy or hard?", 35);
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", firstButton.c_str(), tag,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", secondButton.c_str(), tag + 1,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2 - 70 * m_scaleRatioY));
	dialog->addButton("button/BlankNormal.png", "button/BlankNormal.png", "Cancel", 0,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2 - 140 * m_scaleRatioY));
	dialog->setCallbackFunc(this, callfunc);
	addChild(dialog, 3);
}

void LevelSelect::setResolutionScale()
{
	auto const winSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_scaleRatioX = winSize.width / kDesignResolutionWidth;
	m_scaleRatioY = winSize.height / kDesignResolutionHeight;
}

void LevelSelect::menuBackCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(kTransitionTime, scene));
}

void LevelSelect::gameRankCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = RankScene::createScene();
	Director::getInstance()->pushScene(TransitionCrossFade::create(kTransitionTime, scene));
}

void LevelSelect::timeModeCallback(Ref* pSender)
{
	popDialog(Times, callfuncN_selector(LevelSelect::dialogButtonCallback));
}

void LevelSelect::stepModeCallback(Ref* pSender)
{
	popDialog(Steps, callfuncN_selector(LevelSelect::dialogButtonCallback));
}

void LevelSelect::creativeModeCallback(Ref* pSender)
{
	UD_setInt("Gamemode", Creative);
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(kTransitionTime, scene));
}

void LevelSelect::dialogButtonCallback(Node* pNode)
{
	CCASSERT(pNode != nullptr, "Node is a null pointer");
	_eventDispatcher->resumeEventListenersForTarget(this, true);
	int tag = pNode->getTag();
	if (tag != 0)
	{
		switch (tag)
		{
		case 1:
			UD_setInt("Gamemode", Steps); UD_setInt("Steps", 20); UD_setInt("Goal", 10000);  break;
		case 2:
			UD_setInt("Gamemode", Steps); UD_setInt("Steps", 15); UD_setInt("Goal", 20000); break;
		case 3:
			UD_setInt("Gamemode", Times); UD_setInt("Times", 60); UD_setInt("Goal", 5000); break;
		case 4:
			UD_setInt("Gamemode", Times); UD_setInt("Times", 90); UD_setInt("Goal", 10000); break;
		default:
			break;
		}
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(
			TransitionCrossFade::create(kTransitionTime, scene));
	}
}