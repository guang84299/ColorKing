//
//  GAbout.h
//  ColorKing
//
//  Created by guang on 2016/12/10.
//
//

#ifndef GAbout_h
#define GAbout_h

#include "ui/GTouchLayer.h"

class GAbout : public GTouchLayer
{
public:
    bool init();
    
    void initUI();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GAbout);
};

#endif /* GAbout_h */
