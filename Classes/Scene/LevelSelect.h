#ifndef __LEVEL_SELECT_H__
#define __LEVEL_SELECT_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Layer/Dialog.h"

USING_NS_CC;

class LevelSelect : public cocos2d::Scene
{
public:
	// Create Function
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LevelSelect);

	virtual bool init();

	Menu* addButtonItem(const char* image, const Vec2 position,
		const ccMenuCallback& callback);
	void popDialog(GameMode mode, SEL_CallFuncN callfunc);

	// Selector Callback
	void menuBackCallback(Ref* pSender);
	void gameRankCallback(Ref* pSender);
	void timeModeCallback(Ref* pSender);
	void stepModeCallback(Ref* pSender);
	void creativeModeCallback(Ref* pSender);
	void dialogButtonCallback(Node* pNode);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}
};

#endif // __LEVEL_SELECT_H__