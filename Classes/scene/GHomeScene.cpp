//
//  GHomeScene.cpp
//
//  Created by guang on 16/10/2.
//
//

#include "GHomeScene.h"

USING_NS_CC;

Scene* GHomeScene::createScene()
{
    auto layer = GHomeScene::create();
    layer->setName("scene");
    
    return layer;
}

bool GHomeScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }
    
    initUI();
    
    return true;
}

void GHomeScene::initUI()
{
    auto s = Director::getInstance()->getWinSize();
    
    
}

void GHomeScene::updateUI()
{
    
}

void GHomeScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    Button* btn = (Button*)pSender;
    std::string name = btn->getName();
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            break;
            
        case Widget::TouchEventType::MOVED:
            break;
            
        case Widget::TouchEventType::ENDED:
            
            if(name == "start")
            {
            }
            
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
