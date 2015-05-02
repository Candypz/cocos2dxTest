#ifndef SCENESTART_H
#define SCENESTART_H

#include "cocos2d.h"

USING_NS_CC;

class SceneStart :public Layer{
public:
	static Scene *createScene();
	virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void update(float delta);
	CREATE_FUNC(SceneStart);
private:
	Sprite *m_red;
	Sprite *m_black;
	bool m_selected;
};


#endif