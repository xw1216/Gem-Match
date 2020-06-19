#ifndef _RANK_SCENE_
#define _RANK_SCENE_
#include "cocos2d.h"

USING_NS_CC;

class RankScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	// implement the "static create()" method manually
	CREATE_FUNC(RankScene);

	virtual bool init();


	// selector callback

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);

	void problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}

};
#endif //_RANK_SCENE_


