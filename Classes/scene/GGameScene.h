//
//  GGameScene.h
//
//
//  Created by guang on 16/10/2.
//
//

#ifndef GGameScene_h
#define GGameScene_h

#include "GScene.h"


class GGameScene : public GScene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
   
    void initUI();
   
    CREATE_FUNC(GGameScene);
    
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
   
private:
    
};


#endif /* GGameScene_h */
