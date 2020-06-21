#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Scene/LevelSelect.h"
#include "Scene/SettingScene.h"

class HelloWorld : public cocos2d::Scene
{
public:
    HelloWorld();
    ~HelloWorld() {}
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual bool init();

    void setResolutionScale();
    // selector callback
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuSettingCallback(cocos2d::Ref* pSender);

    void problemLoading(const char* filename) noexcept
    {
        printf("Error while loading: %s\n", filename);
    }
private:
    Vec2 m_origin;
    Size m_visibleSize;
    float m_scaleRatioX, m_scaleRatioY;

};

#endif // __HELLOWORLD_SCENE_H__
