#include "GameLayer.h"
#include "VisibleRect.h"
#include "GridItem.h"
#include "GameScene.h"
#include "GameData.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = VisibleRect::getVisibleRect().size;
	BG_WIDTH_HEIGHT = size.width - 100;
	_score = 0;
	initBg();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void GameLayer::initBg()
{
	auto drawNode = DrawNode::create();
	Point points[] = {Point(0,0),Point(BG_WIDTH_HEIGHT,0),Point(BG_WIDTH_HEIGHT,BG_WIDTH_HEIGHT),Point(0,BG_WIDTH_HEIGHT)};
	drawNode->drawPolygon(points,sizeof(points)/sizeof(points[0]),Color4F(Color4B(200,190,180,255)),1,Color4F(222,190,180,255));
	this->addChild(drawNode);
	drawNode->drawDot(CCPointZero,4,Color4F(1,0,0,1));

	auto posx = BG_WIDTH_HEIGHT/4;
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			auto grid = GridItem::create(posx);
			grid->setPosition(posx*idx,posx*idy);
			this->addChild(grid);
			_gridVec[idx][idy] = grid;
		}
	}
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	_beginPoint = touch->getLocation();
	auto rect = Rect(this->getPositionX(),this->getPositionY(),BG_WIDTH_HEIGHT,BG_WIDTH_HEIGHT);
	return rect.containsPoint(_beginPoint);
}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	_endPoint = touch->getLocation();
	auto value = _beginPoint - _endPoint;
	auto isMove = 0;
	if (abs(value.x) > abs(value.y))
	{
		if (value.x > 0)
		{
			isMove = leftRowAdd();
		} 
		else
		{
			isMove = rightRowAdd();
		}
	} 
	else
	{
		if (value.y > 0)
		{
			isMove = downColAdd();
		} 
		else
		{
			isMove = upColAdd();
		}
	}
	if (isMove != 0)
	{
		randomCreate();
	}else if (hasOver())
	{
		auto gameData = GameData::getInstance();
		if (getScore() > gameData->getHistoryScore())
		{
			gameData->setHistoryScore(getScore());
			GameScene::getInstance()->updateHistoryScore(getScore());
		}
		GameScene::getInstance()->callFun(NULL);
	}
}

int GameLayer::leftRowAdd()
{
	auto isMove = 0;
	//相加
	for (int idy = 0; idy < 4; idy++)
	{
		int num = 0;
		int index = 0;
		for (int idx = 0; idx < 4; idx++)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idx;
				continue;
			}
			if (num == grid->getNum())
			{
				_gridVec[index][idy]->setNum(0);
				_gridVec[idx][idy]->setNum(setScore(num*2));
				num = index = 0;
				isMove = 1;
				continue;
			}
			num = grid->getNum();
			index = idx;
		}
	}
	//移动
	for (int idy = 0; idy < 4; idy++)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			if (_gridVec[idx][idy]->getNum() != 0)
			{
				continue;
			}
			for (int idz = idx + 1; idz < 4; idz++)
			{
				if (_gridVec[idz][idy]->getNum() != 0)
				{
					_gridVec[idx][idy]->setNum(_gridVec[idz][idy]->getNum());
					_gridVec[idz][idy]->setNum(0);
					if (isMove != 1)
					{
						isMove = 2;
					}
					break;
				}
			}
		}
	}
	return isMove;
}

int GameLayer::rightRowAdd()
{
	auto isMove = 0;
	for (int idy = 0; idy < 4; idy++)
	{
		int num = 0;
		int index = 0;
		for (int idx = 3; idx >= 0; idx--)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idx;
				continue;
			}
			if (num == grid->getNum())
			{
				_gridVec[idx][idy]->setNum(0);
				_gridVec[index][idy]->setNum(setScore(num*2));
				num = index = 0;
				isMove = 1;
				continue;
			}
			num = grid->getNum();
			index = idx;
		}
	}

	for (int idy = 0; idy < 4; idy++)
	{
		for (int idx = 3; idx >= 0; idx--)
		{
			if (_gridVec[idx][idy]->getNum() != 0)
			{
				continue;
			}
			for (int idz = idx - 1; idz >= 0; idz--)
			{
				if (_gridVec[idz][idy]->getNum() != 0)
				{
					_gridVec[idx][idy]->setNum(_gridVec[idz][idy]->getNum());
					_gridVec[idz][idy]->setNum(0);
					if (isMove != 1)
					{
						isMove = 2;
					}
					break;
				}
			}
		}
	}
	return isMove;
}

