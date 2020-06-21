#include "Dialog.h"

Dialog::Dialog() :
	m_title(nullptr),
	m_content(nullptr),
	m_titleFontSize(0),
	m_contentFontSize(0),
	m_callback(nullptr),
	m_callbackLisner(nullptr),
	m_size(0, 0)
{
}

cocos2d::Scene* Dialog::createScene()
{
	auto scene = Scene::create();
	auto layer = Dialog::create();
	scene->addChild(layer, 5);
	return scene;
}

bool Dialog::init()
{
	if (!Layer::init())
	{
		return false;
	}

	setResolutionScale();
	menu = Menu::create();
	node = Vector<Node*>();
	return true;
}

void Dialog::onEnter()
{
	Layer::onEnter();
	background = Sprite::create(m_backgroundImage);
	if (background)
	{
		background->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
		background->setScale(m_scaleRatioX, m_scaleRatioY);
		addChild(background, 1);
		m_size = background->getContentSize();
	}
	
	for (const auto& singleNode : node)
	{
		addChild(singleNode, 2);
	}
	if (getTitle())
	{
		Label* title = Label::create(getTitle(), "fonts/FZCHSJW.ttf", getTitleSize() * m_scaleRatioX);
		title->setColor(Color3B::BLACK);
		title->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2 + 140 * m_scaleRatioY);
		addChild(title, 1);
	}
	if (getContentLabel())
	{
		Label* content = Label::create(getContentLabel(), 
			"fonts/FZCHSJW.ttf", getContentFontSize() * m_scaleRatioX);
		content->setColor(Color3B::BLACK);
		content->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2 + 70 * m_scaleRatioY);
		addChild(content, 1);
	}

	auto action = Spawn::createWithTwoActions(
		ScaleTo::create(1.1, 1.1), FadeIn::create(0.5));
	this->runAction(action);

}

bool Dialog::addButton(const char* normalImage, const char* selectedImage, const char* button_title, int tag, Vec2 position)
{
	MenuItemImage* menuImage = MenuItemImage::create(
		normalImage, selectedImage, this, 
		menu_selector(Dialog::buttonCallback));
	menuImage->setScale(m_scaleRatioX, m_scaleRatioY);
	menuImage->setTag(tag);

	CCSize const menuSize = menuImage->getContentSize();
	LabelTTF* ttf = LabelTTF::create(button_title, "", 25 * m_scaleRatioX);
	ttf->setColor(Color3B::BLACK);
	ttf->setPosition(ccp(menuSize.width / 2, menuSize.height / 2));
	menuImage->addChild(ttf);
	Menu* menu = Menu::create(menuImage, NULL);
	menu->setPosition(position);
	node.pushBack(menu);
	return true;
}

bool Dialog::addButton(const char* normalImage, const char* selectedImage, int tag, Vec2 position)
{
	MenuItemImage* menuImage = MenuItemImage::create(
		normalImage, selectedImage, this, 
		menu_selector(Dialog::buttonCallback));
	menuImage->setScale(m_scaleRatioX, m_scaleRatioY);
	menuImage->setTag(tag);
	Menu* menu = Menu::create(menuImage, NULL);
	menu->setPosition(position);
	node.pushBack(menu);
	return true;
}

void Dialog::setBackground(const char* backgroundImage)
{
	this->m_backgroundImage = backgroundImage;
}

void Dialog::setTitle(const char* titles, int fontSize)
{
	m_title = titles;
	m_titleFontSize = fontSize;
}

const char* Dialog::getTitle()
{
	return m_title;
}

int Dialog::getTitleSize()
{
	return m_titleFontSize;
}

void Dialog::setContent(const char* contents, int fontSize)
{
	m_content = contents;
	m_contentFontSize = fontSize;
}

const char* Dialog::getContentLabel()
{
	return m_content;
}

int Dialog::getContentFontSize()
{
	return m_contentFontSize;
}

void Dialog::setResolutionScale()
{
	auto const winSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_scaleRatioX = winSize.width / kDesignResolutionWidth;
	m_scaleRatioY = winSize.height / kDesignResolutionHeight;
}

void Dialog::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun)
{
	m_callbackLisner = target;
	m_callback = callfun;
}

void Dialog::buttonCallback(Ref* pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
	if (m_callbackLisner || m_callback)
	{
		(m_callbackLisner->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}
