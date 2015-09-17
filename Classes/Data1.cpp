//
//  Data1.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/14.
//
//

#include "Data1.h"
USING_NS_CC;

Data1 * Data1::create(int number,int score)
{
    Data1 * data1 = new(std::nothrow) Data1();
    if (data1 && data1->init(number,score)) {
        data1->autorelease();
        return data1;
    }
    else
    {
        delete data1;
        data1 = NULL;
        return NULL;
    }
}

bool Data1::init(int number,int score)
{
    if (!Sprite::init()) {
        return false;
    }
    _number = number;
    _score = score;
    return true;
}