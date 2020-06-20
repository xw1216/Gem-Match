#include "GameOver.h"

cocos2d::Scene* GameOver::createScene()
{
	return GameOver::create();
}

bool GameOver::init()
{
	if (!Scene::create())
	{
		return false;
	}
	else
	{
		Size const visibleSize = Director::getInstance()->getVisibleSize();
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

		if (!CCUserDefault::sharedUserDefault()->
			getIntegerForKey("highestScore"))
		{
			CCUserDefault::sharedUserDefault()->
				setIntegerForKey("highestScore", 0);

		}
		// pause the backgroundmusic
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->pauseBackgroundMusic();
		/*auto label = Label::createWithTTF("GemMatch!", "fonts/FZCHSJW.ttf", 40);
		if (label == nullptr)
		{
			problemLoading("'fonts/FZCHSJW.ttf'");
		}
		else
		{
			label->setPosition(Vec2(kDesignResolutionWidth /2,
				kDesignResolutionHeight- 4 * (label->getContentSize().height)));
			label->setColor(Color3B::Color3B(89, 91, 179));

			// add the label as a child to this layer
			this->addChild(label, 1);
		}*/
		//add Textedit
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan =
			CC_CALLBACK_2(GameOver::touchBeganCallback, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(
			touchListener, this);
		textEdit = CCTextFieldTTF::textFieldWithPlaceHolder("Please input name:", "fonts/FZCHSJW.ttf", 24);
		textEdit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - textEdit->getContentSize().height * 3));
		textEdit->setColorSpaceHolder(Color3B::BLACK);
		textEdit->setTextColor(Color4B::BLACK);
		this->addChild(textEdit);

		//add Summit button
		auto startItem = MenuItemImage::create(
			"button/button_normal.png",
			"button/button_clicked.png",
			CC_CALLBACK_1(GameOver::menuSubmitCallback, this));

		if (startItem == nullptr ||
			startItem->getContentSize().width <= 0 ||
			startItem->getContentSize().height <= 0)
		{
			problemLoading("button/StartNormal.png and button/StartSelected.png");
		}
		else
		{
			float const x = visibleSize.width / 2;
			float const y = visibleSize.height / 5;
			startItem->setPosition(Vec2(x, y));
		}

		auto menuStart = Menu::create(startItem, NULL);
		menuStart->setPosition(Vec2::ZERO);
		this->addChild(menuStart, 2);


		if (!UD_getBool("isExist", false)) {
			UD_setBool("isExist", true);

			for (int i = 1; i <= max_range; i++) {
				// Assign values to the corresponding XML conten
				UD_setString(StringUtils::format("p%d_name", i).c_str(), "name");
				UD_setInt(StringUtils::format("p%d_score", i).c_str(), 0);
				UD_setString(StringUtils::format("p%d_mode", i).c_str(), "mode");

				// Assign values to the corresponding contents of the array
				p[i - 1].name = "name";
				p[i - 1].score = 0;
				p[i - 1].mode = "mode";
			}

		}
		else {
			for (int i = 1; i <= max_range; i++) {
				// Get XML content
				p[i - 1].name = UD_getString(StringUtils::format("p%d_name", i).c_str());
				p[i - 1].score = UD_getInt(StringUtils::format("p%d_score", i).c_str());
				p[i - 1].mode = UD_getString(StringUtils::format("p%d_mode", i).c_str());
			}
		}
	}
}

void GameOver::setScore(int score)
{
	int highestScore = CCUserDefault::sharedUserDefault()->
		getIntegerForKey("highestScore");
	if (score > highestScore)
	{
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey("highestScore", score);
		CCUserDefault::sharedUserDefault()->flush();
		auto sprite = Sprite::create("thehighestscore.png");
		sprite->setPosition(Vec2(kDesignResolutionWidth / 2, kDesignResolutionHeight / 2));
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("music/Win.mp3", false);
		this->addChild(sprite, 0);
	}
	else
	{
		auto sprite = Sprite::create("GameOverA.png");
		sprite->setPosition(Vec2(kDesignResolutionWidth / 2, kDesignResolutionHeight / 2));
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("music/end_Steps.mp3", false);
		this->addChild(sprite, 0);
	}

}

