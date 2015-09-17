//
//  PauseLayer.h
//  zixuanxiangmu
//
//  Created by student on 15/9/13.
//
//

#ifndef __zixuanxiangmu__PauseLayer__
#define __zixuanxiangmu__PauseLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "Ben_file.h"
USING_NS_CC;
using namespace std;

class PauseDelegate {
public:
    virtual void sureClicked() = 0;
    
};

//将这个类，放到层里面，形成组合类
class PauseLayer:public LayerColor{
public:
    static PauseLayer* create();
    virtual bool init();
    void itemClicked(Ref * sender);
    CC_SYNTHESIZE(PauseDelegate * ,delegate,Delegate);
public:
    //存取数据
    vector<Data1*> vec;
    
public:
public:
    virtual void onEnter();
    
    virtual void onExit();
};

#endif /* defined(__zixuanxiangmu__PauseLayer__) */
