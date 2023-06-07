#pragma once

class UI  {
private:    
    int score;
    int time;
    int stage;
    int Timelimit;
    int FPSCnt;
    bool count = true;
public:
    UI();
    ~UI();

    void switchcount() { 
        count = !count;
        FPSCnt = 0;
    }
    int GetTime() { return Timelimit; }

    int Update(int StopTime);

    void Draw(int score,int stage) const;

};