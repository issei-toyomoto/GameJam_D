#pragma once

#include "GameMainScene.h"

class UI  {
private:    
    static int score;
    static int time;
    static int stage;
    static int Timelimit;
    static int FPSCnt;
public:
    /*UI();
    ~UI();*/

    static int Update();
    static void Draw();
};