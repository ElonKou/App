#pragma once
#ifndef LAB_HH_
#define LBB_HH_

#include "MainViewport.hh"

class Lab {
  public:
    MainViewport* m_viewport;

    Lab();

    ~Lab();

    void InitLab();

    void Run();
};

#endif