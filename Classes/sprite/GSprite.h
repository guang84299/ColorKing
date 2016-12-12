//
//  GSprite.h
//  ColorKing
//
//  Created by guang on 2016/12/5.
//
//

#ifndef GSprite_h
#define GSprite_h

#include "cocos2d.h"

USING_NS_CC;

#define ACTION_MOVE 1
#define ACTION_HURT 2
#define ACTION_IDLE 3
#define ACTION_ATTACK 4
#define ACTION_ROTATE 5
#define ACTION_SKILL 6

class GBullet;
class GBulletSprite;
class GGameScene;

class GSprite : public Layer
{
public:
    ~GSprite();
    enum State{
        BORN,
        IDLE,
        IDLEEND,
        RUN,
        RUNEND,
        ATTACK,
        ATTACKEND,
        SKILL,
        SKILLEND,
        HURT,
        HURTEND,
        DIE,
        REMOVE
    };
public:
    bool init();
    void initShape();
    virtual void initAll(){};
    
    CREATE_FUNC(GSprite);
    void autoRotate();
    void born();
    void bornEnd();
    virtual void attack(){};
    void attackEnd();
    virtual void hurt(GBulletSprite* bullet){};
    void hurtEnd();
    void die();
    void dieEnd();    
    void stopRun();
    GSprite* findTarget();
public:
    const Color3B& getShapeColor();
    Vec2 getPos();
    float getShapeScale();
    int getAttackRange();
    bool changeState(State state);
    bool canAttack();
    bool canRandState();
    virtual State randState(){return this->state;};
    Vec2 getMaxVec(Vec2 v);
    Vec2 getHpCurrDir();
    GGameScene* getScene();
protected:
    Sprite* shape;
    Sprite* circle;
    ProgressTimer* hp;
    
    GSprite* target;
    GBullet* bullet;
    GBullet* skillBullet;
    
    Color3B shapeColor;
public:
    State state;
    bool isHero;
};

#endif /* GSprite_h */
