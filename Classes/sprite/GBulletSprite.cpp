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
#include "scene/GGameScene.h"
#include "tools/GTools.h"

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
    this->setIgnoreAnchorPointForPosition(false);
    return true;
}

void GBulletSprite::initAll(int _id,GSprite* parent)
{
    this->bullet = GCache::getInstance()->getBullet(_id);
    this->bullet->retain();
    this->parent = parent;
    this->isHero = (parent == GCache::getInstance()->getGameScene()->hero);
    this->dir = Vec2(random(0.f, 1.0f),random(0.f, 1.0f));
    changeState(State::BORN);
    if(_id == 1 || _id == 2 || _id == 11 || _id == 12 || _id == 13 || _id == 14 || _id == 15 || _id == 16)
    {
        createBullet_1();
    }
    resetContent();
}

void GBulletSprite::run()
{
    if((this->bullet->_id == 1 || this->bullet->_id == 2 || this->bullet->_id == 11) && !findTarget())
    {
        dir = Vec2::ANCHOR_MIDDLE_TOP;
    }
    changeState(State::RUN);
    
    if(this->bullet->_id == 1 || this->bullet->_id == 2)
    {
        run_1();
    }
    else if(this->bullet->_id == 11)
    {
        run_11();
    }
    else if(this->bullet->_id == 12)
    {
        run_12();
    }
    else if(this->bullet->_id == 13)
    {
        run_13();
    }
    else if(this->bullet->_id == 14)
    {
        run_14();
    }
    else if(this->bullet->_id == 15)
    {
        run_15();
    }
    else if(this->bullet->_id == 16)
    {
        run_16();
    }
    
    GTools::playSound(SOUND_SHOOT);

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
    this->setRotation(GTools::getAngle(this->dir));
    this->setScaleX(0.2f);
    Vec2 v = this->dir * bullet->range;
    float time = bullet->range / bullet->speed;
    auto ac = Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(time, v)),
                                             ScaleTo::create(time*0.8f, 1,1), NULL),
                               CallFunc::create(CC_CALLBACK_0(GBulletSprite::runEnd, this)),
                               NULL);
    ac->setTag(ACTION_MOVE);
    this->runAction(ac);
}

void GBulletSprite::run_11()
{
    this->setRotation(GTools::getAngle(this->dir));
    this->setScaleX(0.2f);
    Vec2 v = this->dir * bullet->range;
    float time = bullet->range / bullet->speed;
    auto ac = Sequence::create(Spawn::create(MoveBy::create(time, v),
                                             ScaleTo::create(time*0.8f, 1,1), NULL),
                               CallFunc::create(CC_CALLBACK_0(GBulletSprite::runEnd, this)),
                               NULL);
    ac->setTag(ACTION_MOVE);
    this->runAction(ac);
}

void GBulletSprite::run_12()
{
    run_11();
}

void GBulletSprite::run_13()
{
    run_11();
//    this->setRotation(GTools::getAngle(this->dir));
//    this->setScaleX(0.2f);
//    Vec2 v = this->dir * bullet->range;
//    
//    ccBezierConfig bezier;
//    bezier.controlPoint_1 = Vec2(0,100);
//    bezier.controlPoint_2 = Vec2(0, 200);
//    bezier.endPosition = v;
//    
//    float time = bullet->range / bullet->speed;
//    auto ac = Sequence::create(Spawn::create(
//                                             BezierBy::create(time, bezier),
//                                             ScaleTo::create(time*0.8f, 1,1), NULL),
//                               CallFunc::create(CC_CALLBACK_0(GBulletSprite::runEnd, this)),
//                               NULL);
//    ac->setTag(ACTION_MOVE);
//    this->runAction(ac);
}

void GBulletSprite::run_14()
{
    run_11();
}

void GBulletSprite::run_15()
{
    run_11();
}

void GBulletSprite::run_16()
{
    run_11();
}

void GBulletSprite::runEnd()
{
    changeState(State::DIE);
}

void GBulletSprite::die()
{
    this->stopAllActions();
    changeState(State::REMOVE);
    body->runAction(FadeOut::create(0.02f));
    this->runAction(Sequence::create(DelayTime::create(1),RemoveSelf::create(), NULL));
}

void GBulletSprite::resetContent()
{
    this->setContentSize(body->getContentSize()*body->getScale());
    body->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    
    this->setPosition(parent->getPos());
    parent->getParent()->addChild(this);
}

GSprite* GBulletSprite::findTarget()
{
    if(isHero)
    {
        GEnemySprite* target = nullptr;
        GHeroSprite* hero = GCache::getInstance()->getGameScene()->hero;
        for(int i=0;i<GCache::getInstance()->getGameScene()->enemys.size();i++)
        {
            GEnemySprite* enemy = GCache::getInstance()->getGameScene()->enemys.at(i);
            float dis = hero->getPos().getDistance(enemy->getPos());
            if(enemy->canAttack() && dis < hero->getAttackRange())
            {
                if(target == nullptr)
                {
                    target = enemy;
                }
                else
                {
                    float dis2 = hero->getPos().getDistance(target->getPos());
                    if(dis < dis2)
                    {
                        target = enemy;
                    }
                }
            }
        }
        changeTarget(target);
        return target;
    }
    else
    {
        GHeroSprite* target = GCache::getInstance()->getGameScene()->hero;
        changeTarget(target);
        return target;
    }
}

void GBulletSprite::changeState(State state)
{
    if(this->state == State::REMOVE)
    {
        return;
    }
    if(this->state != state)
    {
        this->state = state;
    }
}

void GBulletSprite::changeTarget(GSprite* target)
{
    this->target = target;
    if(target)
    this->dir = (target->getPos() - this->getPos()).getNormalized();
}

Vec2 GBulletSprite::getPos()
{
//    return this->convertToWorldSpace(body->getPosition());
    return this->getPosition();
}
