#include "GridItem.h"

GridItem* GridItem::create(float wh)
{
	GridItem* gridItem = new GridItem;
	if (gridItem && gridItem->init(wh))
	{
		gridItem->autorelease();
		return gridItem;
	}
	CC_SAFE_DELETE(gridItem);
	return nullptr;
}

bool GridItem::init(float wh)
{
	if (!Node::init())
	{
		return false;
	}
	_label = Label::create("","Arial",34);
	_label->setPosition(wh/2,wh/2);
	_layer = LayerColor::create(Color4B(200,190,180,255));
	_layer->setContentSize(Size(wh-10,wh-10));
	_layer->setPosition(5,5);
	this->addChild(_layer,0);
	this->addChild(_label,1);
	_num = 0;
	return true;
}

void GridItem::setNum(int num)
{
	_num = num;
	updateBg();
}

int GridItem::getNum()
{
	return _num;
}

void GridItem::updateBg()
{
	if (_num == 0)
	{
		_label->setString("");
	} 
	else
	{
		char txt[50] = {};
		sprintf(txt,"%d",_num);
		_label->setString(txt);
	}
	if(_num == 0){  
		_layer->setColor(cocos2d::Color3B(200,190,180));  
	}  
	if (_num == 2) {  
		_layer->setColor(cocos2d::Color3B(240,230,220));  
	}  
	if (_num == 4) {  
		_layer->setColor(cocos2d::Color3B(240,220,200));  
	}  
	if (_num == 8) {  
		_layer->setColor(cocos2d::Color3B(240,180,120));  
	}  
	if (_num == 16) {  
		_layer->setColor(cocos2d::Color3B(240,140,90));  
	}  
	if (_num == 32) {  
		_layer->setColor(cocos2d::Color3B(240,120,90));  
	}  
	if (_num == 64) {  
		_layer->setColor(cocos2d::Color3B(240,90,60));  
	}  
	if (_num == 128) {  
		_layer->setColor(cocos2d::Color3B(240,90,60));  
	}  
	if (_num == 256) {  
		_layer->setColor(cocos2d::Color3B(240,200,70));  
	}  
	if (_num == 512) {  
		_layer->setColor(cocos2d::Color3B(240,200,70));  
	}  
	if (_num == 1024) {  
		_layer->setColor(cocos2d::Color3B(0,130,0));  
	}  
	if (_num == 2048) {  
		_layer->setColor(cocos2d::Color3B(0,130,0));  
	}  
}