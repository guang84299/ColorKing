//
//  GAd.h
//  ColorKing
//
//  Created by guang on 2016/12/10.
//
//

#ifndef GAd_h
#define GAd_h

#include "ui/GTouchLayer.h"

class GAd : public GTouchLayer
{
public:
    bool init();
    
    void initUI();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(GAd);
};


#endif /* GAd_h */
