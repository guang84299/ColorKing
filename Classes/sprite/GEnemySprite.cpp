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
#include "model/GBullet.h"
#include "sprite/GBulletSprite.h"
#include "sprite/GHeroSprite.h"
#include "scene/GGameScene.h"

GEnemySprite::~GEnemySprite()
{
    if(this->enemy)
        this->enemy->release();
    if(this->bullet)
        this->bullet->release();
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
    this->bullet = GCache::getInstance()->getBullet(2);
    this->bullet->retain();
    this->isHero = false;
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

void GEnemySprite::attack()
{
    if(!findTarget())
    {
        changeState(GSprite::State::ATTACKEND);
        return;
    }
    
    auto bullet = GBulletSprite::create(this->bullet->_id,this);
    bullet->run();

    GCache::getInstance()->getGameScene()->enemy_bullets.push_back(bullet);
    
    this->stopActionByTag(ACTION_ATTACK);
    Vec2 v = -bullet->dir * 10 + this->getPos();
    v = getMaxVec(v);
    auto ac = Sequence::create(EaseSineOut::create(MoveTo::create(0.2f, v)),
                               DelayTime::create(this->bullet->speed-0.1f),
                               CallFunc::create(CC_CALLBACK_0(GSprite::attackEnd, this)),
                               NULL);
    ac->setTag(ACTION_ATTACK);
    this->runAction(ac);
    
    auto ac2 = Sequence::create(TintTo::create(0.1, Color3B::WHITE),
                               TintTo::create(0.1, shapeColor),
                               NULL);
    shape->runAction(ac2);
}

void GEnemySprite::hurt(GBulletSprite* bullet)
{
    this->stopActionByTag(ACTION_HURT);
    Vec2 v = bullet->dir * 20 + this->getPos();
    v = getMaxVec(v);
    auto ac = Sequence::create(EaseSineOut::create(MoveTo::create(0.2f, v)),
                               CallFunc::create(CC_CALLBACK_0(GSprite::hurtEnd, this)),
                               NULL);
    ac->setTag(ACTION_HURT);
    this->runAction(ac);
    
    auto ac2 = Sequence::create(TintTo::create(0.1, Color3B::RED),
                                TintTo::create(0.1, shapeColor),
                                NULL);
    shape->runAction(ac2);

    
    reduceHp(bullet->bullet->hurt);
    
    GTools::playSound(SOUND_HURT);
}

void GEnemySprite::reduceHp(int hp)
{
    enemy->hp -= hp;
    enemy->hp = MAX(enemy->hp,0);
    float per = (enemy->hp / (float)enemy->initHp)*100;
    this->hp->setPercentage(per);
    
    if(per <= 0)
    {
        this->die();
        GTools::playSound(SOUND_SCORE);
    }
}

void GEnemySprite::idle()
{
    this->stopActionByTag(ACTION_MOVE);
    this->stopActionByTag(ACTION_IDLE);
    auto ac = Sequence::create(DelayTime::create(enemy->idleTime),
                               CallFunc::create(CC_CALLBACK_0(GEnemySprite::idleEnd, this)),
                               NULL);
    ac->setTag(ACTION_IDLE);
    this->runAction(ac);
}

void GEnemySprite::idleEnd()
{
    changeState(GSprite::State::IDLEEND);
}

void GEnemySprite::run()
{
    this->stopActionByTag(ACTION_MOVE);
    Vec2 dir = (GCache::getInstance()->getGameScene()->hero->getPos()-getPos()).getNormalized();
    Vec2 pos = dir * enemy->walkTime * enemy->speed;
    auto ac = Sequence::create(MoveBy::create(enemy->walkTime, pos),
                               CallFunc::create(CC_CALLBACK_0(GEnemySprite::runEnd, this)),
                               NULL);
    ac->setTag(ACTION_MOVE);
    this->runAction(ac);
}

void GEnemySprite::runEnd()
{
    changeState(GSprite::State::RUNEND);
}

GSprite::State GEnemySprite::randState()
{
    if(canRandState())
    {
        int r = random(0, enemy->rand);
        if(r <= enemy->idle)
        {
            return GSprite::State::IDLE;
        }
        else if(r <= enemy->walk + enemy->idle)
        {
            return GSprite::State::RUN;
        }
        else
        {
            return GSprite::State::ATTACK;
        }
    }
    return this->state;
}
