
//
//  HunterCamp.h
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#ifndef __zixuanxiangmu__HunterCamp__
#define __zixuanxiangmu__HunterCamp__

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace timeline;
using namespace cocos2d;
class HunterCamp:public Layer {
public:
    static Scene* createScene();
    
    virtual bool init ();
    CREATE_FUNC(HunterCamp);
    
public:
    void loadingScene();
    
private:
    Size visibleSize;
};

#endif /* defined(__zixuanxiangmu__HunterCamp__) */
