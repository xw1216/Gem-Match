#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "LevelSelect.h"
#include "GameDefine.h"
#include "Layer/Dialog.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

class SettingScene : public cocos2d::Scene
{

public:
	SettingScene() {}
	~SettingScene() {}
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SettingScene);

	virtual bool init() override;
	void setResolutionScale();
	void addMusicControl();
	void addGroupSelect();

	void menuBackCallback(Ref* pSender);
	void menuBackHomeCallback(Ref* pSender);
	void audioMuteCallback(Ref* pSender);
	void sliderCallBack(Ref* pSender);
	
	void groupASelectCallback(Ref* pSender);
	void groupBSelectCallback(Ref* pSender);
	void groupCSelectCallback(Ref* pSender);

	void  problemLoading(const char* filename) noexcept
	{
		printf("Error while loading: %s\n", filename);
	}
private:
	Vec2 m_origin;
	Size m_visibleSize;
	float m_scaleRatioX, m_scaleRatioY;
	Sprite* m_selector;
};

#endif // !__SETTINGS_SCENE_H__
