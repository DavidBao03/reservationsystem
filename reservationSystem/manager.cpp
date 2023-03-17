//
// Created by 鲍子硕 on 2023/3/16.
//

#include "manager.h"
#include "globalFile.h"
#include <fstream>
#include <algorithm>

//默认构造
Manager::Manager() {

}

//有参构造
Manager::Manager(string name, string pwd) {
    this->m_Name = name;
    this->m_Pwd = pwd;
    this->initVector();

    //初始化机房信息
    ifstream ifs(COMPUTER_FILE, ios::in);

    ComputerRoom computerRoom;
    while (ifs >> computerRoom.m_ComId && ifs >> computerRoom.m_MaxNum) {
        v_computerRoom.push_back(computerRoom);
    }
    ifs.close();
    cout << "机房的数量为：" << v_computerRoom.size() << endl;
}

//菜单界面
void Manager::operMenu() {

    cout << "欢迎管理员" << this->m_Name << "登陆" << endl;
    cout << "1.添加账号" << endl;
    cout << "2.查看账号" << endl;
    cout << "3.查看机房" << endl;
    cout << "4.清空预约" << endl;
    cout << "0.注销登录" << endl;
    cout << "请输入您的选择： " << endl;

}

//添加账号
void Manager::addPerson() {


    cout << "请输入您想添加账号的类型" << endl;
    cout << "1.学生账号" << endl;
    cout << "2.老师账号" << endl;

    int select = 0;
    cin >> select;

    string tip;
    ofstream ofs;

    if (select == 1) {
        tip = "请输入学生学号： ";
        ofs.open(STUDENT_FILE, ios::out | ios::app);
    } else if (select == 2) {
        tip = "请输入老师职工号： ";
        ofs.open(TEACHER_FILE, ios::out | ios::app);
    } else {
        cout << "添加失败！" << endl;
        return;
    }

    int id;
    string name;
    string pwd;

    cout << tip << endl;
    cin >> id;
    if (this->checkRepeat(id, select)) {
        cout << "号码重复，添加失败" << endl;
        return;
    }

    cout << "请输入姓名： " << endl;
    cin >> name;

    cout << "请输入密码： " << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << endl;
    cout << "添加成功！ " << endl;
    ofs.close();

    this->initVector();
}

void printStudent(Student &student) {
    cout << "学号：" << student.m_Id << " 姓名： " << student.m_Name
         << " 密码：" << student.m_Pwd << endl;
}

void printTeacher(Teacher &teacher) {
    cout << "职工号：" << teacher.m_empId << " 姓名： " << teacher.m_Name
         << " 密码： " << teacher.m_Pwd << endl;
}

//查看账号
void Manager::showPerson() {
    cout << "请输入您想查看的人员" << endl;
    cout << "1.学生" << endl;
    cout << "2.老师" << endl;
    int select;
    cin >> select;
    if (select == 1) {
        cout << "所有学生的信息如下： " << endl;
        for_each(v_student.begin(), v_student.end(), printStudent);
    } else {
        cout << "所有老师的信息如下： " << endl;
        for_each(v_teacher.begin(), v_teacher.end(), printTeacher);
    }
}

//查看机房信息
void Manager::showComputer() {
    cout << "机房的信息如下： " << endl;
    for (vector<ComputerRoom>::iterator it = v_computerRoom.begin(); it != v_computerRoom.end(); it++) {
        cout << "机房编号：" << it->m_ComId << " 最大容量：" << it->m_MaxNum << endl;
    }
}

//清空预约记录
void Manager::cleanFile() {
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();
    cout << "清空成功！" << endl;
}

//初始化容器
void Manager::initVector() {
    ifstream ifs(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败！ " << endl;
        return;
    }
    v_student.clear();

    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
        v_student.push_back(s);
    }
    cout << "当前有" << v_student.size() << "个学生" << endl;
    ifs.close();

    ifstream ifs1(TEACHER_FILE, ios::in);
    if (!ifs1.is_open()) {
        cout << "文件打开失败！ " << endl;
        return;
    }
    v_teacher.clear();

    Teacher t;
    while (ifs1 >> t.m_empId && ifs1 >> t.m_Name && ifs1 >> t.m_Pwd) {
        v_teacher.push_back(t);
    }
    cout << "当前有" << v_teacher.size() << "个老师" << endl;
    ifs.close();
}

//去重函数
bool Manager::checkRepeat(int id, int type) {
    if (type == 1) {
        for (vector<Student>::iterator it = v_student.begin(); it != v_student.end(); it++) {
            if (it->m_Id == id) {
                return true;
            }
        }
    } else {
        for (vector<Teacher>::iterator it = v_teacher.begin(); it != v_teacher.end(); it++) {
            if (it->m_empId == id) {
                return true;
            }
        }
    }
    return false;
}

