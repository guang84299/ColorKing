//
//  GScene.cpp
//
//  Created by guang on 16/10/1.
//
//

#include "GScene.h"


USING_NS_CC;

bool GScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    uiLayer = Layer::create();
    uiLayer->setName("uiLayer");
    this->addChild(uiLayer,1000);
    return true;
}
