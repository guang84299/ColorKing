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
#include "model/GBullet.h"
#include "sprite/GBulletSprite.h"
#include "scene/GGameScene.h"

GHeroSprite::~GHeroSprite()
{
    if(this->hero)
        this->hero->release();
    if(this->bullet)
        this->bullet->release();
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
    this->bullet = GCache::getInstance()->getBullet(1);
    this->bullet->retain();
    this->isHero = true;
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

void GHeroSprite::attack()
{
    if(!findTarget())
    {
        changeState(GSprite::State::ATTACKEND);
        return;
    }
    
    auto bullet = GBulletSprite::create(this->bullet->_id,this);
    bullet->run();

    GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
    
    this->stopActionByTag(ACTION_ATTACK);

//    Vec2 v = -bullet->dir * 5 + this->getPos();
//    v = getMaxVec(v);
    shapeColor = getShapeColor();
    auto ac = Sequence::create(TintTo::create(0.1, Color3B::WHITE),
                               TintTo::create(0.1, shapeColor),
                               DelayTime::create(this->bullet->speed-0.1f),
                               CallFunc::create(CC_CALLBACK_0(GSprite::attackEnd, this)),
                               NULL);
    ac->setTag(ACTION_ATTACK);
    shape->runAction(ac);
}

void GHeroSprite::hurt(GBulletSprite* bullet)
{
    this->stopActionByTag(ACTION_HURT);
//    Vec2 v = bullet->dir * 8 + this->getPos();
//    v = getMaxVec(v);
    shapeColor = getShapeColor();
    auto ac = Sequence::create(TintTo::create(0.1, Color3B::RED),
                               TintTo::create(0.1, shapeColor),
                               CallFunc::create(CC_CALLBACK_0(GSprite::hurtEnd, this)),
                               NULL);
    ac->setTag(ACTION_HURT);
    shape->runAction(ac);
    
    reduceHp(bullet->bullet->hurt);
    
    GTools::playSound(SOUND_HURT);
}

void GHeroSprite::reduceHp(int hp)
{
    hero->hp -= hp;
    hero->hp = MAX(hero->hp,0);
    int per = (hero->hp / (float)hero->initHp)*100;
    this->hp->setPercentage(per);
    if(per <= 0)
    {
        this->die();
        GTools::playSound(SOUND_DIE);
    }
}

void GHeroSprite::run(Vec2 &pos)
{
    this->stopActionByTag(ACTION_MOVE);
    
    Vec2 v = getMaxVec(pos);
    float time = this->getPosition().getDistance(v) / hero->speed;
    
    auto ac = MoveTo::create(time, v);
    ac->setTag(ACTION_MOVE);
    this->runAction(ac);
}

void GHeroSprite::changeSkill(int _id)
{    
    shape->stopActionByTag(ACTION_SKILL);
    skillBullet = GCache::getInstance()->getBullet(_id);
    skillBullet->retain();
    changeState(State::SKILL);
    this->isSkill = true;
    skill();
}

void GHeroSprite::skill()
{
    if(this->skillBullet && this->skillBullet->num > 0)
    {
        this->skillBullet->num -- ;
        
        if(this->skillBullet->_id == 12)
        {
            Vec2 dir(0,1);
            for(int i=0;i<skillBullet->onceNum;i++)
            {
                auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
                dir.rotate(Vec2::ZERO, 180/M_PI*10);
                bullet->dir = dir;
                bullet->run();
                GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
            }
        }
        else if(this->skillBullet->_id == 13)
        {
            Vec2 dir(0,1);
            for(int i=0;i<skillBullet->onceNum;i++)
            {
                auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
                dir.rotate(Vec2::ZERO, 180/M_PI*10);
                bullet->dir = dir;
                bullet->run();
                GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
            }
        }
        else if(this->skillBullet->_id == 14)
        {
            Vec2 dir = getHpCurrDir();
            for(int i=0;i<skillBullet->onceNum;i++)
            {
                auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
                dir.rotate(Vec2::ZERO, 180/M_PI*10);
                bullet->dir = dir;
                bullet->run();
                GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
            }
        }
        else if(this->skillBullet->_id == 15)
        {
            Vec2 dir(0,1);
            for(int i=0;i<skillBullet->onceNum;i++)
            {
                auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
                dir.rotate(Vec2::ZERO, 180/M_PI*10);
                bullet->dir = dir;
                bullet->run();
                GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
            }
        }
        else if(this->skillBullet->_id == 16)
        {
            Vec2 dir = getHpCurrDir();
            for(int i=0;i<skillBullet->onceNum;i++)
            {
                auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
                dir.rotate(Vec2::ZERO, 180/M_PI*10);
                bullet->dir = dir;
                bullet->run();
                GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
            }
        }
        else
        {
            auto bullet = GBulletSprite::create(this->skillBullet->_id,this);
            bullet->run();
            GCache::getInstance()->getGameScene()->bullets.push_back(bullet);
        }
    
//        Vec2 v = -bullet->dir * 5 + this->getPos();
//        v = getMaxVec(v);
        shapeColor = getShapeColor();
        auto ac = Sequence::create(Spawn::create(TintTo::create(0.08f, Color3B::WHITE),
                                                 DelayTime::create(this->skillBullet->fireCd),
                                                 NULL),
                                   TintTo::create(0.05f, shapeColor),
                                   CallFunc::create(CC_CALLBACK_0(GHeroSprite::skill, this)),
                                   NULL);
        ac->setTag(ACTION_SKILL);
        shape->runAction(ac);
    }
    else
    {
        skillEnd();
    }
}

void GHeroSprite::skillEnd()
{
    if(this->skillBullet)
        this->skillBullet->release();
    this->skillBullet = nullptr;
    changeState(State::SKILLEND);
    this->isSkill = false;
}
