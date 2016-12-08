//
//  GLevel.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GLevel.h"

GLevel* GLevel::create(GJsonObject* obj)
{
    GLevel* level = new GLevel();
    
    level->_id = obj->getInt("id");
    level->maxEnemyNum = obj->getInt("maxEnemyNum");
    level->updateTime = obj->getDouble("updateTime");
    level->time = obj->getDouble("time");
   
    
    level->autorelease();
    return level;
}

GLevel* GLevel::create(GLevel* level)
{
    GLevel* lv = new GLevel();
    
    lv->_id = level->_id;
    lv->maxEnemyNum = level->maxEnemyNum;
    lv->updateTime = level->updateTime;
    lv->time = level->time;
       
    lv->updateTimeDt = 0;
    
    lv->autorelease();
    return lv;
}
