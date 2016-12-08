//
//  GHeroSprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GHeroSprite.h"
#include "data/GCache.h"
#include "model/GHero.h"
#include "sprite/GBulletSprite.h"

GHeroSprite::~GHeroSprite()
{
    if(this->hero)
        this->hero->release();
}

GHeroSprite* GHeroSprite::create(int _id)
{
    GHeroSprite *sprite = new (std::nothrow) GHeroSprite();
    if (sprite && sprite->init(_id))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool GHeroSprite::init(int _id)
{
    if(!GSprite::init())
    {
        return false;
    }
    initAll(_id);
    return true;
}

void GHeroSprite::initAll(int _id)
{
    this->hero = GCache::getInstance()->getHero(_id);
    this->hero->retain();
    
    float sc = hero->scale;
    shape->setScale(sc);
    hp->setScale(sc);
    circle->setScale(sc);
    this->setContentSize(circle->getContentSize()*circle->getScale());
    
    shape->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    circle->setPosition(shape->getPosition());
    hp->setPosition(shape->getPosition());
}

void GHeroSprite::changeTarget(GSprite* target)
{
    this->target = target;
}

void GHeroSprite::attack()
{
    if(!target)
        return;
    
    auto bullet = GBulletSprite::create(1,this);
    Vec2 dir = (target->getPos() - this->getPos()).getNormalized();
    bullet->setDir(dir);
    bullet->run();
}
