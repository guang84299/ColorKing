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
    Size s = Director::getInstance()->getWinSize();
    gameLayer = LayerColor::create(Color4B(42,42,42,255), s.width, s.height);
    gameLayer->setName("gameLayer");
    this->addChild(gameLayer,0);
    
    uiLayer = Layer::create();
    uiLayer->setName("uiLayer");
    this->addChild(uiLayer,1000);
    return true;
}
