#pragma once
#ifndef MENU_HH_
#define MENU_HH_

#include "WindowBase.hh"

class Menu : public WindowBase {
  public:
    Menu();

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif