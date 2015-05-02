#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "cocos2d.h"
#include "Stone.h"

USING_NS_CC;


class SceneGame :public Layer{
public:
	static Scene *createScene(bool red);
	virtual bool init(bool red);
	//CREATE_FUNC(SceneGame);
	static SceneGame *create(bool red);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	bool getClickPos(Point ptInWin, int &x, int &y);
	int getStone(int x, int y);
	void setScaleId(int id);
	void moveStone(int moveId, int clickid, int x, int y);
	Point getStonePos(int x, int y);
private:
	Sprite *m_selectSprite;
	Point m_plateOffset;
	Point m_stoneOffset;//m_s[0]position
	float m_d;
	Stone *m_s[32];
	int m_selectid;
	bool m_redTrun;//¼ÇÂ¼Ë­×ß
};

#endif