
#pragma once
#include"common.h"
class RunWeed
{
private:
    float X, Y;   //座標
    float SpdX, SpdY;   //速度
    float MSpd;   //最高速度
    float Angle = 0;          //移動方向(-180～180)

    int RunTime = 0;          //逃げる時間
    float RunRad = 0;           //逃げる角度
    int RunCool = 0;            //逃げた後の待機時間

    int Image;                  //画像

public:
    RunWeed(float InitX, float InitY);
    ~RunWeed();

    void Update(float Px, float Py);
    void Draw()const;

    float GetX() { return X; }
    float GetY() { return Y; }
};
