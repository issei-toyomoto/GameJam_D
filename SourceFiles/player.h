#pragma once
class Player
{
private:
    float X, Y;   //���W
    float SpdX, SpdY;   //���x
    float MSpdX, MSpdY;   //�ō����x
    float Angle = 0;          //�ړ�����(-180�`180)
    int Way = 0;               //�U������(1�`8)

    int Attack = 0;     //�U���Ǘ�
    int Combo = 0;      //�U����

    int SickleIng;  //���̉摜

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

};