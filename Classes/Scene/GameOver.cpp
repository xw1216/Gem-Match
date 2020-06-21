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
		setResolutionScale();
		// add background
		auto background = Sprite::create("Background.png");
		if (background == nullptr)
		{
			problemLoading("Background.png");
		}
		else
		{
			background->setScale(m_scaleRatioX, m_scaleRatioY);
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

		//add Textedit
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan =
			CC_CALLBACK_2(GameOver::touchBeganCallback, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(
			touchListener, this);
		textEdit = CCTextFieldTTF::textFieldWithPlaceHolder(
			"Please input name:", "fonts/FZCHSJW.ttf", 35);
		textEdit->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2, 
			m_origin.y + m_visibleSize.height - textEdit->getContentSize().height * 3));
		textEdit->setColorSpaceHolder(Color3B::BLACK);
		textEdit->setTextColor(Color4B::BLACK);
		this->addChild(textEdit);

		//add Gameover sprite
		auto gameover = Sprite::create("image/GameOverA.png");
		if (gameover == nullptr)
		{
			problemLoading("Background.png");
		}
		else
		{
			gameover->setScale(m_scaleRatioX, m_scaleRatioY);
			gameover->setPosition(Vec2(
				m_visibleSize.width/2,
				m_visibleSize.height/2));
			this->addChild(gameover, -20);
		}


		//add Summit button
		auto startItem = MenuItemImage::create(
			"button/SubmitNormal.png",
			"button/SubmitPressed.png",
			CC_CALLBACK_1(GameOver::menuSubmitCallback, this));

		if (startItem == nullptr ||
			startItem->getContentSize().width <= 0 ||
			startItem->getContentSize().height <= 0)
		{
			problemLoading("button/SubmitNormal.png and buttonSubmitNormal.png");
		}
		else
		{
			startItem->setScale(m_scaleRatioX, m_scaleRatioY);
			startItem->setPosition(Vec2(
				m_visibleSize.width / 2, 
				m_visibleSize.height / 5));
		}

		auto menuStart = Menu::create(startItem, NULL);
		menuStart->setPosition(Vec2::ZERO);
		this->addChild(menuStart, 2);

		auto transiParticle = CCParticleSystemQuad::create(
			"plist/Ribbon.plist");
		transiParticle->setScaleX(m_scaleRatioX);
		transiParticle->setScaleY(m_scaleRatioY);
		transiParticle->setPosition(m_visibleSize.width / 2,
			transiParticle->getContentSize().height * 1.5);
		this->addChild(transiParticle, 2);
		transiParticle->setAutoRemoveOnFinish(true);


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
	int const highestScore = CCUserDefault::sharedUserDefault()->
		getIntegerForKey("highestScore");
	if (score > highestScore)
	{
		CCUserDefault::sharedUserDefault()->
			setIntegerForKey("highestScore", score);
		CCUserDefault::sharedUserDefault()->flush();

		auto sprite = Sprite::create("thehighestscore.png");
		sprite->setScale(m_scaleRatioX, m_scaleRatioY);
		sprite->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2));
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("music/Win.mp3", false);
		this->addChild(sprite, 0);
	}
	else
	{
		auto sprite = Sprite::create("GameOverA.png");
		sprite->setScale(m_scaleRatioX, m_scaleRatioY);
		sprite->setPosition(Vec2(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2));
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
	bool isClicked = textEdit->boundingBox().containsPoint(
		touch->getLocation());

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

	popDialog(callfuncN_selector(GameOver::dialogButtonCallback));
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

void GameOver::setResolutionScale()
{
	auto const winSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_scaleRatioX = winSize.width / kDesignResolutionWidth;
	m_scaleRatioY = winSize.height / kDesignResolutionHeight;
}

void GameOver::popDialog(SEL_CallFuncN callfunc)
{
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	Dialog* dialog = Dialog::create();
	dialog->setTitle("Try Again?", 45 * m_scaleRatioX);
	dialog->setBackground("button/DialogBackground.png");
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", "Yes!", 1,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	dialog->addButton("button/BlankNormal.png", "button/BlankPressed.png", "NO,Exit", 2,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2 - 70 * m_scaleRatioY));
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