//
//  GCache.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GCache_h
#define GCache_h

#include "cocos2d.h"

USING_NS_CC;

class GLevel;
class GHero;
class GEnemy;
class GBullet;
class GGameScene;

class GCache : public Ref
{
private:
    GCache(){};
public:
    static GCache* getInstance();
    
    void init();
    void destory();
    
    GLevel* getLevel(int level);
    GHero* getHero(int _id);
    GEnemy* getEnemy(int _id);
    GBullet* getBullet(int _id);
    
    GGameScene* getGameScene();
private:
    std::vector<GLevel*> levels;
    std::vector<GHero*> heros;
    std::vector<GEnemy*> enemys;
    std::vector<GBullet*> bullets;
};

#endif /* GCache_h */
