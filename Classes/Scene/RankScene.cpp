#include "RankScene.h"
#include "GameDefine.h"
#include <string>

USING_NS_CC;

cocos2d::Scene* RankScene::createScene()
{
	return RankScene::create();
}
bool RankScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto const visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();
	TTFConfig config("fonts/FZCHSJW.ttf", 20);
	//add background
	auto background = Sprite::create("Background.png");
	if (background == nullptr)
	{
		problemLoading("Background.png");
	}
	else
	{
		background->setPosition(Vec2(kDesignResolutionWidth / 2, kDesignResolutionHeight / 2));
		this->addChild(background, -20);
	}
	//add back buttton
	auto backItem = MenuItemImage::create(
		"icon/Back.png", "icon/Back.png",
		CC_CALLBACK_1(RankScene::menuBackCallback, this));
	if (backItem == nullptr)
		problemLoading("'icon/Back.png', 'icon/Back.png'");
	else
	{
		float const x = backItem->getContentSize().width;
		float const y = backItem->getContentSize().height;
		backItem->setPosition(Vec2(x, y));
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setPosition(Vec2::ZERO);
		this->addChild(backMenu, 1);
	}

	//add three label
	auto label_fir = Label::createWithTTF("Highest!", "fonts/FZCHSJW.ttf", 35);
	if (label_fir == nullptr)
	{
		problemLoading("'fonts/arial.ttf'");
	}
	else
	{
		label_fir->setPosition(Vec2(origin.x + visibleSize.width / 3,
			origin.y + visibleSize.height - 4 * (label_fir->getContentSize().height)));
		label_fir->setColor(Color3B::Color3B(0,0,0));

		// add the label as a child to this layer
		this->addChild(label_fir, 1);
	}

	std::string fir_name = UD_getString("p1_name");
	const char* fir_n = fir_name.c_str();
	std::string fir_mode = UD_getString("p1_mode");
	const char* fir_m = fir_mode.c_str();
	int fir_score=UD_getInt("p1_score");
	if (fir_mode == "Steps")
	{
		CCLOG("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
	}


	cocos2d::Label* fir_Lable_name = nullptr;
	fir_Lable_name = Label::createWithTTF(
		config, StringUtils::format("name : %s", fir_n));

	cocos2d::Label* fir_Label_mode = nullptr;
	fir_Label_mode = Label::createWithTTF(
		config, StringUtils::format("mode : %s", fir_m));

	cocos2d::Label* fir_Lable_score = nullptr;
	fir_Lable_score = Label::createWithTTF(
		config, StringUtils::format("score :   %d", fir_score));


	fir_Label_mode->setColor(Color3B::BLACK);
	fir_Label_mode->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 4 * (label_fir->getContentSize().height) - 30));
	this->addChild(fir_Label_mode);

	fir_Lable_name->setColor(Color3B::BLACK);
	fir_Lable_name->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 4 * (label_fir->getContentSize().height)+10));
	this->addChild(fir_Lable_name);


	fir_Lable_score->setColor(Color3B::BLACK);
	fir_Lable_score->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 4 * (label_fir->getContentSize().height)-10));
	this->addChild(fir_Lable_score);







	auto label_sec = Label::createWithTTF("Second!", "fonts/FZCHSJW.ttf", 35);
	if (label_sec == nullptr)
	{
		problemLoading("'fonts/FZCHSJW.ttf'");
	}
	else
	{
		label_sec->setPosition(Vec2(origin.x + visibleSize.width / 3,
			origin.y + visibleSize.height - 10 * (label_sec->getContentSize().height)));
		label_sec->setColor(Color3B::Color3B(0,0,0));

		// add the label as a child to this layer
		this->addChild(label_sec, 1);
	}

	std::string sec_name = UD_getString("p2_name");
	const char* sec = sec_name.c_str();
	std::string sec_mode = UD_getString("p2_mode");
	const char* sec_m = sec_mode.c_str();
	int sec_score = UD_getInt("p2_score");

	if (sec_m == "Steps")
	{
		CCLOG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	}
	cocos2d::Label* sec_Lable_name = nullptr;
	sec_Lable_name = Label::createWithTTF(
		config, StringUtils::format("name : %s", sec));

	cocos2d::Label* sec_Label_mode = nullptr;
	sec_Label_mode = Label::createWithTTF(
		config, StringUtils::format("mode : %s", sec_m));

	cocos2d::Label* sec_Lable_score = nullptr;
	sec_Lable_score = Label::createWithTTF(
		config, StringUtils::format("score : %d", sec_score));



	sec_Label_mode->setColor(Color3B::BLACK);
	sec_Label_mode->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 10 * (label_fir->getContentSize().height) - 30));
	this->addChild(sec_Label_mode);

	sec_Lable_name->setColor(Color3B::BLACK);
	sec_Lable_name->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 10 * (label_fir->getContentSize().height) + 10));
	this->addChild(sec_Lable_name);


	sec_Lable_score->setColor(Color3B::BLACK);
	sec_Lable_score->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 10 * (label_fir->getContentSize().height) -10));
	this->addChild(sec_Lable_score);


	auto label_thi = Label::createWithTTF("Third!", "fonts/FZCHSJW.ttf", 35);
	if (label_thi == nullptr)
	{
		problemLoading("'fonts/FZCHSJW.ttf'");
	}
	else
	{
		label_thi->setPosition(Vec2(origin.x + visibleSize.width / 3,
			origin.y + visibleSize.height - 16 * (label_thi->getContentSize().height)));
		label_thi->setColor(Color3B::Color3B(0,0,0));

		// add the label as a child to this layer
		this->addChild(label_thi, 1);
	}
	std::string thi_name = UD_getString("p3_name");
	const char* thi = thi_name.c_str();
	std::string thi_mode = UD_getString("p2_mode");
	const char* thi_m = thi_mode.c_str();
	int thi_score = UD_getInt("p3_score");


	cocos2d::Label* thi_Lable_name = nullptr;
	thi_Lable_name = Label::createWithTTF(
		config, StringUtils::format("name : %s", thi));

	cocos2d::Label* thi_Label_mode = nullptr;
	thi_Label_mode = Label::createWithTTF(
		config, StringUtils::format("mode : %s", thi_m));

	cocos2d::Label* thi_Lable_score = nullptr;
	thi_Lable_score = Label::createWithTTF(
		config, StringUtils::format("score : %d", thi_score));



	thi_Label_mode->setColor(Color3B::BLACK);
	thi_Label_mode->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 16 * (label_fir->getContentSize().height) - 30));
	this->addChild(thi_Label_mode);

	thi_Lable_name->setColor(Color3B::BLACK);
	thi_Lable_name->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 16 * (label_fir->getContentSize().height) + 10));
	this->addChild(thi_Lable_name);


	thi_Lable_score->setColor(Color3B::BLACK);
	thi_Lable_score->setPosition(Vec2(origin.x + 2 * visibleSize.width / 3,
		origin.y + visibleSize.height - 16 * (label_fir->getContentSize().height) - 10));
	this->addChild(thi_Lable_score);

}
void RankScene::menuBackCallback(cocos2d::Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("music/normalclick.mp3", false);
	Director::getInstance()->popScene();
}
