#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "LevelSelect.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual bool init();
   
    
    // selector callback
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
   
    void problemLoading(const char* filename) noexcept
    {
        printf("Error while loading: %s\n", filename);
    }
};

#endif // __HELLOWORLD_SCENE_H__
