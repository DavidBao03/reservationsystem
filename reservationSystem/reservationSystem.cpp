#include <iostream>
#include "indentity.h"
#include "teacher.h"
#include "student.h"
#include "manager.h"
#include "orderFile.cpp"
#include "globalFile.h"


using namespace std;

//进入管理员的子菜单
void managerMenu(Indentity *&manager) {
    while (true) {
        manager->operMenu();

        Manager *ma = (Manager *) manager;

        int select = 0;

        cin >> select;

        if (select == 1) {
            ma->addPerson();
        } else if (select == 2) {
            ma->showPerson();
        } else if (select == 3) {
            ma->showComputer();
        } else if (select == 4) {
            ma->cleanFile();
        } else {
            delete manager;
            cout << "注销成功" << endl;
            return;
        }
    }
}

void studentMenu(Indentity *&student) {
    while (true) {
        student->operMenu();

        Student *s = (Student *) student;

        int select;
        cin >> select;

        if (select == 1) {
            s->applyOrder();
        } else if (select == 2) {
            s->showMyOrder();
        } else if (select == 3) {
            s->showAllOrder();
        } else if (select == 4) {
            s->cancelOrder();
        } else {
            delete student;
            cout << "注销成功" << endl;
            return;
        }
    }
}

void teacherMenu(Indentity *&teacher) {
    while (true) {
        teacher->operMenu();

        Teacher *t = (Teacher *) teacher;

        int select;
        cin >> select;

        if (select == 1) {
            t->showAllOrder();
        } else if (select == 2) {
            t->validOrder();
        } else {
            delete teacher;
            cout << "注销成功" << endl;
            return;
        }
    }
}


void LoginIm(string fileName, int type) {
    Indentity *person = NULL;

    ifstream ifs;
    ifs.open(fileName, ios::in);

    if (!ifs.is_open()) {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if (type == 1)//学生
    {
        cout << "请输入你的学号： " << endl;
        cin >> id;
    } else if (type == 2) {
        cout << "请输入您的职工号： " << endl;
        cin >> id;
    }

    cout << "请输入用户名" << endl;
    cin >> name;

    cout << "请输入密码" << endl;
    cin >> pwd;

    if (type == 1) {
        //学生身份验证
        int fId;
        string fName;
        string fPwd;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "验证登录成功！ " << endl;

                person = new Student(id, name, pwd);

                studentMenu(person);

                return;
            }
        }

    } else if (type == 2) {
        //教师身份验证
        int fId;
        string fName;
        string fPwd;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "验证登录成功！ " << endl;

                person = new Teacher(id, name, pwd);

                teacherMenu(person);

                return;
            }
        }
    } else if (type == 3) {
        //管理员身份验证
        string fName;
        string fPwd;

        while (ifs >> fName && ifs >> fPwd) {
            if (fName == name && fPwd == pwd) {
                cout << "验证登录成功！ " << endl;

                person = new Manager(name, pwd);

                managerMenu(person);

                return;
            }
        }
    }

    cout << "验证登录失败！" << endl;
    return;
}

int main() {
    int select = 0;

    while (true) {
        cout << "请输入您的身份" << endl;
        cout << "1.学生代表" << endl;
        cout << "2.老   师" << endl;
        cout << "3.管 理 员" << endl;
        cout << "0.退   出" << endl;
        cout << "请输入您的选择" << endl;

        cin >> select;

        switch (select) {
            case 1: //学生身份
                LoginIm(STUDENT_FILE, 1);
                break;
            case 2: //老师身份
                LoginIm(TEACHER_FILE, 2);
                break;
            case 3: //管理员身份
                LoginIm(ADMIN_FILE, 3);
                break;
            case 0:  //退出系统
                cout << "欢迎下次使用" << endl;
                return 0;
                break;
            default:
                cout << "输入有误 请重新输入" << endl;
                break;
        }
    }

    return 0;
}
