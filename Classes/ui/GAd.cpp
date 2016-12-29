//
//  GAd.cpp
//  ColorKing
//
//  Created by guang on 2016/12/10.
//
//

#include "GAd.h"
#include "scene/GHomeScene.h"

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
    
    auto text = Text::create(_T("ad_1"), "", 30);
    text->setPosition(Vec2(s.width/2,s.height*0.8f));
    uiLayer->addChild(text);
    
    char c[7];
    sprintf(c, "%d",GCache::getCoin());
    
    text = Text::create(_T("ad_2")+c, "", 20);
    text->setPosition(Vec2(s.width/2,s.height*0.6f));
    uiLayer->addChild(text);

    auto btn = Button::create();
    btn->setTitleText(_T("ad_3"));
    btn->setTitleFontSize(30);
    btn->setName("yes");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2-80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GAd::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create();
    btn->setTitleText(_T("ad_4"));
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
            GTools::playSound(SOUND_BUTTON);
            break;
            
        case Widget::TouchEventType::MOVED:
            break;
            
        case Widget::TouchEventType::ENDED:
            
            if(name == "yes")
            {
                GCache::setAd(true);
                GHomeScene* sc = (GHomeScene*)Director::getInstance()->getRunningScene();
                sc->updateUI();
                
                this->runAction(Sequence::create(EaseSineOut::create(ScaleTo::create(0.3f,0.01f)),RemoveSelf::create(), NULL));
            }
            else if(name == "no")
            {
                this->runAction(Sequence::create(EaseSineOut::create(ScaleTo::create(0.3f,0.01f)),RemoveSelf::create(), NULL));
            }
            
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
