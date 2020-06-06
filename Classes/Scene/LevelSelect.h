#ifndef __LEVEL_SELECT_H__
#define __LEVEL_SELECT_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class LevelSelect : public cocos2d::Scene
{
public:
	// Create Function
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LevelSelect);

	virtual bool init();

	// Selector Callback
	void menuBackCallback(Ref* pSender);
	void gameStartCallback(Ref* pSender);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}
};

#endif // __LEVEL_SELECT_H__
