//
//  GUILevel.h
//  ColorKing
//
//  Created by guang on 2016/12/13.
//
//

#ifndef GUILevel_h
#define GUILevel_h

#include "ui/GTouchLayer.h"

class GUILevel : public GTouchLayer
{
public:
    bool init();
    
    void initUI();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GUILevel);
};


#endif /* GUILevel_h */
