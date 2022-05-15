/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Main.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon May 16 01:23:07 2022
================================================================*/

#include <iostream>
#include "Lab.hh"

using namespace std;

int main(int argc, char* argv[]) {
    Lab lab;
    lab.InitLab();
    lab.Run();
    return 0;
}
