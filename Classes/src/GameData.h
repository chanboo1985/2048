#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <cocos2d.h>
USING_NS_CC;
class GameData
{
public:
	static GameData* getInstance();
	void setHistoryScore(int score);
	int getHistoryScore();
private:
	GameData();
	void init();
private:
	static GameData* _gameData;
	int history_score;
};

#endif