int GameLayer::upColAdd()
{
	auto isMove = 0;
	for (int idx = 0; idx < 4; idx++)
	{
		int num = 0;
		int index = 0;
		for (int idy = 3; idy >= 0; idy--)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idy;
				continue;
			}
			if (num == grid->getNum())
			{
				_gridVec[idx][idy]->setNum(0);
				_gridVec[idx][index]->setNum(setScore(num*2));
				num = index = 0;
				isMove = 1;
				continue;
			}
			num = grid->getNum();
			index = idy;
		}
	}

	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 3; idy >= 0; idy--)
		{
			if (_gridVec[idx][idy]->getNum() != 0)
			{
				continue;
			}
			for (int idz = idy - 1; idz >= 0; idz--)
			{
				if (_gridVec[idx][idz]->getNum() != 0)
				{
					_gridVec[idx][idy]->setNum(_gridVec[idx][idz]->getNum());
					_gridVec[idx][idz]->setNum(0);
					if (isMove != 1)
					{
						isMove = 2;
					}
					break;
				}
			}
		}
	}
	return isMove;
}

int GameLayer::downColAdd()
{
	auto isMove = 0;
	for (int idx = 0; idx < 4; idx++)
	{
		int num = 0;
		int index = 0;
		for (int idy = 0; idy < 4; idy++)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idy;
				continue;
			}
			if (num == grid->getNum())
			{
				_gridVec[idx][index]->setNum(setScore(num*2));
				_gridVec[idx][idy]->setNum(0);
				num = index = 0;
				isMove = 1;
				continue;
			}
			num = grid->getNum();
			index = idy;
		}
	}

	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			if (_gridVec[idx][idy]->getNum() != 0)
			{
				continue;
			}
			for (int idz = idy + 1; idz < 4; idz++)
			{
				if (_gridVec[idx][idz]->getNum() != 0)
				{
					_gridVec[idx][idy]->setNum(_gridVec[idx][idz]->getNum());
					_gridVec[idx][idz]->setNum(0);
					if (isMove != 1)
					{
						isMove = 2;
					}
					break;
				}
			}
		}
	}
	return isMove;
}

void GameLayer::randomCreate()
{
	Vector<GridItem*> gridVec;
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			if (_gridVec[idx][idy]->getNum() == 0)
			{
				gridVec.pushBack(_gridVec[idx][idy]);
			}
		}
	}
	auto grid = gridVec.getRandomObject();
	grid->setNum(CCRANDOM_0_1()*10 < 9 ? 2 : 4);
}

int GameLayer::setScore(int score)
{
	_score += score;
	return score;
}

int GameLayer::getScore()
{
	return _score;
}

void GameLayer::reset()
{
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			_gridVec[idx][idy]->setNum(0);
		}
	}
	_score = 0;
	randomCreate();
}

bool GameLayer::hasOver()
{
	//只要有一个空格
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			if (_gridVec[idx][idy]->getNum() == 0)
			{
				return false;
			}
		}
	}
	//垂直方向有相加的
	for (int idx = 0; idx < 4; idx++)
	{
		int num = 0;
		int index = 0;
		for (int idy = 3; idy >=0; idy--)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idy;
				continue;
			}
			if (num == grid->getNum())
			{
				return false;
			}
			num = grid->getNum();
			index = idy;
		}
	}
	//水平方向有相加的
	for (int idy = 0; idy < 4; idy++)
	{
		int num = 0;
		int index = 0;
		for (int idx = 0; idx < 4; idx++)
		{
			auto grid = _gridVec[idx][idy];
			if (grid->getNum() == 0)
			{
				continue;
			}
			if (num == 0)
			{
				num = grid->getNum();
				index = idx;
				continue;
			}
			if (num == grid->getNum())
			{
				return false;
			}
			num = grid->getNum();
			index = idx;
		}
	}
	return true;
}