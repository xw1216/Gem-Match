#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"
// The default resolution of the game
constexpr int kDesignResolutionWidth = 540;
constexpr int kDesignResolutionHeight = 960;

constexpr int kSpriteNum = 12;
constexpr int kSpriteWidth = 80, 
					  kSpriteHeight = 80;

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

enum SpriteStatus { Normal = 0, Horizontal, Vertical };

#endif // !__GAME_DEFINE__