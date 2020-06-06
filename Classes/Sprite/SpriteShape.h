#ifndef  __SPRITE_SHAPE__
#define __SPRITE_SHAPE__

#include "cocos2d.h"
#include "time.h"
#include "GameDefine.h"

USING_NS_CC;

class SpriteShape : public Sprite
{
public:
	static SpriteShape* create(int row, int col, int index);
	SpriteShape() noexcept;

	bool getIsNeedRemove() noexcept 
			{ return m_isNeedRemove; }
	void setIsNeedRemove(bool boolean) noexcept
			{ m_isNeedRemove = boolean; }
	bool getIsIgored() { return m_isIgnored; }
	void setIsIgnored(bool isIgnored) { m_isIgnored = isIgnored; }

	SpriteStatus getStatus() { return m_status; }
	void setStatus(SpriteStatus status);
	ParticleSystem* getParticle() { return m_particle; };

	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imageIndex, ImageIndex);

private:
	bool m_isNeedRemove;
	bool m_isIgnored;
	SpriteStatus m_status;
	ParticleSystem * m_particle;

};
#endif // ! __SPRITE_SHAPE__