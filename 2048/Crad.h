#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Card :public Sprite{
public:
	static Card *createCardSprite(int number,int wigth,int height,float x,float y);
	virtual bool init();
	CREATE_FUNC(Card);

	//��ȡ����
	int getNumber();

	//��������
	void setNumber(int num);
private:
	//��ʾ����
	int m_number;
	void eneyInit(int number, int wigth, int height, float x, float y);



	//��ʾ���ֵĿؼ�
	Label *labelNumber;


	//��ʾ����
	LayerColor *layerColorBG; 

};