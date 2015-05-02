#include "SceneStart.h"
#include "SceneGame.h"

Scene *SceneStart::createScene(){
	Scene *scene = Scene::create();
	Layer *layer = SceneStart::create();
	scene->addChild(layer);
	return scene;
}

bool SceneStart::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SceneStart::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneStart::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	Sprite *bkr = Sprite::create("chess/bkg2.png");
	bkr->setPosition(Point(visibleSize.width / 2 - 100, visibleSize.height / 2));
	addChild(bkr);

	Sprite *bkb = Sprite::create("chess/bkg1.png");
	bkb->setPosition(Point(visibleSize.width / 2 + 100, visibleSize.height / 2));
	addChild(bkb);

	m_red = bkr;
	m_black = bkb;
	return true;
}

bool SceneStart::onTouchBegan(Touch *touch, Event *unused_event){

	return true;
}

void SceneStart::onTouchMoved(Touch *touch, Event *unused_event){

}

void SceneStart::onTouchEnded(Touch *touch, Event *unused_event){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point ptClick = touch->getLocation();
	bool m_bClickStone = false;

	if (m_red->getBoundingBox().containsPoint(ptClick)){
		m_selected = true;
		m_bClickStone = true;
	} else if (m_black->getBoundingBox().containsPoint(ptClick)){
		m_selected = false;
		m_bClickStone = true;
	}

	if (m_bClickStone){//ÒÆ¶¯Ðý×ª
		MoveTo *moveTo1 = MoveTo::create(2, Point(visibleSize.width / 2, visibleSize.height / 2));
		MoveTo *moveTo2 = MoveTo::create(2, Point(visibleSize.width / 2, visibleSize.height / 2));
		RotateBy *rotae1 = RotateBy::create(2, 360);
		RotateBy *rotae2 = RotateBy::create(2, -360);
		Spawn *spawn1 = Spawn::create(moveTo1, rotae1, NULL);
		Spawn *spawn2 = Spawn::create(moveTo2, rotae2, NULL);

		m_red->runAction(spawn1);
		m_black->runAction(spawn2);

		scheduleUpdate();
	}
}

void SceneStart::update(float delta){
	float pt1 = m_red->getPositionX();
	float pt2 = m_black->getPositionX();
	if (abs(pt1 - pt2) < m_red->getContentSize().width){
		//startGame();
		Director::getInstance()->replaceScene(SceneGame::createScene(m_selected));
	}
}

