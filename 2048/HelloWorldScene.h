#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <cocos-ext.h>
#include "Crad.h"


USING_NS_CC_EXT;
USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
    virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//�˳�����
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//��ť����
	void touchEvent(Ref *pSender, ui::Widget::TouchEventType type);

	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//�Զ����ɿ���
	void autoCreateCardNumber();
	//�ж���Ϸ�ܷ�����
	void doCheckGameOver();
	

	void menuCloseCallback(cocos2d::Ref* pSender);


    CREATE_FUNC(HelloWorld);
private:
	int firstX, firstY, endX, endY;
	Card *carArr[4][4];
	int m_score;

	Label *labTTFCardNumber/* = Label::createWithSystemFont("0", "arial", 80)*/;
	//ui::Button m_bunt;


	void creatCard(cocos2d::Size size);

};

#endif // __HELLOWORLD_SCENE_H__
