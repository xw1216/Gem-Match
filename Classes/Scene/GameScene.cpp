#include "GameScene.h"

// a simple GameScene constructor
GameScene::GameScene() noexcept
	: m_isAction(false), m_isFillSprite(false),
	m_enableOperation(true), m_startSprite(nullptr),
	m_endSprite(nullptr), m_time(0), m_steps(0), m_score(0) {}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	else
	{
		setResolutionScale();
		setGameMode();
		setIndexRange();

		m_cols = 6; m_rows = 8;

		// add background
		auto background = Sprite::create("Background.png");
		if (background == nullptr)
		{
			problemLoading("Back_Scene.png");
		}
		else
		{
			background->setScale(m_scaleRatioX, m_scaleRatioY);
			background->setPosition(Vec2(
				m_visibleSize.width / 2 + m_origin.x,
				m_visibleSize.height / 2 + m_origin.y));
			this->addChild(background, -20);
		}

		auto loadbar = Sprite::create("loadingbar4.png");
		if (loadbar == nullptr)
		{
			problemLoading("loadbar.png");
		}
		else
		{
			loadbar->setPosition(Vec2(
				m_origin.x + m_visibleSize.width / 2 + m_scaleRatioX * 150,
				m_origin.y + m_visibleSize.height / 2 + m_scaleRatioY * 370));
			this->addChild(loadbar, 1);
		}

		// add touch listener of the touch action
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan =
			CC_CALLBACK_2(GameScene::touchBeganCallback, this);
		touchListener->onTouchEnded =
			CC_CALLBACK_2(GameScene::touchEndCallback, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(
			touchListener, this);

		// initialize all needed elements
		initMap();
		initLimit();
		initScorer();

		//add home button
		auto homeItem = MenuItemImage::create(
			"icon/Home.png", "icon/Home.png",
			CC_CALLBACK_1(GameScene::menuHomeCallback, this));
		if (homeItem == nullptr)
			problemLoading("'icon/home.png', 'icon/home.png'");
		else
		{
			homeItem->setScale(m_scaleRatioX, m_scaleRatioY);
			homeItem->setPosition(Vec2(
				m_origin.x + m_visibleSize.width - homeItem->getContentSize().width,
				m_origin.x + homeItem->getContentSize().height));
			auto homeMenu = Menu::create(homeItem, NULL);
			homeMenu->setPosition(Vec2::ZERO);
			this->addChild(homeMenu, 1);
		}

		//add setting buttton
		auto settingItem = MenuItemImage::create(
			"icon/Setting.png", "icon/Setting.png",
			CC_CALLBACK_1(GameScene::menuSettingCallback, this));
		if (settingItem == nullptr)
			problemLoading("icon/Setting.png lost.");
		else
		{
			settingItem->setScale(m_scaleRatioX, m_scaleRatioY);
			settingItem->setPosition(Vec2(
				m_origin.x + m_visibleSize.width - settingItem->getContentSize().width * 2,
				m_origin.y + settingItem->getContentSize().height));
			auto settingMenu = Menu::create(settingItem, NULL);
			settingMenu->setPosition(Vec2::ZERO);
			this->addChild(settingMenu, 1);
		}

		//add pause button
		auto pauseItem = MenuItemImage::create(
			"icon/Pause.png", "icon/Pause.png",
			CC_CALLBACK_1(GameScene::gamePauseCallback, this));
		if (pauseItem == nullptr)
			problemLoading("icon/pause.png lost.");
		else
		{
			pauseItem->setScale(m_scaleRatioX, m_scaleRatioY);
			pauseItem->setPosition(Vec2(
				m_origin.x + pauseItem->getContentSize().width,
				m_origin.y + pauseItem->getContentSize().height));
			auto pauseMenu = Menu::create(pauseItem, NULL);
			pauseMenu->setPosition(Vec2::ZERO);
			this->addChild(pauseMenu, 1);
		}

		//add Goal label
		int m_goal = UD_getInt("Goal");
		TTFConfig config("fonts/MFShangZhen.ttf", 25 * m_scaleRatioX);
		cocos2d::Label* goalLabel = nullptr;
		goalLabel = Label::createWithTTF(
			config, StringUtils::format("Goal : %d", m_goal));
		goalLabel->setName("limitSteps");
		goalLabel->setColor(Color3B::BLACK);
		goalLabel->setPosition(
			m_origin.x + goalLabel->getContentSize().width + 70 * m_scaleRatioX,
			m_origin.y + m_visibleSize.height - 50 * m_scaleRatioY - goalLabel->getContentSize().height * 2);
		this->addChild(goalLabel);

		// schedule update func to check matchs and refresh
		scheduleUpdate();

		return true;
	}
}

