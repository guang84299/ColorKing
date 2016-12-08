//
//  GSprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/5.
//
//

#include "GSprite.h"

bool GSprite::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    initShape();
    return true;
}

void GSprite::initShape()
{
    circle = Sprite::create("circle.png");
    this->addChild(circle);
    
    hp = ProgressTimer::create(Sprite::create("hp.png"));
    hp->setType( ProgressTimer::Type::RADIAL );
    hp->setPercentage(100);
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
    
    this->setContentSize(circle->getContentSize()*circle->getScale());
   
    autoRotate();
}

void GSprite::autoRotate()
{
    auto ac = RepeatForever::create(RotateBy::create(2, 360));
    
    circle->runAction(ac);
}

void GSprite::born()
{
    this->setScale(0.1f);
    this->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(1.2f,1)), NULL));
}

void GSprite::attack()
{
    auto bullet = Sprite::create("qiu.png");
    bullet->setColor(shape->getColor());
    bullet->setScale(0.2f);
    bullet->setPosition(this->getPosition());
    this->getParent()->addChild(bullet);
    
    bullet->runAction(Sequence::create(EaseSineOut::create(MoveBy::create(1, Vec2(random(100, 200),random(100, 200)))),
                                       RemoveSelf::create(),
                                       NULL));
}

const Color3B& GSprite::getShapeColor()
{
    return shape->getColor();
}

Vec2 GSprite::getPos()
{
    return this->convertToWorldSpace(shape->getPosition());
}

float GSprite::getShapeScale()
{
    return shape->getScale();
}
