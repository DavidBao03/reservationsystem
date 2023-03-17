//
// Created by 鲍子硕 on 2023/3/16.
//

#include "student.h"
#include "orderFile.h"

Student::Student(int id, string name, string pwd) {
    m_Id = id;
    m_Name = name;
    m_Pwd = pwd;

    ifstream ifs(COMPUTER_FILE, ios::in);

    ComputerRoom computerRoom;
    while (ifs >> computerRoom.m_ComId && ifs >> computerRoom.m_MaxNum) {
        vCom.push_back(computerRoom);
    }
    ifs.close();
}

//菜单界面
void Student::operMenu() {
    cout << "欢迎学生" << this->m_Name << "登陆" << endl;
    cout << "1.申请预约" << endl;
    cout << "2.查看我的预约" << endl;
    cout << "3.查看所有人的预约" << endl;
    cout << "4.取消预约" << endl;
    cout << "0.注销登录" << endl;
    cout << "请输入您的选择： " << endl;
}

//申请预约
void Student::applyOrder() {
    cout << "机房的开放时间为周一至周五" << endl;
    cout << "1.周一" << endl;
    cout << "2.周二" << endl;
    cout << "3.周三" << endl;
    cout << "4.周四" << endl;
    cout << "5.周五" << endl;
    cout << "请输入你的选择： " << endl;

    int date = 0; //日期
    int interval = 0; //时间段
    int room = 0; //机房编号

    while (true) {
        cin >> date;
        if (date >= 1 && date <= 5) {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请输入申请的时间段" << endl;
    cout << "1.上午" << endl;
    cout << "2.下午" << endl;

    while (true) {
        cin >> interval;
        if (interval >= 1 && interval <= 2) {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请选择机房" << endl;
    cout << vCom[0].m_ComId << "号机房的容量为： " << vCom[0].m_MaxNum << endl;
    cout << vCom[1].m_ComId << "号机房的容量为： " << vCom[1].m_MaxNum << endl;
    cout << vCom[2].m_ComId << "号机房的容量为： " << vCom[2].m_MaxNum << endl;

    while (true) {
        cin >> room;
        if (room >= 1 && room <= 3) {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "预约成功，审核中" << endl;

    ofstream ofs(ORDER_FILE, ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << " " << endl;

    ofs.close();

}

//查看自身预约
void Student::showMyOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "无预约记录" << endl;
        return;
    }

    for (int i = 0; i < of.m_Size; i++) {
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
            cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
            cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
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
}

//查看所有预约
void Student::showAllOrder() {
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

//取消预约
void Student::cancelOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "无预约记录" << endl;
        return;
    }

    cout << "审核中获预约成功的记录可以取消，请输入取消的记录" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < of.m_Size; i++) {
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
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
                } else if (of.m_orderData[i]["status"] == "2") {
                    status = "已预约";
                }
                cout << status << endl;
            }
        }
    }

    cout << "请输入取消的记录，按0返回" << endl;
    int select = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                of.m_orderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "已成功取消预约" << endl;
                break;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
}
