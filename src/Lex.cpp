﻿/* 
* @Author: sxf
* @Date:   2014-10-02 20:47:00
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-17 21:00:17
*/
#include "Lex.h"
#include <iostream>
#include <fstream>
#include "RuleManager.h"
using namespace std;

Lex::Lex() {
	ruleManager = new RuleManager();
}

Lex::~Lex() {

}

Token* Lex::Read() {
    return ruleManager->Read();
}

void Lex::Init(const char* pData){
    // init the lex system
    ruleManager->combineAllDFA();
    ruleManager->InitCore();

    if (pData != NULL)
        setData(pData);
}

int Lex::AddRule(const char* pName,const char* pattern){
	return this->ruleManager->AddRule(pName,pattern);
} 

int Lex::FindRule(const char* pName){
    return this->ruleManager->FindRule(pName);
}

const char* Lex::getData(){
	return this->pData;
}

void Lex::setData(const char* pData){
	this->pData = pData;
    this->ruleManager->setData(pData);
}

int Lex::getRuleSize() {
    return ruleManager->getRuleSize();
}

const char* Lex::getRule(int id) {
    const Rule& r = ruleManager->getRule(id);
    return r.name.c_str();
}

bool Lex::ReadConfig(const char* path) {
    fstream cfgFile;  
    cfgFile.open(path);//打开文件      
    if(!cfgFile.is_open())  
    {  
        printf("can not open cfg file!\n");
        return false;  
    }
    char tmp[1000];  
    while(!cfgFile.eof())//循环读取每一行  
    {  
        cfgFile.getline(tmp,1000);//每行读取前1000个字符，1000个应该足够了  
        std::string line(tmp);  
        size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value  
        if(pos==string::npos) return false;  
        std::string key = line.substr(0,pos);//取=号之前  
        std::string value = line.substr(pos + 1);
        // printf("%s = %s\n",key.c_str(), value.c_str());
        AddRule(key.c_str(), value.c_str());
    }  
    
    return true;  
}
