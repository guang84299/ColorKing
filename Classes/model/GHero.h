//
//  GHero.h
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#ifndef GHero_h
#define GHero_h

#include "cocos2d.h"
#include "data/GJson.h"

USING_NS_CC;

class GHero : public Ref
{
public:
    static GHero* create(GJsonObject* obj);
    static GHero* create(GHero* hero);
public:
    int _id;
    float scale;
    int initHp;
    float speed;
    float attackSpeed;
    
    int hp;
    int lv;
    float attackSpeedDt;
};

#endif /* GHero_h */
