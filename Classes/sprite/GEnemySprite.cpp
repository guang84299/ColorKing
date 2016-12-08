//
//  GEnemySprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GEnemySprite.h"
#include "data/GCache.h"
#include "model/GEnemy.h"

GEnemySprite::~GEnemySprite()
{
    if(this->enemy)
        this->enemy->release();
}

GEnemySprite* GEnemySprite::create(int _id)
{
    GEnemySprite *sprite = new (std::nothrow) GEnemySprite();
    if (sprite && sprite->init(_id))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool GEnemySprite::init(int _id)
{
    if(!GSprite::init())
    {
        return false;
    }
    initAll(_id);
    return true;
}

void GEnemySprite::initAll(int _id)
{
    this->enemy = GCache::getInstance()->getEnemy(_id);
    this->enemy->retain();
    
    float sc = enemy->scale;
    shape->setScale(sc);
    hp->setScale(sc);
    circle->setScale(sc);
    
    this->setContentSize(circle->getContentSize()*circle->getScale());
    
    shape->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    circle->setPosition(shape->getPosition());
    hp->setPosition(shape->getPosition());
}

