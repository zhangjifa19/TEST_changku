//
//  Data1.h
//  zixuanxiangmu
//
//  Created by student on 15/9/14.
//
//

#ifndef __zixuanxiangmu__Data1__
#define __zixuanxiangmu__Data1__

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;
class Data1:public Sprite
{
public:
    static Data1* create(int number,int score);
    virtual bool init(int number,int score);
    int _number;
    int _score;
};

#endif /* defined(__zixuanxiangmu__Data1__) */