// create sprites for first entering randomly
void GameScene::initMap()
{
	setBlockOriginPosition();
	srand(time(0));
	int index = 0;
	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			index = (rand() % (m_endIndex - m_startIndex + 1)) + m_startIndex;
			this->createSprite(row, col, index);
		}
}

void GameScene::createSprite(int row, int col, int index)
{
	SpriteShape* sprite = SpriteShape::create(row, col, index);
	CCASSERT(sprite, "Null Pointer!");

	// confirm the position and set animation for dropped sprites
	Point const endPosition = positionOfItem(row, col);
	Point const startPosition = positionOfAnimateItem(endPosition);
	float const speed = startPosition.y / (1 * m_visibleSize.height);

	sprite->setScale(m_scaleRatioX, m_scaleRatioY);
	sprite->setPosition(startPosition);
	sprite->runAction(MoveTo::create(speed, endPosition));
	this->addChild(sprite, 0);
	// store the sprite into map for further searching
	m_blocks.insert(BlockPair(Point(row, col), sprite));
}

// add limitation for playability according to selected gamemode
void GameScene::initLimit()
{
	TTFConfig config("fonts/MFShangZhen.ttf", 25 * m_scaleRatioX);
	cocos2d::Label* limitLable = nullptr;

	switch (m_gamemode)
	{
	case Steps:
		m_steps = UD_getInt("Steps");
		limitLable = Label::createWithTTF(
			config, StringUtils::format("Steps : %d", m_steps));
		limitLable->setName("limitSteps");
		break;
	case Times:
		m_time = UD_getInt("Times");
		limitLable = Label::createWithTTF(
			config, StringUtils::format("Time : %d", m_time));
		limitLable->setName("limitTimes");
		schedule(schedule_selector(GameScene::timer), 1.0f);
		break;
	default:
		limitLable = Label::createWithTTF(config, "Creative");
		limitLable->setName("limitCreative");
		break;
	}

	limitLable->setColor(Color3B::BLACK);
	limitLable->setPosition(
		m_origin.x + limitLable->getContentSize().width,
		m_origin.y + m_visibleSize.height - limitLable->getContentSize().height * 2);
	this->addChild(limitLable);
}

void GameScene::initScorer()
{
	TTFConfig config("fonts/MFShangZhen.ttf", 25 * m_scaleRatioX);
	cocos2d::Label* scoreLable = Label::createWithTTF(
		config, StringUtils::format("Score : %d", m_score));
	scoreLable->setName("scoreLable");
	scoreLable->setColor(Color3B::BLACK);
	scoreLable->setPosition(
		m_origin.x + m_visibleSize.width - scoreLable->getContentSize().width * 1.2,
		m_origin.y + m_visibleSize.height - scoreLable->getContentSize().height * 2);
	this->addChild(scoreLable);
}

Point GameScene::positionOfAnimateItem(Point point)
{
	return Point(point.x, point.y + m_visibleSize.height);
}

Point GameScene::positionOfItem(int row, int col)
{
	float const x = m_blockOrigin.x + (m_scaleRatioX * kSpriteWidth +
		m_scaleRatioX * kBorderWidth) * col + m_scaleRatioX * kSpriteWidth / 2;
	float const y = m_blockOrigin.y + (m_scaleRatioY * kSpriteHeight +
		m_scaleRatioX * kBorderWidth) * row + m_scaleRatioY * kSpriteHeight / 2;
	return Point(x, y);
}

