/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Main.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon May 16 01:23:07 2022
================================================================*/

#include "AppDemo.hh"
#include "SimpleImage.hh"

int main(int argc, char* argv[]) {
    AppDemo demo;
    demo.InitApp();
    demo.RunApp();

    // unsigned char  cc[3] = {0, 100, 102};
    // unsigned char* dd    = cc;
    // std::cout << sizeof(unsigned char) << std::endl;
    // std::cout << sizeof(unsigned char*) << std::endl;
    // std::cout << dd << std::endl;
    // std::cout << (void*)cc << std::endl;
    // std::cout << cc[0] << std::endl;
    // std::cout << cc[1] << std::endl;
    // std::cout << cc[2] << std::endl;
    return 0;
}
