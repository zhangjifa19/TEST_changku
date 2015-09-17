//
//  ben_file.cpp
//  my0823One
//
//  Created by student on 15/8/29.
//
//
#ifndef  __ben__wenjian__
#define  __ben__wenjian__

#include <iostream>
#include "Ben_file.h"
#include "cocos2d.h"
#include "Data1.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace std;
USING_NS_CC;
template <class T>

class Ben_file{
public:
    std::vector<T*> createwithxmlfile(const std::string &xmlfile);
    void copyXmlfile(const std::string &xmlfile);
    void xmlParse(const std::string &xmlfile);
    void SaveXmlFile(int number,int score);
    void SaveXmlLevel(int level);
private:
    std::string wpath;
    XMLDocument *mydocument;
    XMLElement *parentelement;
    XMLElement *testElement;
    std::vector<T*>vec;
};

//拷贝xml文件到沙盒，解析xml文件，返回容器
template<class T>
std::vector<T*> Ben_file<T>::createwithxmlfile(const std::string &xmlfile)
{
    copyXmlfile(xmlfile);//拷贝xml文件到沙盒
    xmlParse(xmlfile);//解析文件
    return vec;
}

//拷贝xml文件到沙盒
template<class T>
void Ben_file<T>::copyXmlfile(const std::string &xmlfile)
{
    FileUtils *fe = FileUtils::getInstance();
    std::string wpath = fe->getWritablePath();
    wpath += xmlfile;
    log("沙盒路径：%s",wpath.c_str());
    if (!fe->isFileExist(wpath)) {
        std::string path = fe->fullPathForFilename(xmlfile);
        std::string data= fe->getStringFromFile(path);
        
        FILE *file = fopen(wpath.c_str(),"w");
        if (file){
            fputs(data.c_str(),file);
            fclose(file);
        }
    }
}

//解析文件
template<class T>
void Ben_file<T>::xmlParse(const std::string &xmlfile)
{
    FileUtils *fe = FileUtils::getInstance();
    wpath = fe->getWritablePath();
    wpath += xmlfile;
    vec.clear();//清空迭代器
    
    mydocument = new XMLDocument();
    XMLError errorID = mydocument->LoadFile(wpath.c_str());
    if(errorID){
        log("parse error");
        return ;
    }
//    XMLElement * rootelement=mydocument->RootElement();
    parentelement = mydocument->RootElement();
    testElement = parentelement->FirstChildElement();//第二层
    int index = 0 ;
    do {
           index++;
            XMLElement * childElement = testElement->FirstChildElement();
            std::string level = childElement->GetText();
            childElement = childElement->NextSiblingElement();
            std::string score =childElement->GetText();
            T* data2 = T::create(std::atoi(level.c_str()),std::atoi(score.c_str()));
            vec.push_back(data2);//存入迭代器
            log("jiexi  vec %d",vec[index-1]->_number);
            log("jiexi  vec %d",vec[index-1]->_score);
            testElement = testElement->NextSiblingElement();
    }while (testElement);
    
//    return vec;
}

// 保存文件
template<class T>
void Ben_file<T>::SaveXmlLevel(int level)
{
    parentelement = mydocument->RootElement();
    testElement = parentelement->FirstChildElement();//第二层
    XMLElement * numElement = testElement->FirstChildElement();
    XMLNode * oldNode = numElement->FirstChild();
    oldNode->SetValue(__String::createWithFormat("%d",level)->getCString());//改第一个test的level，可以来控制进入的关卡
    
    mydocument->SaveFile(wpath.c_str());
}
template<class T>
void Ben_file<T>::SaveXmlFile(int number,int score)
{
    parentelement = mydocument->RootElement();
    testElement = parentelement->FirstChildElement();//第二层
    int index=0;//控制进入关卡数据，该相应关卡的分数
    do {
        if (index==number)
        {
            XMLElement * childElement = testElement->FirstChildElement();
            childElement = childElement->NextSiblingElement();
            std::string score1=childElement->GetText();
            __String * score2 = __String::createWithFormat("%s",score1.c_str());
            if (score>score2->intValue())
            {
                XMLNode* oldNode = childElement->FirstChild();
                oldNode->SetValue(__String::createWithFormat("%d",score)->getCString());
                log("jiexi  vec %d",vec[index]->_number);
                log("jiexi  vec %d",vec[index]->_score);
                break;
            }
            
        }
        testElement = testElement->NextSiblingElement();
        index++;
    }while (testElement);

    
    mydocument->SaveFile(wpath.c_str());
}
static  Ben_file<Data1> *bendi;

//#include "PauseLayer.cpp"
//#include "GameLayer.cpp"
//Ben_file<Data1> *bendi;

#endif /*  defined(__ben__wenjian__) */