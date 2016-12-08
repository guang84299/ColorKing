#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GScene.h"

class GHeroSprite;
class GEnemySprite;
class GLevel;

class GMainScene : public GScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);

    CREATE_FUNC(GMainScene);
    
    void updateHero(float dt);
private:
    GHeroSprite* hero;
    std::vector<GEnemySprite*> enemys;
    GLevel* level;
};

#endif // __HELLOWORLD_SCENE_H__
