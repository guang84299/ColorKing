//
//  GTouchLayer.h
//  PaoPao
//
//  Created by guang on 2016/10/27.
//
//

#ifndef GTouchLayer_h
#define GTouchLayer_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

USING_NS_CC;

class GTouchLayer : public cocos2d::Layer
{
public:
    virtual bool init() override;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(GTouchLayer);
    
    void setColor(cocos2d::Color4B color);
    
    void useDialogStyle();
protected:
    cocos2d::LayerColor* uiLayer;
    cocos2d::EventListenerTouchOneByOne* touchListener;
private:
    bool isDialogStyle;
    
};
#endif /* GTouchLayer_h */
