

#ifndef __ttgame__Card__
#define __ttgame__Card__

#include "cocos2d.h"

using namespace cocos2d;
class Card :public Node
{
public:
	int number;//数字编号 怪物编号
	int row, col;
	bool canRemove;//是否要消除
	Sprite* sp;
	CREATE_FUNC(Card);
	static Card* createCard(int num, int r, int c);
	bool init();
	void moveTo(int r, int c);
};
#endif /* defined(__ttgame__Card__) */
