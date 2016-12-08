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
public:
    int _id;
    int maxEnemyNum;
    float updateTime;
    float time;
    
    //变更数据
    float updateTimeDt;
    
};

#endif /* GLevel_h */
