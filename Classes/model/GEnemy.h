//
//  GEnemy.h
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#ifndef GEnemy_h
#define GEnemy_h

#include "cocos2d.h"
#include "data/GJson.h"

USING_NS_CC;

class GEnemy : public Ref
{
public:
    static GEnemy* create(GJsonObject* obj);
    static GEnemy* create(GEnemy* enemy);
public:
    int _id;
    float scale;
    int initHp;
    float speed;
    int walk;
    int idle;
    int attack;
    float walkTime;
    float idleTime;
    
    int hp;
    int lv;
    int rand;

};


#endif /* GEnemy_h */
