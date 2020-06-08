#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"
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
	enum GameMode{Steps,Times,Creative};

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
	Point positionOfAnimateItem(Point point);
	Point positionOfItem(int row, int col);

	// scheduled to update the scene every frame 
	void update(float dt);

	// running blocks check
	void checkAndRemove();
	void markRemove  (SpriteShape* sprite) noexcept;
	void removeSprite();
	void explodeSprite(SpriteShape* sprite);
	void colCheck(SpriteShape* sprite, std::list< SpriteShape*>& colChain);
	void rowCheck(SpriteShape* sprite, std::list< SpriteShape*>& rowChain);
	void fillSprite();
	void swapSprite();
	bool swapMatch();
	void processMatch(std::list<SpriteShape*> 
		& matchList, SpriteStatus matchType);

	// game design functions
	void timer(float dt);
	void scorer(int num);
	void pedometer();
	void gameOver(float dt);
	void explodeHorizontal(SpriteShape* sprite);
	void explodeVertical(SpriteShape* sprite);

	// set, get and find  functions
	SpriteShape* findSprite(int row, int col);
	SpriteShape* findSprite(const Point& point);
	int getDifficulty() noexcept { return m_difficulty; } const
	void setDifficulty(int num) noexcept { m_difficulty = num; }
	void setBlockOriginPosition();
	void  problemLoading(const char* filename) noexcept;

	// callbacks
	void actionEndCallback(Node* node);
	bool touchBeganCallback(Touch* touch, Event* event);
	void touchEndCallback(Touch* touch, Event* event);
	
	// protected varieble rows and cols
	CC_SYNTHESIZE(int, m_rows, Rows);
	CC_SYNTHESIZE(int, m_cols, Cols);

private:
	bool m_isAction;
	bool m_isFillSprite;
	bool m_enableOperation;
	
	GameMode m_gamemode;
	int m_difficulty;
	int m_steps;
	int m_time;
	int m_score;

	SpriteShape* m_startSprite, * m_endSprite;

	Point m_blockOrigin;
	BlockMap m_blocks;
};

#endif // !__GAME_SCENE__