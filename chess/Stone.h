#ifndef STONE_H
#define STONE_H

#include "cocos2d.h"

USING_NS_CC;

class Stone :public Sprite{
public:
	//CREATE_FUNC(Stone);
	enum Type{ JIANG, SHI, XIANG, CHE, MA, PAO, BING };

	static struct InitPos{
		int m_x;
		int m_y;
		Stone::Type m_type;
	}m_initPos[16];

	virtual bool init(int id,bool red);
	void reset(bool red);

	static Stone *createStone(int id,bool red);
private:
	CC_SYNTHESIZE(Type, m_type, Type);
	CC_SYNTHESIZE(int, m_x, X);
	CC_SYNTHESIZE(int, m_y, Y);
	CC_SYNTHESIZE(int, m_id, Id);
	CC_SYNTHESIZE(bool, m_dead, Dead);
	CC_SYNTHESIZE(bool, m_red, Red);
//	CC_SYNTHESIZE(int,m_id,Id)
};


#endif