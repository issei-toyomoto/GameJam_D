#pragma once
class Player
{
private:
    int X, Y;   //座標
    float SpdX, SpdY;   //速度
    float MSpdX, MSpdY;   //最高速度

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

};