// refresh the situation about action and filling
void GameScene::update(float dt)
{

	// if certain action was going on , check wether it's going on now
	if (m_isAction)
	{
		m_isAction = false;
		m_enableOperation = true;
		SpriteShape* sprite = nullptr;

		for (int row = 0; row < getRows(); row++)
			for (int col = 0; col < getCols(); col++)
			{
				// traverse all sprites to make sure are there running actions
				sprite = findSprite(row, col);
				if (sprite != nullptr && sprite->getNumberOfRunningActions() > 0)
				{
					m_isAction = true;
					m_enableOperation = false;
					break;
				}
			}
	}
	// if no action, check are there sprites needs to fill
	if (!m_isAction)
	{
		if (m_isFillSprite)
		{
			fillSprite();
			m_isFillSprite = false;
		}
		else
		{
			checkAndRemove();
		}
		if (m_gamemode == Steps && m_isFillSprite
			&& m_enableOperation && m_steps <= -1
			&& this->getNumberOfRunningActions() <= 0)
			gameOver(0);
	}


}

// when there is no action or filling
// begin to check all matches and remove them
void GameScene::checkAndRemove()
{
	SpriteShape* sprite = nullptr;
	// reset all sprite to be not ignored
	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			sprite = findSprite(row, col);
			if (sprite == nullptr)
				continue;
			sprite->setIsIgnored(false);
		}

	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			sprite = findSprite(row, col);
			// skip if it is nullptr ,ignored or it has been already marked
			if (sprite == nullptr)
				continue;
			if (sprite->getIsNeedRemove())
				continue;
			if (sprite->getIsIgored())
				continue;

			// check cols and rows depart
			// store match sprite in the list
			std::list<SpriteShape*> colChain;
			colCheck(sprite, colChain);
			std::list<SpriteShape*> rowChain;
			rowCheck(sprite, rowChain);

			// take the longest matches to process
			// and there are different types for the match and special sprites
			if (colChain.size() < 3 && rowChain.size() < 3)
			{
				continue;
			}
			else if (colChain.size() >= rowChain.size())
			{
				if (colChain.size() == 4)
					processMatch(colChain, Vertical);
				else if (colChain.size() > 4)
					processMatch(colChain, Global);
				else
					processMatch(colChain, Normal);
			}
			else
			{
				if (rowChain.size() == 4)
					processMatch(rowChain, Horizontal);
				else if (rowChain.size() > 4)
					processMatch(rowChain, Global);
				else
					processMatch(rowChain, Normal);
			}
		}
	// begin to remove after marking
	removeSprite();
}

void GameScene::markRemove(SpriteShape* sprite) noexcept
{
	if (sprite == nullptr)
		return;

	if (sprite->getIsNeedRemove())
		return;
	else
		sprite->setIsNeedRemove(true);
}

// distinguish the types of remove and 
// transfer them to explode func to actualize whole row/col clear
void GameScene::removeSprite()
{
	m_isAction = true;
	SpriteShape* sprite = nullptr;
	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			sprite = findSprite(row, col);
			if (sprite == nullptr)
				continue;
			if (sprite->getIsNeedRemove())
			{
				m_isFillSprite = true;
				if (sprite->getStatus() == Vertical)
					explodeVertical(sprite);
				else if (sprite->getStatus() == Horizontal)
					explodeHorizontal(sprite);
				else if (sprite->getStatus() == Global)
					explodeGlobal(sprite);
				else
					explodeSprite(sprite);
			}
		}
}

// remove single sprites and play animation for disappearing
void GameScene::explodeSprite(SpriteShape* sprite)
{
	if (sprite == nullptr)
		return;
	auto explodeSpawn = Spawn::createWithTwoActions(
		ScaleTo::create(0.25, 0), FadeOut::create(0.25));
	auto explodeSequence = Sequence::create(explodeSpawn,
		CallFuncN::create(CC_CALLBACK_1(GameScene::actionEndCallback, this)), NULL);
	sprite->runAction(explodeSequence);
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/Dehiscence.mp3", false);
	audio->playEffect("music/effectnormal.mp3", false);
}

