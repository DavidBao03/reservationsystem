//
// Created by 鲍子硕 on 2023/3/17.
//
#pragma once

#include <iostream>

using namespace std;

#include "globalFile.h"
#include <fstream>
#include <map>

class OrderFile {
public:
    OrderFile();

    void updateOrder();

    int m_Size;

    map<int, map<string, string>> m_orderData;
};