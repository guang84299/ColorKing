//
//  GDropSprite.h
//  ColorKing
//
//  Created by guang on 2016/12/11.
//
//

#ifndef GDropSprite_h
#define GDropSprite_h

#include "cocos2d.h"

USING_NS_CC;

class GDropSprite : public Sprite
{
public:
    static GDropSprite* create(int _id,int type);
    bool init(int _id,int type);
    
    void run(const Vec2& v);

    void die(const Vec2& v);
    void die2(const Vec2& v);

public:
    int _id;
    int type;
    bool isDie;
};

#endif /* GDropSprite_h */
