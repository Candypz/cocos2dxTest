#include "SceneGame.h"

Scene *SceneGame::createScene(bool red){
	Scene *scene = Scene::create();
	Layer *layer = SceneGame::create(red);
	scene->addChild(layer);
	return scene;
}

bool SceneGame::init(bool red){
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_plateOffset = Point(20, 10);

	this->m_stoneOffset = Point(60, 33);
	this->m_d = 46;
	m_redTrun = true;

	//Ìí¼Óµã»÷¿ò
	m_selectid = -1;
	m_selectSprite = Sprite::create("chess/selected.png");
	m_selectSprite->setVisible(false);//Òþ²Ø
	m_selectSprite->setLocalZOrder(1000);
	m_selectSprite->setScale(.8f);
	addChild(m_selectSprite);

	//Ìí¼Ó×À×Ó
	Sprite *desk = Sprite::create("chess/floor.jpg");
	desk->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	desk->setScaleX(visibleSize.width / desk->getContentSize().width);
	desk->setScaleY(visibleSize.height / desk->getContentSize().height);
	addChild(desk);
	//Ìí¼ÓÆåÅÌ
	Sprite *bg = Sprite::create("chess/background.png");
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(m_plateOffset);
	bg->setScale((visibleSize.height-m_plateOffset.y*2) / bg->getContentSize().height);
	addChild(bg);
	//Ìí¼ÓÆå×Ó
	for (int i = 0; i < 32; ++i){
		m_s[i] = Stone::createStone(i,red);
		m_s[i]->setPosition(Point(m_s[i]->getX()*m_d, m_s[i]->getY()*m_d) + m_stoneOffset);
		addChild(m_s[i]);
	}
	//Ìí¼Ó¼àÌý
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

SceneGame *SceneGame::create(bool red){
	SceneGame *pRet = new SceneGame();
	if (pRet){
		if (pRet->init(red)){
			pRet->autorelease();
		} 
		else{
			pRet->release();
			return NULL;
		}
	}
	else{
		return NULL;
	}
	return pRet;
}

bool SceneGame::onTouchBegan(Touch *touch, Event *unused_event){
	int x, y;
	Point ptInWin = touch->getLocation();
	
	if (!getClickPos(ptInWin, x, y)){
		return false;
	}
	

	int clickid = getStone(x, y);

	if (m_selectid == -1){
		setScaleId(clickid);
	}
	else{
		moveStone(m_selectid, clickid, x, y);
	}



	return true;
}

bool SceneGame::getClickPos(Point ptInWin, int &x, int &y){
	for (x = 0; x <= 8; ++x){
		for (y = 0; y <= 9; ++y){
			Point ptInPlate = Point(x*m_d, y*m_d) + m_stoneOffset;
			if (ptInWin.getDistance(ptInPlate) < m_d / 2){
				return true;
			}
		}
	}
	return false;
}

int SceneGame::getStone(int x, int y){
	Stone *s;
	for (int i = 0; i < 32; ++i){
		s = m_s[i];
		if (s->getX() == x&&s->getY() == y&&!s->getDead()){
			return s->getId();
		}
	}
	return -1;
}

void SceneGame::setScaleId(int id){
	if (id == -1){
		return;
	}

	if (m_s[id]->getRed() != m_redTrun){
		return ;
	}

	m_selectid = id;
	m_selectSprite->setVisible(true);
	m_selectSprite->setPosition(m_s[m_selectid]->getPosition());
}

Point SceneGame::getStonePos(int x, int y){
	int xx = x*m_d;
	int yy = y*m_d;
	return Point(xx, yy) + m_stoneOffset;
}

void SceneGame::moveStone(int moveId, int clickid, int x, int y){
	if ((clickid!=-1)&&(m_s[moveId]->getRed() == m_s[clickid]->getRed())){
		setScaleId(clickid);
		return;
	}

	if (clickid != -1){
		m_s[clickid]->setDead(true);
		m_s[clickid]->setVisible(false);
	}
	
	m_s[moveId]->setX(x);
	m_s[moveId]->setY(y);
	m_s[moveId]->setPosition(getStonePos(x,y));
	m_selectid = -1;
	m_selectSprite->setVisible(false);
	m_redTrun = !m_redTrun;
}