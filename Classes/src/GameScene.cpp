#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::getInstance();
	scene->addChild(layer);
	return scene;
}

GameScene* GameScene::_layer = nullptr;
GameScene* GameScene::getInstance()
{
	if (!_layer)
	{
		_layer = GameScene::create();
	}
	return _layer;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initBg();
	scheduleUpdate();
	return true;
}

void GameScene::initBg()
{
	this->addChild(LayerColor::create(Color4B(0,0,0,0)));

	gameLayer = GameLayer::create();
	gameLayer->setPosition(50,50);
	gameLayer->randomCreate();
	this->addChild(gameLayer);

	auto layerIcon = LayerColor::create(Color4B(230,230,0,255));
	history_label = Label::create("2048", "Arial", 44);
	history_label->setPosition(50,50);
	layerIcon->setContentSize(Size(100,100));
	layerIcon->setPosition(VisibleRect::leftTop() + Point(50,-150));
	layerIcon->addChild(history_label);
	this->addChild(layerIcon);

	auto scoreIcon = LayerColor::create(Color4B(135,135,135,255));
	auto scorelabel = Label::create("Score", "Arial", 24);
	scorelabel->setPosition(50,35);
	scoreIcon->setContentSize(Size(100,50));
	scoreIcon->setPosition(VisibleRect::leftTop() + Point(200,-100));
	scoreIcon->addChild(scorelabel);

	_scoreLabel = Label::create("0", "Arial", 24);
	_scoreLabel->setPosition(50,10);
	scoreIcon->addChild(_scoreLabel);
	this->addChild(scoreIcon);

	auto setingBg = LayerColor::create(Color4B(135,135,135,255));
	setingBg->setContentSize(Size(100,50));
	auto setinglabel = Label::create("Seting", "Arial", 24);
	setinglabel->setPosition(50,25);
	setingBg->addChild(setinglabel);
	auto menu = MenuItemSprite::create(setingBg,setingBg,CC_CALLBACK_1(GameScene::callFun,this));
	menu->setPosition(10,250);
	this->addChild(Menu::create(menu, NULL));

	gameMenuLayer = nullptr;
}

void GameScene::update(float delay)
{
	char txt[100];
	sprintf(txt,"%d",gameLayer->getScore());
	_scoreLabel->setString(txt);
}

void GameScene::updateHistoryScore(int score)
{
	char txt[64] = {};
	sprintf(txt,"%d",score);
	history_label->setString(txt);
}

void GameScene::callFun(Ref* ref)
{
	if (gameMenuLayer == nullptr)
	{
		gameMenuLayer = GameMenuLayer::create();
	}
	this->addChild(gameMenuLayer);
}

void GameScene::playFun()
{
	removeMenuLayer();
}

void GameScene::resetGameFun()
{
	removeMenuLayer();
	gameLayer->reset();
}

void GameScene::removeMenuLayer()
{
	gameMenuLayer->removeFromParent();
	gameMenuLayer = nullptr;
}