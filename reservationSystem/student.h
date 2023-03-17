//
// Created by 鲍子硕 on 2023/3/16.
//

#pragma once

#include "indentity.h"
#include <vector>
#include "computerRoom.h"
#include "globalFile.h"
#include <fstream>

class Student : public Indentity {
public:

    //默认构造
    Student() {

    }

    //有参构造
    Student(int id, string name, string pwd);

    //菜单界面
    void operMenu();

    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    int m_Id;

    vector<ComputerRoom> vCom;
};