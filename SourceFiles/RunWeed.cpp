#include "RunWeed.h"
#include"common.h"
#include"DxLib.h"
#include<Math.h>

RunWeed::RunWeed(float InitX, float InitY)
{
    //初期の座標
    X = InitX;
    Y = InitY;

    //最高速度を設定する
    SpdX = 0;
    SpdY = 0;
    MSpd = 16;

    //画像を設定する
    Image = LoadGraph("images/kusa.png");
}

RunWeed::~RunWeed()
{
}

void RunWeed::Update(float Px, float Py)
{

    //プレイヤー間のX軸、Y軸との距離を取る
    float DisX = X - Px;
    float DisY = Y - Py;

    //プレイヤー間の距離
    float AbsX = fabsf(Px - X);
    float AbsY = fabsf(Py - Y);
    float Dis = (float)sqrt(AbsX * AbsX + AbsY * AbsY);

    //ゼロ除算防止
    //if (DisX == 0.f)DisX = 1.f;
    //if (DisY == 0.f)DisY = 1.f;

    //追い詰められた時の動作
    //画面左端に追い詰められた時
    if (X < MARGIN_X + BLOCK_SIZE)
    {
        //左上の角にいる時
        if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE)
        {
            //プレイヤーの位置に応じて右か下に逃げる
            if (Px < Py - UI_SIZE)
            {
                DisX = 1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = 1;
            }
        }
        //左下の角にいる時
        else if (SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
        {
            //プレイヤーの位置に応じて右か上に逃げる
            if (Px < SCREEN_HEIGHT - Py)
            {
                DisX = 1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = -1;
            }
        }
        //角にいないとき
        else
        {
            //プレイヤーと壁との反射角を取るように逃げる
            DisX = -DisX;
        }
    }
    //画面右端に追い詰められた時
    else if (SCREEN_WIDTH - MARGIN_X - BLOCK_SIZE < X)
    {
        //右上の角にいる時
        if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE)
        {
            //プレイヤーの位置に応じて左か下に逃げる
            if (SCREEN_WIDTH - Px < Py - UI_SIZE)
            {
                DisX = -1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = 1;
            }
        }
        //右下の角にいる時
        else if (SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
        {
            //プレイヤーの位置に応じて左か上に逃げる
            if (SCREEN_WIDTH - Px < SCREEN_HEIGHT - Py)
            {
                DisX = -1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = -1;
            }
        }
        //角にいないとき
        else
        {
            //プレイヤーと壁との反射角を取るように逃げる
            DisX = -DisX;
        }
    }
    //画面上か下の端にいるとき
    else if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE || SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
    {
        //プレイヤーと壁との反射角を取るように逃げる
        DisY = -DisY;
    }

    //プレイヤーから離れるための角度
    float Rad = (float)atan2(DisY, DisX);

    //プレイヤー間の距離
    //DisX = fabsf(Px - X);
    //DisY = fabsf(Py - Y);
    //float Dis = (float)sqrt(DisX * DisX + DisY * DisY);

    //角度ラジアン
    float InpX = (float)cos(Rad);
    float InpY = (float)tan(Rad);


    //プレイヤーとの距離が一定以上なら加速
    if (Dis <= 150 && RunCool == 0)
    {
        RunTime = 15;
        RunCool = RunTime + 60;
        RunRad = Rad;
    }

    if (RunTime)
    {
        //X軸
        SpdX = MSpd * (float)cos(RunRad);

        //Y軸
        SpdY = MSpd * (float)sin(RunRad);
        RunTime--;
    }
    //スティックの傾きが一定以下なら減速
    else
    {
        SpdX = 0;
        SpdY = 0;
    }

    if (--RunCool < 0)RunCool = 0;

    //X座標をX速度に応じて変化させる
    X += SpdX;
    //画面端にたどり着いたときに補正する
    while (X - BLOCK_SIZE / 2 < MARGIN_X)
    {
        X++;
    }

    while (SCREEN_WIDTH - MARGIN_X < X + BLOCK_SIZE / 2)
    {
        X--;
    }

    //Y座標をY速度に応じて変化させる
    Y += SpdY;
    //画面端にたどり着いたときに補正する
    while (Y - BLOCK_SIZE / 2 < MARGIN_Y + 100)
    {
        Y++;
    }

    while (SCREEN_HEIGHT - MARGIN_Y < Y + BLOCK_SIZE / 2)
    {
        Y--;
    }
}

void RunWeed::Draw() const
{
    //DrawBox(X - BLOCK_SIZE / 2, Y - BLOCK_SIZE / 2, X + BLOCK_SIZE / 2, Y + BLOCK_SIZE / 2, 0x00ff00, true);
    DrawRotaGraph(X, Y, 1, 0, Image, true);
}