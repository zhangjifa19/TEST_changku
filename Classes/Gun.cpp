//
//  Gun.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#include "Gun.h"
bool Gun::init(){
    Sprite::initWithFile("hhh.png");
    setScale(0.5);
    setAnchorPoint(Point(0.5,0));
    setRotation(90);
    return true;
}