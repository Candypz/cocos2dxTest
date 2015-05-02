#include "Stone.h"

Stone::InitPos Stone::m_initPos[16]=
{
	{0,0,Stone::CHE},
	{1,0,Stone::MA},
	{2,0,Stone::XIANG},
	{3,0,Stone::SHI},
	{4,0,Stone::JIANG},
	{5,0,Stone::SHI},
	{6,0,Stone::XIANG},
	{7,0,Stone::MA},
	{8,0,Stone::CHE},

	{1,2,Stone::PAO},
	{7,2,Stone::PAO},

	{0,3,Stone::BING},
	{2,3,Stone::BING},
	{4,3,Stone::BING},
	{6,3,Stone::BING},
	{8,3,Stone::BING},
};

Stone *Stone::createStone(int id,bool red){
	Stone *s = new Stone();
	s->init(id,red);
	s->autorelease();
	return s;
}

void Stone::reset(bool red){
	this->setDead(false);
	if (red){
		if (m_id < 16){
			this->setX(m_initPos[m_id].m_x);
			this->setY(m_initPos[m_id].m_y);
		}
		else{
			this->setX(8 - m_initPos[m_id - 16].m_x);
			this->setY(9 - m_initPos[m_id - 16].m_y);
		}
	}
	else{
		if (m_id < 16){
			this->setX(8-m_initPos[m_id].m_x);
			this->setY(9-m_initPos[m_id].m_y);
		}
		else{
			this->setX(m_initPos[m_id - 16].m_x);
			this->setY(m_initPos[m_id - 16].m_y);
		}
	}
}

bool Stone::init(int id,bool red){
	if (!Sprite::init()){
		return false;
	}

	m_id = id;
	m_red = m_id < 16;

	if (m_id < 16){
		m_type = m_initPos[m_id].m_type;
	}
	else{
		m_type = m_initPos[m_id - 16].m_type;
	}

	const char *stonePic[14] = {
		"chess/rk.png",
		"chess/ra.png",
		"chess/rb.png",
		"chess/rr.png",
		"chess/rn.png",
		"chess/rc.png",
		"chess/rp.png",

		"chess/bk.png",
		"chess/ba.png",
		"chess/bb.png",
		"chess/br.png",
		"chess/bn.png",
		"chess/bc.png",
		"chess/bp.png"
	};

	int idx = (m_red ? 0 : 1) * 7 + m_type;
	Sprite::initWithFile(stonePic[idx]);

	setScale(.8f);

	reset(red);

	return true;
}


