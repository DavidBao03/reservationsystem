//
// Created by 鲍子硕 on 2023/3/16.
//

#include "teacher.h"
#include <vector>
#include "orderFile.h"

Teacher::Teacher() {

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd) {
    this->m_empId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu() {
    cout << "欢迎老师" << this->m_Name << "登陆" << endl;
    cout << "1.查看所有人的预约" << endl;
    cout << "2.审核预约" << endl;
    cout << "0.注销登录" << endl;
    cout << "请输入您的选择： " << endl;
}

//查看所有预约
void Teacher::showAllOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "无预约记录" << endl;
        return;
    }

    for (int i = 0; i < of.m_Size; i++) {

        cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
        cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
        cout << "学号：" << of.m_orderData[i]["stuId"] << " ";
        cout << "姓名：" << of.m_orderData[i]["stuName"] << " ";
        cout << "机房号：" << of.m_orderData[i]["roomId"] << " ";

        string status;
        // 1审核中 2已预约 -1预约失败 0取消预约
        cout << "预约状态：";
        if (of.m_orderData[i]["status"] == "1") {
            status = "审核中";
        } else if (of.m_orderData[i]["status"] == "2") {
            status = "已预约";
        } else if (of.m_orderData[i]["status"] == "-1") {
            status = "预约失败";
        } else if (of.m_orderData[i]["status"] == "0") {
            status = "已取消预约";
        }
        cout << status << endl;

    }
}

//审核预约
void Teacher::validOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "无预约记录" << endl;
        return;
    }

    cout << "待审核的预约记录如下：" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < of.m_Size; i++) {

        if (of.m_orderData[i]["status"] == "1") {
            v.push_back(i);
            cout << index++ << " ";
            cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
            cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
            cout << "机房号：" << of.m_orderData[i]["roomId"] << " ";

            string status;
            // 1审核中 2已预约 -1预约失败 0取消预约
            cout << "预约状态：";
            if (of.m_orderData[i]["status"] == "1") {
                status = "审核中";
            }
            cout << status << endl;
        }

    }

    cout << "请输入审核的记录，按0返回" << endl;
    int select = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                int ret = 0;
                cout << "请输入审核结果：" << endl;
                cout << "1.通过" << endl;
                cout << "2.不通过" << endl;
                cin >> ret;
                if (ret == 1) {
                    of.m_orderData[v[select - 1]]["status"] = "2";
                } else {
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "审核完毕" << endl;
                break;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
}