//
//  GUILevel.cpp
//  ColorKing
//
//  Created by guang on 2016/12/13.
//
//

#include "GUILevel.h"
#include "data/GCache.h"
#include "scene/GGameScene.h"

bool GUILevel::init()
{
    if ( !GTouchLayer::init() )
    {
        return false;
    }
    this->useLevelStyle();
    initUI();
    
    return true;
}

void GUILevel::initUI()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto logo = Sprite::create("game_logo.png");
    logo->setPosition(s.width/2, s.height*0.75f);
    uiLayer->addChild(logo);
    
    
    auto btn = Button::create("home.png","home.png");
    btn->setName("close");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(s.width-30,s.height-30));
    btn->addTouchEventListener(CC_CALLBACK_2(GUILevel::touchEvent, this));
    uiLayer->addChild(btn);
    
    int num = GCache::getInstance()->getLevelNum();
    
    ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setBounceEnabled(true);
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    scrollView->setContentSize(Size(s.width, s.height*0.6f));
    scrollView->setInnerContainerSize(Size(200*num,scrollView->getContentSize().height));
    scrollView->setScrollBarPositionFromCorner(Vec2(1, 1));
    scrollView->setScrollBarColor(Color3B::YELLOW);
    scrollView->setPosition(Vec2(0,0));
    uiLayer->addChild(scrollView);
    
    std::vector<Button*> list;
    char c[7];
    int index = GCache::getInstance()->getCurrLevel()-1;
    for(int i=0;i<num;i++)
    {
        btn = Button::create("qiu.png","qiu.png");
        btn->setName("level");
        btn->setTag(i+1);
//        btn->setAnchorPoint(Vec2(1,1));
        btn->setPosition(Vec2(200*i+100,random(100, (int)scrollView->getContentSize().height-100)));
        btn->addTouchEventListener(CC_CALLBACK_2(GUILevel::touchEvent, this));
        scrollView->addChild(btn,2);
        
        list.push_back(btn);
        
        sprintf(c, "%d",i+1);
        auto text = Text::create(std::string("LEVEL ")+c, "", 24);
        text->setAnchorPoint(Vec2(0,0.5));
        if(btn->getPositionY() > scrollView->getContentSize().height/2)
            text->setPosition(Vec2(0,-60));
        else
            text->setPosition(Vec2(0,160));
        btn->addChild(text);
        
        if(index > i)
        {
            auto ac = Sequence::create(TintTo::create(2, Color3B(52,224,240)),
                                        TintTo::create(2, Color3B(240,218,16)),
                                        NULL);
            btn->runAction(RepeatForever::create(ac));
        }
        else if(index == i)
        {
            auto ac = Sequence::create(TintTo::create(2, Color3B(250,2,124)),
                                       TintTo::create(2, Color3B(136,18,244)),
                                       NULL);
            btn->runAction(RepeatForever::create(ac));
        }
        else
        {
            btn->runAction(TintTo::create(1, Color3B::GRAY));
            btn->setTouchEnabled(false);
        }
    }
    
    for(int i=0;i<list.size()-1;i++)
    {
        Button* btn1 = list.at(i);
        Button* btn2 = list.at(i+1);
        
        auto node = DrawNode::create();
        node->drawLine(btn1->getPosition(), btn2->getPosition(), Color4F::MAGENTA);
        scrollView->addChild(node,1);
    }
    

}

void GUILevel::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
                GCache::getInstance()->setGameLevel(btn->getTag());
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
