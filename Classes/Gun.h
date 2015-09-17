//
//  Gun.h
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#ifndef __zixuanxiangmu__Gun__
#define __zixuanxiangmu__Gun__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class Gun:public Sprite{
public:
    virtual bool init();
    CREATE_FUNC(Gun);
};

#endif /* defined(__zixuanxiangmu__Gun__) */
