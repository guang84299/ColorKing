//
//  GBullet.h
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#ifndef GBullet_h
#define GBullet_h

#include "cocos2d.h"
#include "data/GJson.h"

USING_NS_CC;

class GBullet : public Ref
{
public:
    static GBullet* create(GJsonObject* obj);
    static GBullet* create(GBullet* enemy);
public:
    int _id;
    float speed;
    int hurt;
    int range;
    int num;
    float fireCd;
    int onceNum;
};

#endif /* GBullet_h */
