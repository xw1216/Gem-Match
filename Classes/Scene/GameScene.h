#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"
#include "Layer/Dialog.h"
#include "LevelSelect.h"
#include "GameOver.h"
#include "GameDefine.h"
#include "Sprite\SpriteShape.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	typedef std::map <Point, SpriteShape* > BlockMap;
	typedef std::pair<Point, SpriteShape*> BlockPair;
	
	// three game mode are designed 
	// and could be selected in levelselect

	GameScene() noexcept;
	// create related function
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);

	// initiallization related function
	virtual bool init();
	void initMap();
	void createSprite(int row, int col,int index);
	void initLimit();
	void initScorer();

	// calculate the position of the drop blocks and existing blocks
	Point positionOfAnimateItem(Point point);
	Point positionOfItem(int row, int col);

	// scheduled to update the scene every frame 
	void update(float dt);

	// running blocks check
	// check matchs and remove sprites
	void checkAndRemove();
	void markRemove  (SpriteShape* sprite) noexcept;
	void removeSprite();
	void explodeSprite(SpriteShape* sprite);
	void colCheck(SpriteShape* sprite, std::list< SpriteShape*>& colChain);
	void rowCheck(SpriteShape* sprite, std::list< SpriteShape*>& rowChain);
	// fill in the blanks of the removed sprites
	void fillSprite();

	// response when user exchange blocks
	// then check and process match
	void swapSprite();
	bool swapMatch();
	void processMatch(std::list<SpriteShape*> 
		& matchList, SpriteStatus matchType);

	// game design functions
	void timer(float dt);
	void scorer(int num);
	void pedometer();

	// replace scene to gameover
	void gameOver(float dt);
	/*void rankList(float dt);*/

	// impletation of the row or col clear sprite
	void explodeHorizontal(SpriteShape* sprite);
	void explodeVertical(SpriteShape* sprite);
	void explodeGlobal(SpriteShape* sprite);

	// set, get and find  functions
	void setGameMode();
	SpriteShape* findSprite(int row, int col);
	SpriteShape* findSprite(const Point& point);
	int getDifficulty() noexcept { return m_difficulty; } const
	void setDifficulty(int num) noexcept { m_difficulty = num; }
	void setBlockOriginPosition();
	void  problemLoading(const char* filename) noexcept;
	
	// callbacks
	void menuSettingCallback(Ref* pSender);
	void menuHomeCallback(Ref* pSender);
	void gamePauseCallback(Ref* pSender);
	void dialogButtonCallback(Node* pNode);
	void actionEndCallback(Node* node);
	bool touchBeganCallback(Touch* touch, Event* event);
	void touchEndCallback(Touch* touch, Event* event);
	
	// protected varieble
	CC_SYNTHESIZE(int, m_time, times);
	CC_SYNTHESIZE(int, m_steps, steps);
	CC_SYNTHESIZE(int, m_rows, Rows);
	CC_SYNTHESIZE(int, m_cols, Cols);

private:
	// instance status varieble, used in frame update
	bool m_isAction;
	bool m_isFillSprite;
	bool m_enableOperation;

	
	// game setting data
	// user can customize them in the future
	GameMode m_gamemode;
	int m_difficulty;
	int m_score;

	// data to identify the swap and special sprites
	SpriteShape* m_startSprite, * m_endSprite;

	// the origin point of the blocks map 
	// can be revised based on the number of rows and cols
	Point m_blockOrigin;

	// store all of the existing sprites
	BlockMap m_blocks;
};

#endif // !__GAME_SCENE__