//
//  GUIGameOver.h
//  ColorKing
//
//  Created by guang on 2016/12/21.
//
//

#ifndef GUIGameOver_h
#define GUIGameOver_h

#include "ui/GTouchLayer.h"

class GUIGameOver : public GTouchLayer
{
public:
    bool init();
    
    void fail();
    
    void success();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GUIGameOver);
};

#endif /* GUIGameOver_h */
