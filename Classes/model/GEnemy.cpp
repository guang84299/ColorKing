//
//  GEnemy.cpp
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#include "GEnemy.h"

GEnemy* GEnemy::create(GJsonObject* obj)
{
    GEnemy* enemy = new GEnemy();
    
    enemy->_id = obj->getInt("id");
    enemy->scale = obj->getDouble("scale");
    enemy->initHp = obj->getInt("initHp");
    enemy->speed = obj->getDouble("speed");
    enemy->walk = obj->getInt("walk");
    enemy->idle = obj->getInt("idle");
    enemy->attack = obj->getInt("attack");
    enemy->walkTime = obj->getDouble("walkTime");
    enemy->idleTime = obj->getDouble("idleTime");
    enemy->hp = enemy->initHp;
    enemy->lv = 1;
    enemy->rand = enemy->walk + enemy->idle + enemy->attack;
    
    enemy->autorelease();
    return enemy;
}

GEnemy* GEnemy::create(GEnemy* ho)
{
    GEnemy* enemy = new GEnemy();
    
    enemy->_id = ho->_id;
    enemy->scale = ho->scale;
    enemy->initHp = ho->initHp;
    enemy->speed = ho->speed;
    enemy->walk = ho->walk;
    enemy->idle = ho->idle;
    enemy->attack = ho->attack;
    enemy->walkTime = ho->walkTime;
    enemy->idleTime = ho->idleTime;
    enemy->rand = ho->rand;
    enemy->hp = ho->hp;
    enemy->lv = ho->lv;
    
    enemy->autorelease();
    return enemy;
}
