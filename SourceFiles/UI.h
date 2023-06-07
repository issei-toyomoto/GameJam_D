#pragma once

class UI  {
private:    
    int score;
    int time;
    int stage;
    int Timelimit;
    int FPSCnt;
public:
    UI();
    ~UI();

    int Update();

    void Draw(int score,int stage) const;

};