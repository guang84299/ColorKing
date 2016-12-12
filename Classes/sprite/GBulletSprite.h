//
//  GBulletSprite.h
//  ColorKing
//
//  Created by guang on 2016/12/7.
//
//

#ifndef GBulletSprite_h
#define GBulletSprite_h

#include "cocos2d.h"

USING_NS_CC;

class GBullet;
class GSprite;

class GBulletSprite : public Layer
{
public:
    ~GBulletSprite();
    enum State{
        BORN,
        RUN,
        DIE,
        REMOVE
    };
public:
    static GBulletSprite* create(int _id,GSprite* parent);
    bool init(int _id,GSprite* parent);
    void initAll(int _id,GSprite* parent);
    
    void run();
    
    void createBullet_1();
    
    void run_1();
    //连发
    void run_11();
    //爆裂
    void run_12();
    //喷射
    void run_13();
    //旋转
    void run_14();
    //快速爆裂
    void run_15();
    //旋转爆裂
    void run_16();
    
    void runEnd();
    void die();
public:
    void resetContent();
    void changeState(State state);
    void changeTarget(GSprite* target);
    GSprite* findTarget();
    Vec2 getPos();
public:
    GBullet* bullet;
    GSprite* parent;
    GSprite* target;
    State state;
    Vec2 dir;
    bool isHero;
private:
    Node* body;
    
};


#endif /* GBulletSprite_h */
