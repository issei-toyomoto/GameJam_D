
#pragma once
#include"common.h"
class RunWeed
{
private:
    float X, Y;   //���W
    float SpdX, SpdY;   //���x
    float MSpd;   //�ō����x
    float Angle = 0;          //�ړ�����(-180�`180)

    int RunTime = 0;          //�����鎞��
    float RunRad = 0;           //������p�x
    int RunCool = 0;            //��������̑ҋ@����

    int Image;                  //�摜

public:
    RunWeed(float InitX, float InitY);
    ~RunWeed();

    void Update(float Px, float Py);
    void Draw()const;

    float GetX() { return X; }
    float GetY() { return Y; }
};
