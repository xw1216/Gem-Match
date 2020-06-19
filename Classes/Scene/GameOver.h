#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "LevelSelect.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

struct Player
{
	std::string name;
	int score;
};

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameOver);

	virtual bool init();

	void setScore(int score) noexcept;
	void getScore(int score) { finalScore = score; };

	void levelSelectBackCallback(Ref* pSender);
	void gameStartCallback(Ref* pSender);

	bool touchBeganCallback(Touch* touch, Event* event);
	void menuSubmitCallback(Ref* pSender);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}
private:
	TextFieldTTF* textEdit;
	int finalScore;
	Player p[max_range + 1];
};


#endif // !__GAME_OVER_H__
