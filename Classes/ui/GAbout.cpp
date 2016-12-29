//
//  GAbout.cpp
//  ColorKing
//
//  Created by guang on 2016/12/10.
//
//

#include "GAbout.h"

bool GAbout::init()
{
    if ( !GTouchLayer::init() )
    {
        return false;
    }
    
    initUI();
    
    return true;
}

void GAbout::initUI()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto logo = Sprite::create("logo.png");
    logo->setPosition(s.width/2, s.height*0.65f);
    uiLayer->addChild(logo);
    
    
    auto btn = Button::create("evaluate.png","evaluate.png");
    btn->setName("evaluate");
//    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2-180,s.height*0.2f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAbout::touchEvent, this));
    uiLayer->addChild(btn);
    
    auto text = Text::create(_T("about_1"), "", 24);
    text->setPosition(Vec2(btn->getPositionX(),btn->getPositionY()-60));
    uiLayer->addChild(text);
    
    btn = Button::create("share.png","share.png");
    btn->setName("share");
    btn->setPosition(Vec2(s.width/2,s.height*0.2f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAbout::touchEvent, this));
    uiLayer->addChild(btn);
    
    text = Text::create(_T("about_2"), "", 24);
    text->setPosition(Vec2(btn->getPositionX(),btn->getPositionY()-60));
    uiLayer->addChild(text);
    
    btn = Button::create("more.png","more.png");
    btn->setName("more");
    btn->setPosition(Vec2(s.width/2+180,s.height*0.2f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAbout::touchEvent, this));
    uiLayer->addChild(btn);
    
    text = Text::create(_T("about_3"), "", 24);
    text->setPosition(Vec2(btn->getPositionX(),btn->getPositionY()-60));
    uiLayer->addChild(text);
    
    text = Text::create(_T("about_4"), "", 26);
    text->setPosition(Vec2(s.width/2,s.height*0.42f));
    uiLayer->addChild(text);
    
    text = Text::create(_T("about_5"), "", 20);
    text->setPosition(Vec2(s.width/2,s.height*0.35f));
    uiLayer->addChild(text);
}

void GAbout::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    Button* btn = (Button*)pSender;
    std::string name = btn->getName();
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            GTools::playSound(SOUND_BUTTON);
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
