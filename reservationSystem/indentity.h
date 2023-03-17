//
// Created by 鲍子硕 on 2023/3/16.
//
#pragma once

#include <iostream>

using namespace std;

//身份抽象基类
class Indentity {
public:
    //操作菜单 纯虚函数
    virtual void operMenu() = 0;

    virtual ~Indentity() = 0;

    //用户名
    string m_Name;
    //密码
    string m_Pwd;
};

