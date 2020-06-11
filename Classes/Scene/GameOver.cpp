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

		auto label = Label::createWithTTF("GemMatch!", "fonts/FZCHSJW.ttf", 40);
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
		}
	}
}

void GameOver::setScore(int score) noexcept
{
	int highestScore = CCUserDefault::sharedUserDefault()->
		getIntegerForKey("highestKey");
	if(score>highestScore)
		CCUserDefault::sharedUserDefault()->
		setIntegerForKey("highestScore", score);
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