/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Lab.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "Lab.hh"
#include <iostream>

using namespace std;

MainViewport* viewport = nullptr;

Lab::Lab() {}

Lab::~Lab() {
    if (m_viewport) {
        delete m_viewport;
    }
    std::cout << "destructor Lab" << std::endl;
}

void Lab::InitLab() {
    m_viewport = new MainViewport();
    viewport   = m_viewport;
}

void Lab::Run() {
    m_viewport->StartWindow();
}