void GameOver::levelSelectBackCallback(Ref* pSender)
{
	auto scene = LevelSelect::createScene();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(kTransitionTime, scene));
}

void GameOver::gameStartCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(kTransitionTime, scene));
}
bool GameOver::touchBeganCallback(Touch* touch, Event* event)
{
	//Used to determine whether the control is in the point  
	bool isClicked = textEdit->boundingBox().containsPoint(touch->getLocation());

	//if true  
	if (isClicked) {

		textEdit->attachWithIME();
	}
	else {
		textEdit->detachWithIME();
	}

	return true;
}
void GameOver::menuSubmitCallback(Ref* pSender)
{
	p[max_range].name = textEdit->getString();
	p[max_range].score = finalScore;
	p[max_range].mode = current_mode;

	bool isExist = false;
	// is player in ranklist
	for (int i = 0; i < max_range; i++) {
		if (p[i].name == p[max_range].name) {
			p[i].score = p[i].score > p[max_range].score ? p[i].score : p[max_range].score;
			isExist = true;
			break;
		}
	}

	if (!isExist) {
		// bubble sorting
		for (int i = 0; i < max_range; i++) {
			for (int j = max_range - i; j > 0; j--) {
				if (p[j].score > p[j - 1].score) {
					Player temp;
					temp = p[j];
					p[j] = p[j - 1];
					p[j - 1] = temp;
				}
			}
		}
	}

	// Store XML
	for (int i = 1; i <= max_range; i++) {
		// Assign values to the corresponding XML content
		UD_setString(StringUtils::format("p%d_name", i).c_str(), p[i - 1].name);
		UD_setInt(StringUtils::format("p%d_score", i).c_str(), p[i - 1].score);
		UD_setString(StringUtils::format("p%d_mode", i).c_str(), p[i - 1].mode);
		CCUserDefault::sharedUserDefault()->flush();
	}
	popDialog( callfuncN_selector(GameOver::dialogButtonCallback));
	// 这里，是用来测试的，忽略不计吧
	CCLOG(p[0].name.c_str());
	CCLOG("score:%d", p[0].score);
	CCLOG("mode:%s", p[0].mode.c_str());
	CCLOG(p[1].name.c_str());
	CCLOG("score:%d", p[1].score);
	CCLOG("mode:%s", p[1].mode.c_str());
	CCLOG(p[2].name.c_str());
	CCLOG("score:%d\n", p[2].score);
	CCLOG("mode:%s", p[3].mode.c_str());
}
void GameOver::setcurrentmode(int modetype)
{
	switch (modetype)
	{
	case 0:
		current_mode = "Steps";
		break;
	case 1:
		current_mode = "Times";
		break;
	}
}
void GameOver::popDialog(SEL_CallFuncN callfunc)
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	Dialog* dialog = Dialog::create();
	dialog->setTitle("Try Again?", 45);
	dialog->setBackground("button/DialogBackground.png");
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", "Yes!", 1,
		Vec2(visibleSize.width / 2, visibleSize.height / 2));
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", "NO,Exit", 2,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
	dialog->setCallbackFunc(this, callfunc);
	addChild(dialog, 3);
}
void GameOver::dialogButtonCallback(Node* pNode)
{
	CCASSERT(pNode != nullptr, "Node is a null pointer");
	_eventDispatcher->resumeEventListenersForTarget(this, true);
	int tag = pNode->getTag();
	
		if (tag == 1)
		{
			float percent = UD_getInt("musicPercent");
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
			if (CCUserDefault::sharedUserDefault()->getIntegerForKey(MUSIC_KEY))
			{
				
				audio->playBackgroundMusic("music/Olimpica.mp3", true);
				audio->setBackgroundMusicVolume(percent / 100.0);
				UD_setFloat("musicPercent", percent);
			}
			audio->playEffect("music/normalclick.mp3", false);
			auto scene = LevelSelect::createScene();
			Director::getInstance()->replaceScene(TransitionMoveInR::create(kTransitionTime, scene));
		}
		else
		{
			Director::getInstance()->end();
		}

}