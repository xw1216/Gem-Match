#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "LevelSelect.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SettingScene);

	virtual bool init();

	void menuBackCallback(Ref* pSender);
	void menuBackHomeCallback(Ref* pSender);
	void audioMuteCallback(Ref* pSender);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}

};



#endif // !__SETTINGS_SCENE_H__