void GameScene::colCheck(SpriteShape* sprite, std::list<SpriteShape*>& colChain)
{
	// checkAndRemove() makes sure that sprite is not nullptr
	colChain.push_back(sprite);

	SpriteShape* neighbourSprite = nullptr;

	// left hand search
	for (int neighbourCol = sprite->getCol() - 1;
		neighbourCol >= 0; neighbourCol--)
	{
		neighbourSprite = findSprite(sprite->getRow(), neighbourCol);
		if (neighbourSprite != nullptr &&
			neighbourSprite->getImageIndex() == sprite->getImageIndex() &&
			!(neighbourSprite->getIsNeedRemove()))
		{
			colChain.push_back(neighbourSprite);
		}
		else
		{
			break;
		}
	}
	// right hand search
	for (int neighbourCol = sprite->getCol() + 1;
		neighbourCol < getCols(); neighbourCol++)
	{
		neighbourSprite = findSprite(sprite->getRow(), neighbourCol);
		if (neighbourSprite != nullptr &&
			neighbourSprite->getImageIndex() == sprite->getImageIndex() &&
			!(neighbourSprite->getIsNeedRemove()))
		{
			colChain.push_back(neighbourSprite);
		}
		else
		{
			break;
		}
	}
}

void GameScene::rowCheck(SpriteShape* sprite, std::list<SpriteShape*>& rowChain)
{
	// checkAndRemove() makes sure that sprite is not nullptr
	rowChain.push_back(sprite);
	SpriteShape* neighbourSprite = nullptr;

	// downward search
	for (int neighbourRow = sprite->getRow() - 1;
		neighbourRow >= 0; neighbourRow--)
	{
		neighbourSprite = findSprite(neighbourRow, sprite->getCol());
		if (neighbourSprite != nullptr &&
			neighbourSprite->getImageIndex() == sprite->getImageIndex() &&
			!(neighbourSprite->getIsNeedRemove()))
		{
			rowChain.push_back(neighbourSprite);
		}
		else
		{
			break;
		}
	}
	// upwards sreach
	for (int neighbourRow = sprite->getRow() + 1;
		neighbourRow < getRows(); neighbourRow++)
	{
		neighbourSprite = findSprite(neighbourRow, sprite->getCol());
		if (neighbourSprite != nullptr &&
			neighbourSprite->getImageIndex() == sprite->getImageIndex() &&
			!(neighbourSprite->getIsNeedRemove()))
		{
			rowChain.push_back(neighbourSprite);
		}
		else
		{
			break;
		}
	}
}

void GameScene::fillSprite()
{
	m_isAction = true;
	std::vector<int> colEmptyNum;
	SpriteShape* sprite = nullptr;
	for (int col = 0; col < getCols(); col++)
	{
		int removedCounter = 0;
		for (int row = 0; row < getRows(); row++)
		{
			sprite = findSprite(row, col);
			if (sprite == nullptr)
				// record the num of removed sprite in a single col
				removedCounter++;
			else
			{
				if (removedCounter > 0)
				{
					int const newRow = row - removedCounter;
					m_blocks.insert(
						BlockPair(Point(newRow, col), sprite));
					m_blocks.erase(Point(row, col));

					Point const endPosition = positionOfItem(newRow, col);
					Point const startPosition = sprite->getPosition();

					float const speed = (startPosition.y - endPosition.y) / m_visibleSize.height * 3;
					sprite->stopAllActions();
					sprite->runAction(MoveTo::create(speed, endPosition));
					sprite->setRow(newRow);
				}
			}
		}
		colEmptyNum.push_back(removedCounter);
		// calculate and refresh the game score
		scorer(removedCounter);
	}

	// create new sprites randomly to fill in the blanks
	int index = 0;
	srand(time(0));
	for (int col = 0; col < getCols(); col++)
	{
		for (int row = getRows() - colEmptyNum[col];
			row < getRows(); row++)
		{
			index = (rand() % (m_endIndex - m_startIndex + 1)) + m_startIndex;
			createSprite(row, col, index);
		}
	}
}

