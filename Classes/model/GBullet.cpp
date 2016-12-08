//
//  GBullet.cpp
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#include "GBullet.h"

GBullet* GBullet::create(GJsonObject* obj)
{
    GBullet* bullet = new GBullet();
    
    bullet->_id = obj->getInt("id");
    bullet->speed = obj->getDouble("speed");
    bullet->hurt = obj->getInt("hurt");
    bullet->range = obj->getInt("range");
    
    bullet->autorelease();
    return bullet;
}

GBullet* GBullet::create(GBullet* ho)
{
    GBullet* bullet = new GBullet();
    
    bullet->_id = ho->_id;
    bullet->speed = ho->speed;
    bullet->hurt = ho->hurt;
    bullet->range = ho->range;
    
    bullet->autorelease();
    return bullet;
}
