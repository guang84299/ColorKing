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
    
    void changeTarget(GSprite* target);
    void attack();
    
public:
    GHero* hero;
    GSprite* target;
};

#endif /* GHeroSprite_h */
