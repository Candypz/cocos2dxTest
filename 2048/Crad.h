#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Card :public Sprite{
public:
	static Card *createCardSprite(int number,int wigth,int height,float x,float y);
	virtual bool init();
	CREATE_FUNC(Card);

	//获取数字
	int getNumber();

	//设置数字
	void setNumber(int num);
private:
	//显示数字
	int m_number;
	void eneyInit(int number, int wigth, int height, float x, float y);



	//显示数字的控件
	Label *labelNumber;


	//显示背景
	LayerColor *layerColorBG; 

};