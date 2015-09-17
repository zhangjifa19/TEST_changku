//
//  HunterCamp.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#include "HunterCamp.h"
#include "MainLayer.h"
#include "GameLayer.h"

Scene * HunterCamp::createScene(){
    auto scene= Scene::create();
    auto layer = HunterCamp::create();
    scene->addChild(layer);
    return scene;
}

bool HunterCamp::init(){
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    loadingScene();
    return true;
    
    
}


void HunterCamp::loadingScene(){
    auto node = CSLoader::createNode("MainScene_1.csb");
    node->setAnchorPoint(Vec2(0.5,0.5));
    node->setScale(visibleSize.width/node->getContentSize().width,visibleSize.height/node->getContentSize().height);
    node->setPosition(Vec2(visibleSize/2));
    
    auto button = node->getChildByName<ui::Button *>("Button_1");
    button->addClickEventListener([this](Ref* r){
        log("返回营地");
        auto scene = MainLayer::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    
    auto buttonNode = node->getChildByName<Node*>("ProjectNode_1");
    
    auto button1 = buttonNode->getChildByName<ui::Button *>("Button_2");
    button1->addClickEventListener([this](Ref* r){
        
        log("------");
        
        auto scene =  GameLayer::createScene();
        Director::getInstance()->replaceScene(scene);
        
    });
    
    
    
    this->addChild(node);
}