void GameScene::swapSprite()
{
	const int  startRow = m_startSprite->getRow(),
		startCol = m_startSprite->getCol(),
		endRow = m_endSprite->getRow(),
		endCol = m_endSprite->getCol();

	m_blocks.erase(Point(startRow, startCol));
	m_blocks.erase(Point(endRow, endCol));
	m_blocks.insert(BlockPair(
		Point(endRow, endCol), m_startSprite));
	m_blocks.insert(BlockPair(
		Point(startRow, startCol), m_endSprite));
	m_startSprite->setRow(endRow); m_startSprite->setCol(endCol);
	m_endSprite->setRow(startRow); m_endSprite->setCol(startCol);

}

// invoked when user swap tow sprites and play animations
// judge whether they could come into being new matches
// remain sawp if could while return to origin if could not
bool GameScene::swapMatch()
{
	m_isAction = true;
	m_enableOperation = false;

	if (m_startSprite == nullptr || m_endSprite == nullptr)
		return false;

	Point const departure = m_startSprite->getPosition();
	Point const destination = m_endSprite->getPosition();

	swapSprite();
	std::list<SpriteShape*>
		colChainStart, rowChainStart,
		colChainEnd, rowChainEnd;
	colCheck(m_startSprite, colChainStart);
	colCheck(m_endSprite, colChainEnd);
	rowCheck(m_startSprite, rowChainStart);
	rowCheck(m_endSprite, rowChainEnd);

	if (rowChainStart.size() >= 3
		|| rowChainEnd.size() >= 3
		|| colChainStart.size() >= 3
		|| colChainEnd.size() >= 3)
	{
		m_startSprite->runAction(Sequence::create(
			MoveTo::create(kBlockSwapTime, destination),
			DelayTime::create(0.75), nullptr));
		m_endSprite->runAction(Sequence::create(
			MoveTo::create(kBlockSwapTime, departure),
			DelayTime::create(0.75), nullptr));
		return true;
	}
	swapSprite();
	m_startSprite->runAction(Sequence::create(
		MoveTo::create(kBlockSwapTime, destination),
		MoveTo::create(kBlockSwapTime, departure),
		DelayTime::create(0.75), nullptr));
	m_endSprite->runAction(Sequence::create(
		MoveTo::create(kBlockSwapTime, departure),
		MoveTo::create(kBlockSwapTime, destination),
		DelayTime::create(0.75), nullptr));
	return false;
}

// mainly designed to identify the special sprites and refresh
// the ignorance, isneedremove and particle effcts
void GameScene::processMatch(std::list<SpriteShape*>
	& matchList, SpriteStatus matchType)
{
	// mark and set status for all of the blocks in a manully match
	SpriteShape* sprite = nullptr;
	bool isThereSpriteIgnored = false;

	for (std::list<SpriteShape*>::iterator iterList = matchList.begin();
		iterList != matchList.end(); iterList++)
	{
		sprite = *iterList;

		if (sprite == nullptr)
			continue;
		else if (matchType != Normal)
		{
			if ((sprite == m_startSprite || sprite == m_endSprite)
				&& sprite->getStatus() == Normal)
			{
				// ignore and remain the special block
				isThereSpriteIgnored = true;
				sprite->setIsIgnored(true);
				sprite->setIsNeedRemove(false);

				sprite->setStatus(matchType);
				sprite->getParticle()->setPosition(
					m_scaleRatioX * kSpriteWidth / 2,
					m_scaleRatioY * kSpriteHeight / 2);
				continue;
			}
		}

		markRemove(sprite);
	}

	// set status for all of the automatically droped matches
	if (!isThereSpriteIgnored && matchType != Normal)
	{
		sprite->setIsIgnored(true);
		sprite->setIsNeedRemove(false);
		sprite->setStatus(matchType);
		sprite->getParticle()->setPosition(
			m_scaleRatioX * kSpriteWidth / 2,
			m_scaleRatioY * kSpriteHeight / 2);
	}
}


