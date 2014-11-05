#ifndef __GRID_ITEM_H__
#define __GRID_ITEM_H__
#include <cocos2d.h>
USING_NS_CC;
class GridItem : public Node
{
public:
	static GridItem* create(float wh);

	virtual bool init(float wh);

	void setNum(int num);

	int getNum();
private:
	void updateBg();

	float _wh;
	int _num;
	Label* _label;
	LayerColor* _layer;
};

#endif