//
//  GTouchLayer.cpp
//  PaoPao
//
//  Created by guang on 2016/10/27.
//
//

#include "GTouchLayer.h"

USING_NS_CC;

bool GTouchLayer::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    Size s = Director::getInstance()->getWinSize();
    
    uiLayer = LayerColor::create(Color4B(42,42,42,255),s.width,s.height);
    this->addChild(uiLayer);
    
    this->setPositionY(s.height);
    this->runAction(EaseSineOut::create(MoveBy::create(0.8f,Vec2(0,-s.height))));
    
    isDialogStyle = false;
    
    return true;
}

void GTouchLayer::useDialogStyle()
{
    isDialogStyle = true;
    Size s = Director::getInstance()->getWinSize();
    
    this->stopAllActions();
    setColor(Color4B(60,60,60,255));
    uiLayer->setContentSize(Size(s.width/2,s.height/2));
    this->setPositionY(0);
    uiLayer->setPosition(s.width/4, s.height/4);
    this->setScale(0.1);
    this->runAction(EaseSineOut::create(ScaleTo::create(0.4f,1)));
}

void GTouchLayer::setColor(cocos2d::Color4B color)
{
    uiLayer->initWithColor(color);
}

bool GTouchLayer::onTouchBegan(Touch* touch, Event* event)
{
    Size s = Director::getInstance()->getWinSize();
    if(isDialogStyle)
    {
        this->runAction(Sequence::create(EaseSineOut::create(ScaleTo::create(0.4f,0.01f)),RemoveSelf::create(), NULL));
    }
    else
    {
        this->runAction(Sequence::create(EaseSineOut::create(MoveBy::create(0.8f,Vec2(0,s.height))),RemoveSelf::create(), NULL));
    }
    
    return true;
}

void GTouchLayer::onEnter()
{
    Layer::onEnter();
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GTouchLayer::onTouchBegan, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

void GTouchLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(touchListener);
}
