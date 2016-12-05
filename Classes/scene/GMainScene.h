#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GScene.h"

class GMainScene : public GScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GMainScene);
    
private:
    
};

#endif // __HELLOWORLD_SCENE_H__
