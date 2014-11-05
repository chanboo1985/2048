#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include <cocos2d.h>
#include "VisibleRect.h"
#include "GameLayer.h"
#include "GameMenuLayer.h"
USING_NS_CC;
class GameScene : public Layer
{
public:
	static Scene* createScene();

	static GameScene* getInstance();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void resetGameFun();

	void playFun();

	void callFun(Ref* ref);

	void updateHistoryScore(int score);

private:
	void update(float delay);

	void initBg();

	void removeMenuLayer();

	Label* _scoreLabel;
	Label* history_label;
	static GameScene* _layer;
	GameLayer* gameLayer;
	GameMenuLayer* gameMenuLayer;
};

#endif