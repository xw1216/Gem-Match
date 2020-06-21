#ifndef  __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;


class Dialog :public cocos2d::Layer
{
public:
	Dialog();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Dialog);

	virtual bool init();
	virtual void onEnter();

	bool addButton(const char* normalImage, const char* seletedImage,
		const char* button_title, int tag, Vec2 position);
	bool addButton(const char* normalImage, const char* selectedImage,
		int tag, Vec2 position);

	void setBackground(const char* backgroundImage);

	void setTitle(const char* titles, int fontSize);
	const char* getTitle();
	int getTitleSize();

	void setContent(const char* contents, int fontSize);
	const char* getContentLabel();
	int getContentFontSize();

	void setResolutionScale();
	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);
	void buttonCallback(Ref* pSender);

	CCObject* m_callbackLisner;
	SEL_CallFuncN m_callback;
	Size m_size;

private:
	Sprite* background;
	Menu* menu;
	Vector<Node*> node;
	const char* m_title;
	const char* m_content;
	int m_titleFontSize;
	int m_contentFontSize;
	Sprite* m_sprite;
	const char* m_backgroundImage;
	Vec2 m_origin;
	Size m_visibleSize;
	float m_scaleRatioX, m_scaleRatioY;

};

#endif // !__DIALOG_H__
