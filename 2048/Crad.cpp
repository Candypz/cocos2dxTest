#include "Crad.h"
USING_NS_CC;

Card *Card::createCardSprite(int number, int wigth, int height, float x, float y){
	Card *enemy = new Card();
	if (enemy&&enemy->init()){
		enemy->autorelease();
		enemy->eneyInit(number, wigth, height, x, y);

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Card::init(){
	if (!Sprite::init()){
		return false;
	}

	return true;
}

int Card::getNumber(){
	return m_number;
}

void Card::setNumber(int num){
	m_number = num;

	//数字大小
	if (m_number >= 0){
		labelNumber->setSystemFontSize(100);
	}
	if (m_number >= 16){
		labelNumber->setSystemFontSize(90);
	}
	if (m_number >= 128){
		labelNumber->setSystemFontSize(60);
	}
	if (m_number >= 1024){
		labelNumber->setSystemFontSize(40);
	}

	//判断数字大小改颜色
	if (m_number == 0){
		layerColorBG->setColor(Color3B(200, 190, 180));
	}
	if (m_number == 2){
		layerColorBG->setColor(Color3B(240, 230, 220));
	}
	if (m_number == 4){
		layerColorBG->setColor(Color3B(240, 220, 200));
	}
	if (m_number == 8){
		layerColorBG->setColor(Color3B(240, 180, 120));
	}
	if (m_number == 16){
		layerColorBG->setColor(Color3B(240, 140, 90));
	}
	if (m_number == 32){
		layerColorBG->setColor(Color3B(240, 120, 90));
	}
	if (m_number == 64){
		layerColorBG->setColor(Color3B(240, 90, 60));
	}
	if (m_number == 128){
		layerColorBG->setColor(Color3B(240, 90, 60));
	}
	if (m_number == 256){
		layerColorBG->setColor(Color3B(240, 200, 70));
	}
	if (m_number == 512){
		layerColorBG->setColor(Color3B(240, 200, 70));
	}
	if (m_number == 1024){
		layerColorBG->setColor(Color3B(0, 130, 0));
	}
	if (m_number == 2048){
		layerColorBG->setColor(Color3B(0, 190, 0));
	}

	//更新显示数字
	if (m_number > 0){
		labelNumber->setString(__String::createWithFormat("%i", m_number)->getCString());
	}else{
		labelNumber->setString("");
	}
}

void Card::eneyInit(int number, int wigth, int height, float x, float y){
	//初始化数字
	m_number = number;

	//加人游戏的背景颜色
	layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), wigth - 15, height - 15);
	layerColorBG->setPosition(x, y);

	//判断如果不等于0就显示为空
	if (m_number > 0){
		labelNumber = Label::createWithSystemFont(__String::createWithFormat("%i", m_number)->getCString(), "fonts/arial.ttf", 100);
		labelNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labelNumber);
	}else{
		labelNumber = Label::createWithSystemFont("", "arial", 100);
		labelNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labelNumber);
	}
	this->addChild(layerColorBG);
}