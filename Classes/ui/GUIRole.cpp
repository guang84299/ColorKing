//
//  GUIRole.cpp
//  ColorKing
//
//  Created by guang on 2016/12/13.
//
//

#include "GUIRole.h"
#include "sprite/GSprite.h"

bool GUIRole::init()
{
    if ( !GTouchLayer::init() )
    {
        return false;
    }
    this->useRoleStyle();
    initUI();
    
    return true;
}

void GUIRole::initUI()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto logo = Sprite::create("game_logo.png");
    logo->setPosition(s.width/2, s.height*0.75f);
    uiLayer->addChild(logo);
    
    
    auto btn = Button::create("home.png","home.png");
    btn->setName("close");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width-30,s.height-30));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIRole::touchEvent, this));
    uiLayer->addChild(btn);
    
    auto sp = GSprite::create();
    sp->setPosition(s.width/2, s.height*0.5f);
    uiLayer->addChild(sp);

    //lv
    int lv = 10;//GCache::getLv();
    
    auto text = Text::create(StringUtils::format(_T("role_1").c_str(),lv), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2-150,s.height*0.3f));
    uiLayer->addChild(text);
    //战斗力
    int attack = 100;
    for(int i=0;i<lv;i++)
    {
        attack += attack*0.1f;
    }
    text = Text::create(StringUtils::format(_T("role_3").c_str(),attack), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2-150,s.height*0.25f));
    uiLayer->addChild(text);
    //金币
    text = Text::create(StringUtils::format(_T("role_7").c_str(),GCache::getCoin()), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2-150,s.height*0.2f));
    uiLayer->addChild(text);
    // next lv
    text = Text::create(StringUtils::format(_T("role_2").c_str(),lv+1), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2+250,s.height*0.3f));
    uiLayer->addChild(text);
    //下级战斗力
    attack += attack*0.1f;
    text = Text::create(StringUtils::format(_T("role_4").c_str(),attack), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2+250,s.height*0.25f));
    uiLayer->addChild(text);
    //钻石
    text = Text::create(StringUtils::format(_T("role_8").c_str(),4), "", 24);
    text->setAnchorPoint(Vec2(1,0.5));
    text->setPosition(Vec2(s.width/2+250,s.height*0.2f));
    uiLayer->addChild(text);
    
    btn = Button::create();
    btn->setTitleText(StringUtils::format(_T("role_5").c_str(),114));
    btn->setTitleFontSize(30);
    btn->setName("coin");
//    btn->setAnchorPoint(Vec2(1,0.5));
    btn->setPosition(Vec2(s.width/2-200,s.height*0.1f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIRole::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.1f),
                                                          Blink::create(0.5, 2),
                                                          FadeIn::create(0),
                                                          NULL)));
    
    btn = Button::create();
    btn->setTitleText(StringUtils::format(_T("role_6").c_str(),224));
    btn->setTitleFontSize(30);
    btn->setName("crystal");
//    btn->setAnchorPoint(Vec2(1,0.5));
    btn->setPosition(Vec2(s.width/2+200,s.height*0.1f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIRole::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.1f),
                                                          Blink::create(0.5, 2),
                                                          FadeIn::create(0),
                                                          NULL)));
}

void GUIRole::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
            
            if(name == "close")
            {
                this->onTouchBegan(nullptr,nullptr);
            }
            else if(name == "level")
            {
                
            }

            
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
