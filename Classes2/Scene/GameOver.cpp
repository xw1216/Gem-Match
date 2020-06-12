//胜利的欢呼声 许可:CC-BY 作者:chripei 来源:耳聆网 https://www.ear0.com/sound/19472
#include "GameOver.h"
#include<string>
using namespace std;

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
	}
}

void GameOver::setScore(int score) noexcept
{
	int highestScore = CCUserDefault::sharedUserDefault()->
		getIntegerForKey("highestScore");
	if(score>highestScore)
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