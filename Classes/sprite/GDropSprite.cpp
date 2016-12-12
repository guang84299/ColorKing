//
//  GDropSprite.cpp
//  ColorKing
//
//  Created by guang on 2016/12/11.
//
//

#include "GDropSprite.h"

GDropSprite* GDropSprite::create(int _id,int type)
{
    GDropSprite *sprite = new (std::nothrow) GDropSprite();
    if (sprite && sprite->init(_id,type))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool GDropSprite::init(int _id,int type)
{
    if(!Sprite::init())
    {
        return false;
    }
    
    this->_id = _id;
    this->type = type;
    
    //子弹
    if(type == 1)
    {
        this->initWithFile("qiu.png");
        this->setScale(0.36f);
        this->setContentSize(this->getContentSize()*this->getScale());
        
        if(_id == 11)
        {
            this->setColor(Color3B::YELLOW);
        }
        else if(_id == 12)
        {
            this->setColor(Color3B::BLUE);
        }
        else if(_id == 13)
        {
            this->setColor(Color3B::GREEN);
        }
        else if(_id == 14)
        {
            this->setColor(Color3B::RED);
        }
        else if(_id == 15)
        {
            this->setColor(Color3B::MAGENTA);
        }
        else if(_id == 16)
        {
            this->setColor(Color3B::ORANGE);
        }
    }
    //金币
    else if(type == 2)
    {
        
    }

    return true;
}

void GDropSprite::die(const Vec2& v)
{
    this->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(0.1f, v)),
                                     RemoveSelf::create(),
                                     NULL));
}
