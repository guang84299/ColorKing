//
//  GAd.cpp
//  ColorKing
//
//  Created by guang on 2016/12/10.
//
//

#include "GAd.h"

bool GAd::init()
{
    if ( !GTouchLayer::init() )
    {
        return false;
    }
    this->useDialogStyle();
    initUI();
    
    return true;
}

void GAd::initUI()
{
    auto s = uiLayer->getContentSize();
    
    auto text = Text::create("是否花费10000金币去掉广告？", "", 30);
    text->setPosition(Vec2(s.width/2,s.height*0.8f));
    uiLayer->addChild(text);
    
    text = Text::create("当前金币 500", "", 20);
    text->setPosition(Vec2(s.width/2,s.height*0.6f));
    uiLayer->addChild(text);

    auto btn = Button::create();
    btn->setTitleText("好哒");
    btn->setTitleFontSize(30);
    btn->setName("yes");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2-80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAd::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create();
    btn->setTitleText("不用啦");
    btn->setTitleFontSize(30);
    btn->setName("no");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2+80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAd::touchEvent, this));
    uiLayer->addChild(btn);
}

void GAd::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
