#ifndef _START_GAME_
#define _START_GAME_

#include "cocos2d.h"

class StartGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(StartGame);
};

#endif // _START_GAME_
