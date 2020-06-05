#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#include "cocos2d.h"

// The default resolution of the game
constexpr int kDesignResolutionWidth = 540;
constexpr int kDesignResolutionHeight = 960;

constexpr int kSpriteNum = 12;
constexpr int kSpriteWidth = 80, 
					  kSpriteHeight = 80;

constexpr int kBorderWidth = 4;
constexpr float kTransitionTime = 0.75;

// The image of all blocks
constexpr char* spriteNormal[kSpriteNum] =
{
	"BlockA.png","BlockB.png","BlockC.png",
	"BlockD.png","BlockE.png","BlockF.png",
	"BlockG.png","BlockH.png","BlockI.png",
	"BlockJ.png","BlockK.png","BlockL.png"
};

#endif // !__GAME_DEFINE__