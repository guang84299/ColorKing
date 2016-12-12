//
//  GHero.cpp
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#include "GHero.h"

GHero* GHero::create(GJsonObject* obj)
{
    GHero* hero = new GHero();
    
    hero->_id = obj->getInt("id");
    hero->scale = obj->getDouble("scale");
    hero->initHp = obj->getInt("initHp");
    hero->speed = obj->getDouble("speed");
    hero->attackSpeed = obj->getDouble("attackSpeed");
    hero->hp = hero->initHp;
    hero->lv = 1;
    hero->attackSpeedDt = 0;
    
    hero->autorelease();
    return hero;
}

GHero* GHero::create(GHero* ho)
{
    GHero* hero = new GHero();
    
    hero->_id = ho->_id;
    hero->scale = ho->scale;
    hero->initHp = ho->initHp;
    hero->speed = ho->speed;
    hero->attackSpeed = ho->attackSpeed;
    hero->hp = ho->hp;
    hero->lv = ho->lv;
    hero->attackSpeedDt = ho->attackSpeedDt;
    
    hero->autorelease();
    return hero;
}
