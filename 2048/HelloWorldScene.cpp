#include "HelloWorldScene.h"
#include "Crad.h"



USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	//物理世界
	//auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = HelloWorld::create();


    scene->addChild(layer);

    return scene;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	Director::getInstance()->end();
}

void HelloWorld::touchEvent(Ref *pSender, ui::Widget::TouchEventType type){
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN://按下
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
		break;

	case ui::Widget::TouchEventType::CANCELED://按键中断
		break;

	case ui::Widget::TouchEventType::ENDED://按下结束
		break;

	case ui::Widget::TouchEventType::MOVED://按下并移动
		break;
	}
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_score = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();


	//退出程序
	auto listenerEnd = EventListenerKeyboard::create();
	listenerEnd->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerEnd, this);


	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	addChild(layerColorBG);

	auto labTTFCardNumberName = Label::createWithSystemFont("Score", "fonts/arial.ttf", 60);
	labTTFCardNumberName->setPosition(Point(visibleSize.width / 5, visibleSize.height - 70));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = Label::createWithSystemFont("0", "fonts/arial.ttf", 60);
	labTTFCardNumber->setPosition(Point(visibleSize.width / 2 + 100, visibleSize.height - 70));
	addChild(labTTFCardNumber);


	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listen->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);

	//设置重来按钮
	auto m_bunt = ui::Button::create("normal.png", "selected.png");
	m_bunt->setScale9Enabled(true);//可拉伸图片
	m_bunt->setTitleText("Begen");
	m_bunt->setTitleFontSize(50);
	m_bunt->setTitleFontName("fonts/arial.ttf");
	m_bunt->setContentSize(cocos2d::Size(visibleSize.width / 10+200, visibleSize.height / 15));
	m_bunt->setPosition(Point(visibleSize.width / 5 + 180, visibleSize.height - 150));
	m_bunt->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchEvent, this));
	addChild(m_bunt);


	creatCard(visibleSize);

	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
	Point touchPo = touch->getLocation();

	firstX = touchPo.x;
	firstY = touchPo.y;

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event){
	Point touchPo = touch->getLocation();
	endX = firstX - touchPo.x;
	endY = firstY - touchPo.y;

	if (abs(endX) > abs(endY)){//绝对值
		//左右
		if (endX+5>0){
			//左边
			if (doLeft()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//右边
			if (doRight()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}else{
		//上下
		if (endY + 5 < 0){
			//上
			if (doUp()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//下
			if (doDown()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
}

bool HelloWorld::doLeft(){
	log("doLeft");
	bool isdo = false;
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			for (int x1 = x + 1; x1<4; x1++){
				if (carArr[x1][y]->getNumber()>0){
					if (carArr[x][y]->getNumber() <= 0){
						carArr[x][y]->setNumber(carArr[x1][y]->getNumber());
						carArr[x1][y]->setNumber(0);

						x--;
						isdo = true;
					}
					else if (carArr[x][y]->getNumber() == carArr[x1][y]->getNumber()){
						carArr[x][y]->setNumber(carArr[x][y]->getNumber() * 2);
						carArr[x1][y]->setNumber(0);
						//设置分数
						m_score += carArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", m_score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doRight(){
	log("doRight");

	bool isdo = false;
	for (int y = 0; y < 4; y++){
		for (int x = 3; x >=0; x--){
			for (int x1 = x - 1; x1 >=0; x1--){
				if (carArr[x1][y]->getNumber()>0){
					if (carArr[x][y]->getNumber() <= 0){
						carArr[x][y]->setNumber(carArr[x1][y]->getNumber());
						carArr[x1][y]->setNumber(0);

						x++;
						isdo = true;
					}
					else if (carArr[x][y]->getNumber() == carArr[x1][y]->getNumber()){
						carArr[x][y]->setNumber(carArr[x][y]->getNumber() * 2);
						carArr[x1][y]->setNumber(0);
						//设置分数
						m_score += carArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", m_score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doUp(){
	log("doUp");

	bool isdo = false;
	for (int x = 0; x < 4; x++){
		for (int y = 3; y >=0; y--){
			for (int y1 = y - 1; y1>=0; y1--){
				if (carArr[x][y1]->getNumber()>0){
					if (carArr[x][y]->getNumber() <= 0){
						carArr[x][y]->setNumber(carArr[x][y1]->getNumber());
						carArr[x][y1]->setNumber(0);

						y++;
						isdo = true;
					}
					else if (carArr[x][y]->getNumber() == carArr[x][y1]->getNumber()){
						carArr[x][y]->setNumber(carArr[x][y]->getNumber() * 2);
						carArr[x][y1]->setNumber(0);
						//设置分数
						m_score += carArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", m_score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doDown(){
	log("doDown");

	bool isdo = false;
	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++){
			for (int y1 = y + 1; y1<4; y1++){
				if (carArr[x][y1]->getNumber()>0){
					if (carArr[x][y]->getNumber() <= 0){
						carArr[x][y]->setNumber(carArr[x][y1]->getNumber());
						carArr[x][y1]->setNumber(0);

						y--;
						isdo = true;
					}
					else if (carArr[x][y]->getNumber() == carArr[x][y1]->getNumber()){
						carArr[x][y]->setNumber(carArr[x][y]->getNumber() * 2);
						carArr[x][y1]->setNumber(0);
						//设置分数
						m_score += carArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", m_score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

void HelloWorld::creatCard(cocos2d::Size size){
	//求出单元格的宽高
	int lon = (size.width - 28) / 4;

	//4*4
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			Card *card = Card::createCardSprite(0, lon, lon, lon*i + 20, lon*j + 20 + size.height / 6);
			addChild(card);
			carArr[i][j] = card;
		}
	}
}

void HelloWorld::autoCreateCardNumber(){
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	if (carArr[i][j]->getNumber() > 0){
		autoCreateCardNumber();
	}else{
		carArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

void HelloWorld::doCheckGameOver(){
	bool isGameOver = true;

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			if (carArr[x][y]->getNumber() == 0||
				(x>0&&(carArr[x][y]->getNumber()==carArr[x-1][y]->getNumber())) ||
				(x<3 && (carArr[x][y]->getNumber() == carArr[x + 1][y]->getNumber())) ||
				(y>0 && (carArr[x][y]->getNumber() == carArr[x][y-1]->getNumber())) ||
				(y<3 && (carArr[x][y]->getNumber() == carArr[x][y+1]->getNumber())))
				{
				isGameOver = false;
			}
		}
	}
	if (isGameOver){
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
