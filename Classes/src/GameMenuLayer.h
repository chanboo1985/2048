#ifndef __GAME_MENU_lAYER_H__
#define __GAME_MENU_lAYER_H__
#include <cocos2d.h>
USING_NS_CC;
class GameMenuLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameMenuLayer);
private:
	void resetGameFun(Ref* ref);

	void callFun(Ref* ref);
};

#endif