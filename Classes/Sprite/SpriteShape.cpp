#include "SpriteShape.h"

SpriteShape* SpriteShape::create(int row, int col, int index)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("plist/Blocks.plist");
	SpriteShape* sprite = new SpriteShape();
	sprite->setRow(row);
	sprite->setCol(col);
	sprite->setImageIndex(index);
	sprite->initWithSpriteFrameName(spriteNormal[sprite->getImageIndex()]);
	
	
	
	// autorealease so that the ownership of sprite can handover easily 
	// and it will be destroyed in GameScene actionEndCallback
	sprite->autorelease(); 
	return sprite;
}

SpriteShape::SpriteShape() noexcept
{
	m_row = 0; m_col = 0;m_imageIndex = 0;
	m_isNeedRemove = false;
	m_status = Normal;
	m_particle = nullptr;
	m_isIgnored = false;
}

void SpriteShape::setStatus(SpriteStatus status)
{
	m_status = status;
	switch (status)
	{
	case Horizontal:
		m_particle = ParticleSystem::create("plist/ParticleHorizental.plist");
		break;
	case Vertical:
		m_particle = ParticleSystem::create("plist/ParticleVerticle.plist");
		break;
	default:
		break;
	}
}
