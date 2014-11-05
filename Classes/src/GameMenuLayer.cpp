#include "GameMenuLayer.h"
#include "GameScene.h"

bool GameMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	//不向下传递触摸
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch, Event *unused_event){
		CCLog("override touch began");
		return true;
	};
	listener->onTouchEnded = [](Touch *touch, Event *unused_event){
		CCLog("override touch ended");
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	auto layer = LayerColor::create(Color4B(230,230,0,200));
	this->addChild(layer);
	auto playmenu = MenuItemLabel::create(Label::create("play","Arial",60),CC_CALLBACK_1(GameMenuLayer::callFun,this));
	auto resetmenu = MenuItemLabel::create(Label::create("reset","Arial",60),CC_CALLBACK_1(GameMenuLayer::resetGameFun,this));
	auto menu = Menu::create(playmenu,resetmenu,NULL);
	menu->alignItemsVertically();
	this->addChild(menu);
	return true;
}

void GameMenuLayer::callFun(Ref* ref)
{
	GameScene::getInstance()->playFun();
}

void GameMenuLayer::resetGameFun(Ref* ref)
{
	GameScene::getInstance()->resetGameFun();
}