//
//  PauseLayer.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/13.
//
//

#include "PauseLayer.h"


PauseLayer* PauseLayer::create(){
    PauseLayer* layer = new (std::nothrow) PauseLayer;
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PauseLayer::init(){
    if (!LayerColor::init()) {
        return false;
    }
    this->setOpacity(150);
    auto label = Label::createWithSystemFont("第一关","fonts/Marker Felt.ttf",30);
    label->setColor(Color3B::ORANGE);
//    Sprite* letter1 = label->getLetter(1);
//    letter1->setColor(Color3B::RED);
//    letter1->runAction(RepeatForever::create(RotateBy::create(1.0f,180)));
    auto item_pause = MenuItemLabel::create(label);
    item_pause->setCallback(CC_CALLBACK_1(PauseLayer::itemClicked,this));
    item_pause->setTag(90);
//    item->setPosition(Vec2(480,320));
    auto item_chongWan = MenuItemImage::create("anniu-chongwan_sel.png","anniu-chongwan.png");
    item_chongWan->setCallback(CC_CALLBACK_1(PauseLayer::itemClicked,this));
    item_chongWan->setTag(91);
    auto item_xiayigua = MenuItemImage::create("anniu-xiayigua_sel.png","anniu-xiayigua.png");
    item_xiayigua->setCallback(CC_CALLBACK_1(PauseLayer::itemClicked,this));
    item_xiayigua->setTag(92);
    auto item_kaishi = MenuItemImage::create("anniu-kaishi_sel.png","anniu-kaishi.png");
    item_kaishi->setCallback(CC_CALLBACK_1(PauseLayer::itemClicked,this));
    item_kaishi->setTag(93);
    
    auto menu = Menu::create(item_pause,item_chongWan,item_xiayigua,item_kaishi,NULL);
//    menu->setPosition(Vec2::ZERO);
//    menu->alignItemsHorizontallyWithPadding(10);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
    
    //读取数据
    bendi = new Ben_file<Data1>();//模版

    vec = bendi->createwithxmlfile("data_gameLayer.xml");
    
    return true;
}

void PauseLayer::itemClicked(Ref* sender){
    //点击按钮的时候，通过代理调用对应的函数
    auto item= (MenuItemImage*)sender;
    log("anniu Tag %d",item->getTag());
    delegate->sureClicked();
    vec= bendi->createwithxmlfile("data_gameLayer.xml");
    if (item->getTag() == 90) {
        log("第一关");
        int sc = vec[0]->_score;
        bendi->SaveXmlLevel(0);
        bendi->SaveXmlFile(0,sc);
        delegate->sureClicked();//设置代理
    
    }
    else if(item->getTag() == 91){
        int l= vec[0]->_number;
        int sc = vec[l]->_score;
        bendi->SaveXmlLevel(l);
        bendi->SaveXmlFile(l,sc);
        log("重玩本关");
        delegate->sureClicked();//设置代理
    }
    else if(item->getTag() == 92){
        int l= vec[0]->_number;
        int sc = vec[l]->_score;
        log("l = %d",l);
        
        bendi->SaveXmlFile(l, sc);
        log("sc = %d",sc);
        if (l<2) {
            l++;
            log("标题");
            bendi->SaveXmlLevel(l);
        }
        else {
            MessageBox("已经是最后一关", "标题");
        }
        
        delegate->sureClicked();//设置代理
        log("下一关");
    }
    else if(item->getTag() == 93){
    Director::getInstance()->resume();
    log("开始游戏");
    }
    this->removeFromParent();
}
void PauseLayer::onEnter()
{
    Layer::onEnter();
}
void PauseLayer::onExit()
{
    Layer::onExit();
}
