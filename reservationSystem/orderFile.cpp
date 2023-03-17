//
// Created by 鲍子硕 on 2023/3/17.
//

#include "orderFile.h"

OrderFile::OrderFile() {
    ifstream ifs(ORDER_FILE, ios::in);

    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;

    this->m_Size = 0;

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName
           && ifs >> roomId && ifs >> status) {
        string key;
        string value;
        map <string, string> m;

        int pos = date.find(":");
        if (pos != -1) {
            key = date.substr(0, pos);
            value = date.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        pos = interval.find(":");
        if (pos != -1) {
            key = interval.substr(0, pos);
            value = interval.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        pos = stuId.find(":");
        if (pos != -1) {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        pos = stuName.find(":");
        if (pos != -1) {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        pos = roomId.find(":");
        if (pos != -1) {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        pos = status.find(":");
        if (pos != -1) {
            key = status.substr(0, pos);
            value = status.substr(pos + 1);
            m.insert(make_pair(key, value));
        }

        m_orderData.insert(make_pair(m_orderData.size(), m));
        m_Size++;
    }
    ifs.close();
}

void OrderFile::updateOrder() {
    if (m_Size == 0) {
        return;
    }

    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < m_Size; i++) {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << " ";
    }
    ofs.close();
}
