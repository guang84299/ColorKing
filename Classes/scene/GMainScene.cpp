#include "GMainScene.h"

USING_NS_CC;

Scene* GMainScene::createScene()
{
    auto layer = GMainScene::create();
    layer->setName("scene");

    return layer;
}

bool GMainScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }
    
    
    return true;
}