// limitation by remaining time
void GameScene::timer(float dt)
{
	m_time--;
	cocos2d::Label* limit = dynamic_cast <cocos2d::Label*>(
		this->getChildByName("limitTimes"));
	int currentgoal = UD_getInt("Goal");
	if (m_score >= currentgoal)
	{
		int current_diff = UD_getInt("gamediff");
		increaseDiff(current_diff);
	}
	if (m_time > 0)
	{
		limit->setString(StringUtils::format("Time : %d", m_time));
		return;
	}
	else
	{
		limit->setScale(0);
		auto gameover = Sprite::create("image/GameOverA.png");
		gameover->setPosition(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height * 1.2);
		gameover->runAction(MoveTo::create(0.5, Point(
			m_origin.x + m_visibleSize.width / 2,
			m_origin.y + m_visibleSize.height / 2)));
		this->addChild(gameover, 1);

		gameOver(0);
	}
	return;
}

void GameScene::scorer(int num)
{
	m_score += num * 50;
	if (num >= 6 && num < 8)
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("music/excellent.mp3", false);
	}
	else if (num >= 8)
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("music/excellent.mp3", false);
	}
	cocos2d::Label* score = dynamic_cast<cocos2d::Label*>(
		this->getChildByName("scoreLable"));
	score->setString(StringUtils::format("Score: %d", m_score));

	//add loadingbar
	auto loadingBar = ui::LoadingBar::create("load_bar2.png");
	if (loadingBar == nullptr)
	{
		problemLoading("load_bar2.png");
	}
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent((100 * m_score) / UD_getInt("Goal"));
	loadingBar->setPosition(Vec2(
		m_visibleSize.width / 2 + 150 * m_scaleRatioX,
		m_visibleSize.height / 2 + 370 * m_scaleRatioY));
	this->addChild(loadingBar, 20);

}

// limitation by remaining steps
void GameScene::pedometer()
{
	m_steps--;
	cocos2d::Label* limit = dynamic_cast <cocos2d::Label*>(
		this->getChildByName("limitSteps"));
	int currentgoal = UD_getInt("Goal");
	if (m_score >= currentgoal)
	{
		int current_diff = UD_getInt("gamediff");
		increaseDiff(current_diff);
	}
	if (m_steps > 0)
		limit->setString(StringUtils::format("Steps : % d", m_steps));
	else
	{
		limit->setScale(0);
	}
}

void GameScene::increaseDiff(int diff)
{
	int m_goal = UD_getInt("Goal");
	UD_setInt("gamediff", diff + 1);
	UD_setInt("Goal", m_goal + 2000);
	auto scene = GameScene::create();
	this->removeFromParent();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(kTransitionTime, scene));
}

// replace to gameover scene
void GameScene::gameOver(float dt)
{
	auto scene = GameOver::createScene();
	this->removeFromParent();
	Director::getInstance()->replaceScene(
		TransitionMoveInR::create(kTransitionTime, scene));
}

