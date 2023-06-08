#pragma once

class UI  {
private:    
    int score;
    int stage;
    int Timelimit;
    int FPSCnt;
    bool count = true;
public:
    UI();
    ~UI();

    void switchcount() { 
        count = !count;
    }
    int GetTime() { return Timelimit; }
    void SetTime(int Time) 
    { 
        Timelimit = Time;
        FPSCnt = 1;
    }

    int Update();

    void Draw(int score,int stage) const;

};