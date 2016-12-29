//
//  GUIRole.h
//  ColorKing
//
//  Created by guang on 2016/12/13.
//
//

#ifndef GUIRole_h
#define GUIRole_h

#include "ui/GTouchLayer.h"

class GUIRole : public GTouchLayer
{
public:
    bool init();
    
    void initUI();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GUIRole);
};

#endif /* GUIRole_h */