void GameScene::explodeHorizontal(SpriteShape* const sprite)
{
	// play the particle effects for horizontal clear

	auto explodeParticle = CCParticleSystemQuad::create(
		"plist/ExplodeHorizon.plist");
	explodeParticle->setPosition(0, sprite->getPosition().y);
	explodeParticle->runAction(MoveTo::create(kTransitionTime,
		Point(2 * m_visibleSize.width, sprite->getPosition().y)));
	this->addChild(explodeParticle, 2);
	explodeParticle->setAutoRemoveOnFinish(true);

	int const row = sprite->getRow();
	SpriteShape* otherSprite = nullptr;
	for (int col = 0; col < getCols(); col++)
	{
		otherSprite = findSprite(row, col);
		explodeSprite(otherSprite);
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/HandV.mp3", false);

}

void GameScene::explodeVertical(SpriteShape* sprite)
{
	auto explodeParticle = CCParticleSystemQuad::create(
		"plist/ExplodeVertical.plist");
	explodeParticle->setPosition(sprite->getPosition().x, 0);
	explodeParticle->runAction(MoveTo::create(kTransitionTime,
		Point(sprite->getPosition().x, 2 * m_visibleSize.height)));
	this->addChild(explodeParticle, 2);
	explodeParticle->setAutoRemoveOnFinish(true);

	int const col = sprite->getCol();
	SpriteShape* otherSprite = nullptr;
	for (int row = 0; row < getRows(); row++)
	{
		otherSprite = findSprite(row, col);
		explodeSprite(otherSprite);
	}

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/HandV.mp3", false);
}

void GameScene::explodeGlobal(SpriteShape* sprite)
{
	auto explodeParticle = CCParticleSystemQuad::create(
		"plist/ExplodeGlobal.plist");
	explodeParticle->setPosition(sprite->getPosition());
	explodeParticle->runAction(RotateBy::create(1, 3, 3));

	explodeParticle->setAutoRemoveOnFinish(true);
	this->addChild(explodeParticle, 1);


	SpriteShape* otherSprite = nullptr;
	auto const index = sprite->getImageIndex();
	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			otherSprite = findSprite(row, col);
			if (otherSprite != nullptr)
				if (index == otherSprite->getImageIndex())
					explodeSprite(otherSprite);
		}
}

void GameScene::setGameMode()
{
	int const mode = UD_getInt("Gamemode");
	if (mode == 0)
		m_gamemode = Steps;
	else if (mode == 1)
		m_gamemode = Times;
	else
		m_gamemode = Creative;
}

void GameScene::setIndexRange()
{
	int group = UD_getInt("Group");
	switch (group)
	{
	case 1:
		m_startIndex = 0;
		m_endIndex = 3;
		break;
	case 2:
		m_startIndex = 4;
		m_endIndex = 7;
		break;
	case 3:
		m_startIndex = 8;
		m_endIndex = 11;
		break;
	default:
		m_startIndex = 0;
		m_endIndex = 3;
		break;
	}
}

void GameScene::setResolutionScale()
{
	auto const winSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_scaleRatioX = winSize.width / kDesignResolutionWidth;
	m_scaleRatioY = winSize.height / kDesignResolutionHeight;
}

SpriteShape* GameScene::findSprite(int row, int col)
{
	BlockMap::iterator iter;
	iter = m_blocks.find(Point(row, col));
	if (iter != m_blocks.end())
		return ((*iter).second);
	return nullptr;
}

SpriteShape* GameScene::findSprite(const Point& point)
{
	SpriteShape* sprite = nullptr;
	Rect rectangle = Rect(0, 0, 0, 0);
	for (int row = 0; row < getRows(); row++)
		for (int col = 0; col < getCols(); col++)
		{
			sprite = findSprite(row, col);
			if (sprite != nullptr)
			{
				rectangle.origin.set(
					sprite->getPositionX() - m_scaleRatioX * kSpriteWidth / 2,
					sprite->getPositionY() - m_scaleRatioY * kSpriteHeight / 2);
				rectangle.size.setSize(
					m_scaleRatioX * kSpriteWidth,
					m_scaleRatioY * kSpriteHeight);
				if (rectangle.containsPoint(point))
				{
					return sprite;
				}
			}
		}
	return nullptr;
}

void GameScene::setBlockOriginPosition()
{
	m_blockOrigin.x = m_origin.x + m_visibleSize.width / 2 -
		(m_scaleRatioX * kSpriteWidth + m_scaleRatioX * kBorderWidth) * m_cols / 2;
	m_blockOrigin.y = m_origin.y + m_visibleSize.height / 2 -
		(m_scaleRatioY * kSpriteHeight + m_scaleRatioY * kBorderWidth) * m_rows / 2;
}

void  GameScene::problemLoading(const char* filename) noexcept
{
	printf("Error while loading: %s\n", filename);
}

