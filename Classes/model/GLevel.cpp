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
    level->updateBulletTime = obj->getDouble("updateBulletTime");
    level->maxBulletNum = obj->getInt("maxBulletNum");
    level->bullet1 = obj->getInt("bullet1");
    level->bullet2 = obj->getInt("bullet2");
    level->bullet3 = obj->getInt("bullet3");
    level->bullet4 = obj->getInt("bullet4");
    level->bullet5 = obj->getInt("bullet5");
    level->bullet6 = obj->getInt("bullet6");
    
    level->bulletRand = level->bullet1 + level->bullet2 + level->bullet3
    + level->bullet4 + level->bullet5 + level->bullet6;
   
    
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
    lv->updateBulletTime = level->updateBulletTime;
    lv->maxBulletNum = level->maxBulletNum;
    lv->bullet1 = level->bullet1;
    lv->bullet2 = level->bullet2;
    lv->bullet3 = level->bullet3;
    lv->bullet4 = level->bullet4;
    lv->bullet5 = level->bullet5;
    lv->bullet6 = level->bullet6;
    
    lv->bulletRand = level->bulletRand;
       
    lv->updateTimeDt = 0;
    lv->updateBulletTimeDt = 0;
    
    lv->autorelease();
    return lv;
}

int GLevel::getRandBulletId()
{
    int r = random(0, this->bulletRand);
    int _id = 11;
    if(r <= bullet1)
    {
        _id = 11;
    }
    else if(r <= bullet1+bullet2)
    {
        _id = 12;
    }
    else if(r <= bullet1+bullet2+bullet3)
    {
        _id = 13;
    }
    else if(r <= bullet1+bullet2+bullet3+bullet4)
    {
        _id = 14;
    }
    else if(r <= bullet1+bullet2+bullet3+bullet4+bullet5)
    {
        _id = 15;
    }
    else
    {
        _id = 16;
    }
    return _id;
}
