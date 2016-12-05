//
//  GGameScene.cpp
//
//  Created by guang on 16/10/2.
//
//

#include "GGameScene.h"

USING_NS_CC;

Scene* GGameScene::createScene()
{
    auto layer = GGameScene::create();
    layer->setName("scene");
    
    return layer;
}

bool GGameScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }

    
    
    initUI();
    
    return true;
}

void GGameScene::initUI()
{
    Size s = Director::getInstance()->getWinSize();
    
    
}

void GGameScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    Button* btn = (Button*)pSender;
    std::string name = btn->getName();
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
//            GTools::playSound(SOUND_BUTTON);
            if(name == "speed")
            {
                
            }
                        break;
            
        case Widget::TouchEventType::MOVED:
            
            break;
            
        case Widget::TouchEventType::ENDED:
            
            if(name == "speed")
            {
               
            }
           
            break;
            
        case Widget::TouchEventType::CANCELED:
            if(name == "speed")
            {
                
            }
            
            break;
            
        default:
            break;
    }
}
