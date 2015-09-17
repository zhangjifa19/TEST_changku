//
//  MainLayer.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#include "MainLayer.h"
#include "HunterCamp.h"
#include "Monsters.h"

Scene *MainLayer::createScene(){
    auto scene = Scene::create();
    auto layer = MainLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MainLayer::init()
{
    if(!Layer::init()){
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    loadingScene();
    return true;
}

void MainLayer::loadingScene(){
    
    auto node = CSLoader::createNode("MainScene.csb");
    node->setAnchorPoint(Vec2(0.5,0.5));
    node->setScale(visibleSize.width/node->getContentSize().width,visibleSize.height/node->getContentSize().height);
    node->setPosition(Vec2(visibleSize/2));
    this->addChild(node);
    auto Button_1 = node->getChildByName<ui::Button*>("Button_1");
    auto Button_1_0 = node->getChildByName<ui::Button*>("Button_1_0");
    auto Button_1_1 = node->getChildByName<ui::Button*>("Button_1_1");
    auto Button_1_2 = node->getChildByName<ui::Button*>("Button_1_2");
    auto Button_1_3 = node->getChildByName<ui::Button*>("Button_1_3");
    auto Button_1_4 = node->getChildByName<ui::Button*>("Button_1_4");
    
    int tag = Button_1->getTag();
    log("---%d",tag);
    Button_1->addClickEventListener([this](Ref* r){
        log("武器信息");
    });
    Button_1_0->addClickEventListener([this](Ref* r){
        
        log("金钱信息");
        
    });
    Button_1_1->addClickEventListener([this](Ref* r){
        
        log("帮助信息");
        
    });
    Button_1_2->addClickEventListener([this](Ref* r){
        
        log("商店信息");
        
    });
    Button_1_3->addClickEventListener([this](Ref* r){
        
        log("设置");
        
    });
    
    Button_1_4->addClickEventListener([this](Ref*){
        log("狩猎");
        auto scene = HunterCamp::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    
    
    
    
    
}