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
		addButtonItem("icon/Home.png", Vec2(
			visibleSize.width - kIconlength, kIconlength),
			CC_CALLBACK_1(LevelSelect::menuBackCallback, this));

		// add different game mode start menu
		auto clock = addButtonItem("icon/Clock.png", Vec2(
			visibleSize.width / 2 - 2 * kIconlength, visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::timeModeCallback, this));
		clock->setScale(1.5);
		auto steps = addButtonItem("icon/Play.png", Vec2(
			visibleSize.width / 2, visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::stepModeCallback, this));
		steps->setScale(1.5);
		auto times = addButtonItem("icon/Refresh.png", Vec2(
			visibleSize.width / 2 + 2 * kIconlength, visibleSize.height / 2),
			CC_CALLBACK_1(LevelSelect::creativeModeCallback, this));
		times->setScale(1.5);

		//add ranklist button
		addButtonItem("icon/Menu.png", Vec2(
			visibleSize.width / 2, visibleSize.height / 4),
			CC_CALLBACK_1(LevelSelect::gameRankCallback, this));

		return true;
	}
}

Menu* LevelSelect::addButtonItem(const char* image, Vec2 position,
	const ccMenuCallback& callback)
{
	auto menuItem = MenuItemImage::create(image, image, callback);
	if (menuItem == nullptr)
		assert("menu create failed");
	else
	{
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
		firstButton = "Win 10000 pts in 20 steps";
		secondButton = "Win 20000 pts in 15 steps";
	}
	else if (mode == Times)
	{
		tag = 3;
		title = "Time Mode";
		firstButton = "Win 5000 pts in 60s";
		secondButton = "Win 10000 pts in 90s";
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	Dialog* dialog = Dialog::create();
	dialog->setTitle(title.c_str(), 45);
	dialog->setBackground("button/DialogBackground.png");
	dialog->setContent("Easy or hard?", 35);
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", firstButton.c_str(), tag,
		Vec2(visibleSize.width / 2, visibleSize.height / 2));
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", secondButton.c_str(), tag + 1,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
	dialog->addButton("button/BlankNormal.png", "button/BlankNormal.png", "Cancel", 0,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 - 140));
	dialog->setCallbackFunc(this, callfunc);
	addChild(dialog, 3);
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
			UD_setInt("Gamemode", Steps); UD_setInt("Steps", 20); UD_setInt("Goal", 10000); break;
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