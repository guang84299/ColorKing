//
//  GBulletSprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#include "GBulletSprite.h"

#include "data/GCache.h"
#include "model/GBullet.h"
#include "sprite/GHeroSprite.h"
#include "sprite/GEnemySprite.h"

#define ACTION_MOVE 1

GBulletSprite::~GBulletSprite()
{
    if(this->bullet)
        this->bullet->release();
}

GBulletSprite* GBulletSprite::create(int _id,GSprite* parent)
{
    GBulletSprite *sprite = new (std::nothrow) GBulletSprite();
    if (sprite && sprite->init(_id,parent))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool GBulletSprite::init(int _id,GSprite* parent)
{
    if(!Layer::init())
    {
        return false;
    }
    initAll(_id,parent);
    return true;
}

void GBulletSprite::initAll(int _id,GSprite* parent)
{
    this->bullet = GCache::getInstance()->getBullet(_id);
    this->bullet->retain();
    this->parent = parent;
    
    if(_id == 1)
    {
        createBullet_1();
    }
    resetContent();
}

void GBulletSprite::run()
{
    if(this->bullet->_id == 1)
    {
        run_1();
    }
}

void GBulletSprite::createBullet_1()
{
    auto sp = Sprite::create("qiu.png");
    sp->setColor(parent->getShapeColor());
    sp->setScale(parent->getShapeScale()*0.3f);
    this->addChild(sp);
    
    body = sp;
}

void GBulletSprite::run_1()
{
    Vec2 v = this->dir * bullet->range;
    this->runAction(Sequence::create(EaseSineOut::create(MoveBy::create(1, v)),
                                       RemoveSelf::create(),
                                       NULL));
}

void GBulletSprite::resetContent()
{
    this->setContentSize(body->getContentSize()*body->getScale());
//    body->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    
    this->setPosition(parent->getPos());
    parent->getParent()->addChild(this);
}

void GBulletSprite::changeTarget(GSprite* target)
{
    this->target = target;
}

void GBulletSprite::setDir(Vec2& dir)
{
    this->dir = dir;
}

Vec2 GBulletSprite::getPos()
{
    return this->convertToWorldSpace(body->getPosition());
}
