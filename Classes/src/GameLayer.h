#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include <cocos2d.h>
#include "GridItem.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameLayer);

	int leftRowAdd();

	int rightRowAdd();

	int upColAdd();

	int downColAdd();

	void randomCreate();

	int getScore();

	void reset();
private:
	float BG_WIDTH_HEIGHT;
	void initBg();
	int _score;
	int setScore(int score);
	bool hasOver();
	Point _beginPoint;
	Point _endPoint;
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	GridItem* _gridVec[4][4];
};

#endif