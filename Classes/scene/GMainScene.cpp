#include "GMainScene.h"
#include "data/GCache.h"
#include "tools/GTools.h"
#include "scene/GHomeScene.h"

USING_NS_CC;

Scene* GMainScene::createScene()
{
    auto layer = GMainScene::create();
    layer->setName("scene");

    return layer;
}

bool GMainScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }
    GCache::getInstance()->init();
    
    initUI();
    
    if(GCache::getCurrLevel() == 0)
    {
        GCache::setCurrLevel(1);
        GCache::setMusic(true);
    }
    GCache::setAd(false);
    GTools::preload();
    this->runAction(Sequence::create(DelayTime::create(2),
                                     CallFunc::create(CC_CALLBACK_0(GMainScene::goHome, this)),
                                     NULL));
    
    return true;
}

void GMainScene::initUI()
{
    Size s = Director::getInstance()->getWinSize();
    
    auto logo = Sprite::create("logo.png");
    logo->setPosition(s.width/2, s.height*0.55f);
    uiLayer->addChild(logo);
}

void GMainScene::goHome()
{
    auto t = TransitionFade::create(1, GHomeScene::create(), Color3B::BLACK);
    Director::getInstance()->replaceScene(t);
}
