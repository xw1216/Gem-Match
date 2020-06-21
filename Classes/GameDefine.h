#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

USING_NS_CC;

// The default resolution of the game
constexpr int kDesignResolutionWidth = 540;
constexpr int kDesignResolutionHeight = 960;

constexpr int kSpriteNum = 12;
constexpr int kSpriteWidth = 80,
kSpriteHeight = 80;
constexpr int kIconlength = 50;

constexpr int kBorderWidth = 4;
constexpr float kTransitionTime = 0.75;
constexpr float kBlockSwapTime = 0.25;

// The image of all blocks
constexpr char* spriteNormal[kSpriteNum] =
{
	"BlockA.png","BlockB.png","BlockC.png",
	"BlockD.png","BlockE.png","BlockF.png",
	"BlockG.png","BlockH.png","BlockI.png",
	"BlockJ.png","BlockK.png","BlockL.png"
};

enum GameMode { Steps = 0, Times = 1, Creative = 2 };
enum SpriteStatus { Normal = 0, Horizontal, Vertical, Global };

//for ranklist
#define max_range 5

#define UD_getInt CCUserDefault::sharedUserDefault()->getIntegerForKey 
#define UD_getBool CCUserDefault::sharedUserDefault()->getBoolForKey 
#define UD_getFloat CCUserDefault::sharedUserDefault()->getFloatForKey 
#define UD_getDouble CCUserDefault::sharedUserDefault()->getDoubleForKey 
#define UD_getString CCUserDefault::sharedUserDefault()->getStringForKey 

#define UD_setInt CCUserDefault::sharedUserDefault()->setIntegerForKey 
#define UD_setBool CCUserDefault::sharedUserDefault()->setBoolForKey 
#define UD_setFloat CCUserDefault::sharedUserDefault()->setFloatForKey 
#define UD_setDouble CCUserDefault::sharedUserDefault()->setDoubleForKey 
#define UD_setString CCUserDefault::sharedUserDefault()->setStringForKey 

#endif // !__GAME_DEFINE__