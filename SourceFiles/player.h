#pragma once
class Player
{
private:
    int X, Y;   //���W
    float SpdX, SpdY;   //���x
    float MSpdX, MSpdY;   //�ō����x

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

};