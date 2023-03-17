//
// Created by 鲍子硕 on 2023/3/16.
//
#pragma once

#include "indentity.h"

class Teacher : public Indentity {
public:
    //默认构造
    Teacher();

    //有参构造
    Teacher(int empId, string name, string pwd);

    //菜单界面
    void operMenu();

    //查看所有预约
    void showAllOrder();

    //审核预约
    void validOrder();

    //职工号
    int m_empId;
};

