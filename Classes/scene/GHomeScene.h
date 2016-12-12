//
//  GHomeScene.h
//
//  Created by guang on 16/10/2.
//
//

#ifndef GHomeScene_h
#define GHomeScene_h

#include "GScene.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class GHomeScene : public GScene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void initUI();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GHomeScene);
    
    void updateUI();
private:
   
};


#endif /* GHomeScene_h */
