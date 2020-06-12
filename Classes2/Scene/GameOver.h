#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "LevelSelect.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameOver);

	virtual bool init();

	void setScore(int score) noexcept;

	void levelSelectBackCallback(Ref* pSender);
	void gameStartCallback(Ref* pSender);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}
};


#endif // !__GAME_OVER_H__
