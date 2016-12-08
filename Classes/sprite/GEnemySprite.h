//
//  GEnemySprite.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GEnemySprite_h
#define GEnemySprite_h

#include "sprite/GSprite.h"

class GEnemy;

class GEnemySprite : public GSprite
{
public:
    ~GEnemySprite();
public:
    static GEnemySprite* create(int _id);
    bool init(int _id);
    void initAll(int _id);
    
public:
    GEnemy* enemy;
};


#endif /* GEnemySprite_h */
