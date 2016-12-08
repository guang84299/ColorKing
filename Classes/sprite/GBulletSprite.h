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
public:
    static GBulletSprite* create(int _id,GSprite* parent);
    bool init(int _id,GSprite* parent);
    void initAll(int _id,GSprite* parent);
    
    void run();
    
    void createBullet_1();
    
    void run_1();
public:
    void resetContent();
    void changeTarget(GSprite* target);
    void setDir(Vec2& dir);
    Vec2 getPos();
public:
    GBullet* bullet;
    GSprite* parent;
    GSprite* target;
private:
    Node* body;
    Vec2 dir;
};


#endif /* GBulletSprite_h */
