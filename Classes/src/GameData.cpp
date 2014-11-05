#include "GameData.h"
#include <cocos2d.h>
USING_NS_CC;

GameData::GameData()
{
	this->init();
}

GameData* GameData::_gameData = nullptr;
GameData* GameData::getInstance()
{
	if (!_gameData)
	{
		_gameData = new GameData;
	}
	return _gameData;
}

void GameData::init()
{
	history_score = 0;
	setHistoryScore(UserDefault::getInstance()->getIntegerForKey("history_score",0));
}

void GameData::setHistoryScore(int score)
{
	history_score = score;
	UserDefault::getInstance()->setIntegerForKey("history_score",history_score);
}

int GameData::getHistoryScore()
{
	return history_score;
}