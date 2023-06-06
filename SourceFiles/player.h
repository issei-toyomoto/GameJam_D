#pragma once
class Player
{
private:
    float X, Y;   //À•W
    float SpdX, SpdY;   //‘¬“x
    float MSpdX, MSpdY;   //Å‚‘¬“x
    float Angle = 0;          //ˆÚ“®•ûŒü(-180`180)
    int Way = 0;               //UŒ‚•ûŒü(1`8)

    int Attack = 0;     //UŒ‚ŠÇ—
    int Combo = 0;      //UŒ‚‰ñ”

    int SickleIng;  //Š™‚Ì‰æ‘œ

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;

};