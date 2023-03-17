//
// Created by 鲍子硕 on 2023/3/16.
//
#pragma once

#include <vector>
#include "student.h"
#include "computerRoom.h"
#include "teacher.h"
#include "indentity.h"

class Manager : public Indentity {
public:
    //默认构造
    Manager();

    //有参构造
    Manager(string name, string pwd);

    //菜单界面
    void operMenu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //初始化容器
    void initVector();

    //去重函数
    bool checkRepeat(int id, int type);

    //学生容器
    vector<Student> v_student;

    //老师容器
    vector<Teacher> v_teacher;

    //机房信息
    vector<ComputerRoom> v_computerRoom;
};