void GameScene::actionEndCallback(Node* node)
{
	SpriteShape* sprite =
		dynamic_cast<SpriteShape*>(node);
	m_blocks.erase(Point(sprite->getRow(), sprite->getCol()));
	// sprite are finally destroyed here
	sprite->removeFromParent();
}

bool GameScene::touchBeganCallback(Touch* touch, Event* event)
{
	CCLOG("Touch Begin!");
	m_startSprite = nullptr;
	m_endSprite = nullptr;
	if (m_enableOperation)
	{
		auto const location = touch->getLocation();
		// there's proper convert function from Vec2 to Point
		m_startSprite = findSprite(location);
		return true;
	}
	return false;
}

void GameScene::touchEndCallback(Touch* touch, Event* event)
{
	if (m_startSprite == nullptr || !m_enableOperation)
	{
		return;
	}

	// check the direction the user pointed to
	int row = m_startSprite->getRow();
	int col = m_startSprite->getCol();
	Point location = touch->getLocation();

	auto const upRec = Rect(
		m_startSprite->getPositionX() - m_scaleRatioX * kSpriteWidth / 2,
		m_startSprite->getPositionY() + m_scaleRatioY * kSpriteHeight / 3,
		m_scaleRatioX * kSpriteWidth, m_scaleRatioY * kSpriteHeight);
	auto const downRec = Rect(
		m_startSprite->getPositionX() - m_scaleRatioX * kSpriteWidth / 2,
		m_startSprite->getPositionY() - (m_scaleRatioY * kSpriteHeight / 2) * 3,
		m_scaleRatioX * kSpriteWidth, m_scaleRatioY * kSpriteHeight);
	auto const leftRec = Rect(
		m_startSprite->getPositionX() - (m_scaleRatioX * kSpriteWidth / 2) * 3,
		m_startSprite->getPositionY() - m_scaleRatioY * kSpriteHeight / 2,
		m_scaleRatioX * kSpriteWidth, m_scaleRatioY * kSpriteHeight);
	auto const rightRec = Rect(
		m_startSprite->getPositionX() + m_scaleRatioX * kSpriteWidth / 2,
		m_startSprite->getPositionY() - m_scaleRatioY * kSpriteHeight / 2,
		m_scaleRatioX * kSpriteWidth, m_scaleRatioY * kSpriteHeight);

	if (upRec.containsPoint(location))
		row++;
	else if (downRec.containsPoint(location))
		row--;
	else if (leftRec.containsPoint(location))
		col--;
	else if (rightRec.containsPoint(location))
		col++;
	m_endSprite = findSprite(row, col);

	if (swapMatch() && m_gamemode == 0)
	{
		pedometer();
	}

	return;
}
void GameScene::menuHomeCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = HelloWorld::createScene();
	this->removeFromParent();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::gamePauseCallback(Ref* pSender)
{
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	if (m_gamemode == Times)
	{
		this->unschedule(schedule_selector(GameScene::timer));
	}
	Dialog* dialog = Dialog::create();
	dialog->setTitle("Pause", 45);
	dialog->setBackground("button/DialogBackground.png");
	dialog->setContent("What to do?", 40);
	dialog->addButton("button/ResumeNormal.png", "button/ResumePressed.png", 2,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	dialog->addButton("button/ExitNormal.png", "button/ExitPressed,png", 3,
		Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2 - 80 * m_scaleRatioX));
	dialog->setCallbackFunc(this, callfuncN_selector(
		GameScene::dialogButtonCallback));
	addChild(dialog, 3);
}

void GameScene::dialogButtonCallback(Node* pNode)
{
	CCASSERT(pNode != nullptr, "Node is a null pointer");
	_eventDispatcher->resumeEventListenersForTarget(this, true);
	if (pNode->getTag() == 2) 
		if (m_gamemode == Times)
		{
			schedule(schedule_selector(GameScene::timer), 1.0f);
		}
	if (pNode->getTag() == 3)
	{
		gameOver(0);
	}
}

void GameScene::menuSettingCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	auto scene = SettingScene::createScene();
	Director::getInstance()->pushScene(scene);
}
