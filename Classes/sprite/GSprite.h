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

class GSprite : public Layer
{
public:
    bool init();
    void initShape();
    virtual void initAll(){};
    
    CREATE_FUNC(GSprite);
    void autoRotate();
    void born();
    virtual void attack();
public:
    const Color3B& getShapeColor();
    Vec2 getPos();
    float getShapeScale();
protected:
    Sprite* shape;
    Sprite* circle;
    ProgressTimer* hp;
};

#endif /* GSprite_h */
