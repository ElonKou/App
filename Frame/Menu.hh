#pragma once
#ifndef MENU_HH_
#define MENU_HH_

#include "WindowBase.hh"

class Menu : public WindowBase {
  private:
    bool show_demo;

  public:
    Menu();

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif