//
//  GHomeScene.cpp
//
//  Created by guang on 16/10/2.
//
//

#include "GHomeScene.h"
#include "sprite/GSprite.h"
#include "scene/GGameScene.h"

#include "ui/GAbout.h"
#include "ui/GAd.h"

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
    
    auto logo = Sprite::create("game_logo.png");
    logo->setPosition(s.width/2, s.height*0.65f);
    uiLayer->addChild(logo);
    
    auto sp = GSprite::create();
    sp->setPosition(s.width/2, s.height*0.4f);
    uiLayer->addChild(sp);
    
    Button* btn = Button::create();
    btn->setTitleText("进入游戏");
    btn->setTitleFontSize(34);
    btn->setName("start");
    btn->setPosition(Vec2(s.width/2,s.height*0.15f));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.5f),
                                                          FadeOut::create(0.9f),
                                                          FadeIn::create(0.9f),
                                                          NULL)));
    
    btn = Button::create("01.png","01.png");
    btn->setName("about");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width - 20,s.height-20));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);

    btn = Button::create("02.png","02.png");
    btn->setName("ad");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width - 20,s.height-150));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create("sound.png","sound.png");
    btn->setName("sound");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width - 20,s.height-130*2));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create("coin.png","coin.png");
    btn->setName("coin");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width - 20,s.height-130*3));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create("role.png","role.png");
    btn->setName("role");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width - 20,s.height-130*4));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    uiLayer->addChild(btn);
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
                auto t = TransitionFade::create(1, GGameScene::create(), Color3B::BLACK);
                Director::getInstance()->replaceScene(t);
            }
            else if(name == "about")
            {
                uiLayer->addChild(GAbout::create(),2);
            }
            else if(name == "ad")
            {
                uiLayer->addChild(GAd::create(),2);
            }
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
