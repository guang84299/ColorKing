//
//  GSprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/5.
//
//

#include "GSprite.h"
#include "sprite/GBulletSprite.h"
#include "data/GCache.h"
#include "model/GBullet.h"
#include "sprite/GHeroSprite.h"
#include "sprite/GEnemySprite.h"
#include "sprite/GDropSprite.h"
#include "scene/GGameScene.h"


GSprite::~GSprite()
{
    
}

bool GSprite::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->skillBullet = nullptr;
    initShape();
    this->setIgnoreAnchorPointForPosition(false);
    return true;
}

void GSprite::initShape()
{
    circle = Sprite::create("circle.png");
    this->addChild(circle);
    
    hp = ProgressTimer::create(Sprite::create("hp.png"));
    hp->setType( ProgressTimer::Type::RADIAL );
    hp->setPercentage(100);
//    hp->setReverseDirection(true);
    this->addChild(hp);
    
    int id = random(1, 4);
    shape = Sprite::create("qiu.png");
    this->addChild(shape);
    if(id == 1)
    {
        shape->setColor(Color3B(52,224,240));
    }
    else if(id == 2)
    {
        shape->setColor(Color3B(240,218,16));
    }
    else if(id == 3)
    {
        shape->setColor(Color3B(250,2,124));
    }
    else if(id == 4)
    {
        shape->setColor(Color3B(136,18,244));
    }
    this->shapeColor = shape->getColor();
    this->setContentSize(circle->getContentSize()*circle->getScale());
    
    shape->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    circle->setPosition(shape->getPosition());
    hp->setPosition(shape->getPosition());
   
    autoRotate();
    changeState(GSprite::State::BORN);
    
}

void GSprite::autoRotate()
{
    auto ac = RepeatForever::create(RotateBy::create(2, 360));
    circle->runAction(ac);
    
    auto ac2 = RepeatForever::create(RotateBy::create(10, -360));
    hp->runAction(ac2);
    
    auto ac3 = Sequence::create(TintTo::create(2, Color3B(52,224,240)),
                                TintTo::create(2, Color3B(240,218,16)),
                                TintTo::create(2, Color3B(250,2,124)),
                                TintTo::create(2, Color3B(136,18,244)),
                                NULL);
    shape->runAction(RepeatForever::create(ac3));
    
    auto ac4 = RepeatForever::create(RotateBy::create(5, -360));
    shape->runAction(ac4);
}

void GSprite::born()
{
    this->setScale(0.1f);
    this->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(1.2f,1)),
                                     CallFunc::create(CC_CALLBACK_0(GSprite::bornEnd, this)),
                                     NULL));
    
}

void GSprite::bornEnd()
{
    changeState(GSprite::State::IDLEEND);
}

void GSprite::attackEnd()
{
    changeState(GSprite::State::ATTACKEND);
}


void GSprite::hurtEnd()
{
    changeState(GSprite::State::HURTEND);
}

void GSprite::die()
{
    changeState(GSprite::State::REMOVE);
    auto ac = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.2f,0.1f)),
                               CallFunc::create(CC_CALLBACK_0(GSprite::dieEnd, this)),
                               NULL);
    this->runAction(ac);
}

void GSprite::dieEnd()
{
    Vec2 dir(0,1);
    for(int i=0;i<5;i++)
    {
        GDropSprite* drop = GDropSprite::create(1, 2);
        drop->setPosition(this->getPos());
        this->getParent()->addChild(drop);
        dir.rotate(Vec2::ZERO, 180/M_PI*10);
        drop->run(dir);
        getScene()->drops.push_back(drop);
    }
   
    
    this->removeFromParent();
}

void GSprite::stopRun()
{
    this->stopActionByTag(ACTION_MOVE);
}

GSprite* GSprite::findTarget()
{
    if(isHero)
    {
        GEnemySprite* target = nullptr;
        GHeroSprite* hero = getScene()->hero;

        for(int i=0;i<getScene()->enemys.size();i++)
        {
            GEnemySprite* enemy = getScene()->enemys.at(i);
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
        this->target = target;
        return target;
    }
    else
    {
        GHeroSprite* target = getScene()->hero;
        this->target = target;
        return target;
    }
}

bool GSprite::changeState(State state)
{
    if(this->state == State::REMOVE)
    {
        return false;
    }
    if(this->state != state)
    {
        this->state = state;
        return true;
    }
    return false;
}

const Color3B& GSprite::getShapeColor()
{
    return shape->getColor();
}

Vec2 GSprite::getPos()
{
//    return this->convertToWorldSpace(shape->getPosition());
    return this->getPosition();
}

float GSprite::getShapeScale()
{
    return shape->getScale();
}

int GSprite::getAttackRange()
{
    if(skillBullet)
        return skillBullet->range;
    return bullet->range;
}

bool GSprite::canAttack()
{
    return (state != State::BORN && state != State::REMOVE && state != State::DIE && state != State::HURT);
}

bool GSprite::canRandState()
{
    return (state == State::IDLEEND || state == State::RUNEND || state == ATTACKEND || state == HURTEND);
}

Vec2 GSprite::getMaxVec(Vec2 v)
{
    Size s = Director::getInstance()->getWinSize();
    if(v.x < this->getContentSize().width/2)
        v.x = this->getContentSize().width/2;
    else if(v.x > s.width - this->getContentSize().width/2)
        v.x = s.width - this->getContentSize().width/2;
    if(v.y < this->getContentSize().height/2)
        v.y = this->getContentSize().height/2;
    else if(v.y > s.height - this->getContentSize().height/2)
        v.y = s.height - this->getContentSize().height/2;
    Vec2 p = v;
    return p;
}

Vec2 GSprite::getHpCurrDir()
{
    float angle = shape->getRotation();
    angle = angle > 180 ? angle - 360 : angle;
    angle = angle < -180 ? angle + 360 : angle;
    
    float currAngle = (angle-90)/(-180 / M_PI);
    Vec2 dir = Vec2::forAngle(currAngle);
    
    return dir;
}

void GSprite::clearAllAction()
{
    shape->stopAllActions();
    circle->stopAllActions();
    hp->stopAllActions();
    this->stopAllActions();
}

GGameScene* GSprite::getScene()
{
    GGameScene* gs = static_cast<GGameScene*>(this->getParent()->getParent());
    return gs;
}
