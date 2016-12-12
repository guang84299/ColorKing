//
//  GHeroSprite.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GHeroSprite_h
#define GHeroSprite_h

#include "sprite/GSprite.h"

class GHero;

class GHeroSprite : public GSprite
{
public:
    ~GHeroSprite();
public:
    static GHeroSprite* create(int _id);
    bool init(int _id);
    void initAll(int _id);
    
    void attack();
    void hurt(GBulletSprite* bullet);
    void reduceHp(int hp);
    
    void run(Vec2& pos);

    void changeSkill(int _id);
    void skill();
    void skillEnd();
public:
    GHero* hero;
    bool isSkill;
};

#endif /* GHeroSprite_h */
