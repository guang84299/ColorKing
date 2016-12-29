//
//  GUIGameOver.cpp
//  ColorKing
//
//  Created by guang on 2016/12/21.
//
//

#include "GUIGameOver.h"
#include "scene/GGameScene.h"
#include "scene/GHomeScene.h"

bool GUIGameOver::init()
{
    if ( !GTouchLayer::init() )
    {
        return false;
    }
    this->useOverStyle();
    
    return true;
}

void GUIGameOver::fail()
{
    auto s = uiLayer->getContentSize();
    
    auto text = Text::create(_T("gameover_1"), "", 30);
    text->setPosition(Vec2(s.width/2,s.height*0.8f));
    uiLayer->addChild(text);
    
    auto btn = Button::create();
    btn->setTitleText(_T("gameover_2"));
    btn->setTitleFontSize(30);
    btn->setName("again");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2-80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIGameOver::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create();
    btn->setTitleText(_T("gameover_3"));
    btn->setTitleFontSize(30);
    btn->setName("home");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2+80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIGameOver::touchEvent, this));
    uiLayer->addChild(btn);
}

void GUIGameOver::success()
{
    auto s = uiLayer->getContentSize();
    
    auto text = Text::create(_T("gameover_4"), "", 30);
    text->setPosition(Vec2(s.width/2,s.height*0.8f));
    uiLayer->addChild(text);
    
    auto btn = Button::create();
    btn->setTitleText(_T("gameover_5"));
    btn->setTitleFontSize(30);
    btn->setName("next");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2-80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIGameOver::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create();
    btn->setTitleText(_T("gameover_3"));
    btn->setTitleFontSize(30);
    btn->setName("home");
    //    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width/2+80,s.height*0.3f));
    btn->addTouchEventListener(CC_CALLBACK_2(GUIGameOver::touchEvent, this));
    uiLayer->addChild(btn);
    
    if(GCache::getInstance()->getGameLevel() ==  GCache::getInstance()->getLevelNum())
    {
        uiLayer->getChildByName("next")->setVisible(false);
        btn->setPositionX(s.width/2);
    }
}

void GUIGameOver::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
            
            if(name == "home")
            {
                auto t = TransitionFade::create(1, GHomeScene::create(), Color3B::BLACK);
                Director::getInstance()->replaceScene(t);
            }
            else if(name == "again")
            {
                auto t = TransitionFade::create(1, GGameScene::create(), Color3B::BLACK);
                Director::getInstance()->replaceScene(t);
            }
            else if(name == "next")
            {
                GCache::getInstance()->setGameLevel(GCache::getInstance()->getGameLevel()+1);
                auto t = TransitionFade::create(1, GGameScene::create(), Color3B::BLACK);
                Director::getInstance()->replaceScene(t);
            }
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
