#pragma once
class Player
{
private:
    float X, Y;   //座標
    float SpdX, SpdY;   //速度
    float MSpdX, MSpdY;   //最高速度
    float Angle = 0;          //移動方向(-180～180)
    int Way = 0;               //攻撃方向(1～8)

    int Attack = 0;     //攻撃管理
    int Combo = 0;      //攻撃回数

    int SickleIng;  //鎌の画像

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

    float GetX() { return X; }
    float GetY() { return Y; }

    int AtkPos(char XY, double Dis) const;
};