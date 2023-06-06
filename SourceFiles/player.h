#pragma once
class Player
{
private:
    float X, Y;   //ç¿ïW
    float SpdX, SpdY;   //ë¨ìx
    float MSpdX, MSpdY;   //ç≈çÇë¨ìx

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

};