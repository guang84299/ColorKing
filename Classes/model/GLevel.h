//
//  GLevel.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GLevel_h
#define GLevel_h

#include "cocos2d.h"
#include "data/GJson.h"

USING_NS_CC;

class GLevel : public Ref
{
public:
    static GLevel* create(GJsonObject* obj);
    static GLevel* create(GLevel* level);
    
    int getRandBulletId();
public:
    int _id;
    int maxEnemyNum;
    float updateTime;
    int time;
    float updateBulletTime;
    int maxBulletNum;
    int bullet1;
    int bullet2;
    int bullet3;
    int bullet4;
    int bullet5;
    int bullet6;
    
    
    int bulletRand;
    
    
    //变更数据
    float updateTimeDt;
    float updateBulletTimeDt;
};

#endif /* GLevel_h */
