#pragma once
#include"common.h"
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

    int Image[12];   //プレイヤーキャラ画像
    int SickleImg;  //鎌の画像

    int Attackse;   //攻撃効果音

    int Walk;       //歩行アニメーション

public:
    Player();
    ~Player();

    void Update();
    void Draw()const;
    void DrawSickle()const;

    float GetX() { return X; }
    float GetY() { return Y; }

    int AtkPos(char XY, double Dis) const;
    void Reset() 
    {
        //初期の座標
        X = SCREEN_WIDTH / 2;
        Y = SCREEN_HEIGHT / 2 + UI_SIZE / 2;

        //最高速度を設定する
        SpdX = 0;
        SpdY = 0;
        MSpdX = 8;
        MSpdY = 8;
        
        Angle = 0;
        Way = 0;
        Attack = 0;
        Combo = 0;
    }
};