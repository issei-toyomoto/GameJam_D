#include"common.h"
#include "player.h"
#include"DxLib.h"
#include"PadInput.h"
#include<Math.h>

Player::Player()
{
    //初期の座標
    X = SCREEN_WIDTH / 2;
    Y = SCREEN_HEIGHT / 2 + UI_SIZE / 2;

    //最高速度を設定する
    SpdX = 0;
    SpdY = 0;
    MSpdX = 8;
    MSpdY = 8;
}

Player::~Player()
{
}

void Player::Update() 
{
    //スティック入力値
    float InpX = InputControl::TipLeftLStick(STICKL_X);
    float InpY = -InputControl::TipLeftLStick(STICKL_Y);

    //スティック角度・傾き
    float Rad = InputControl::LstickRad();
    float Tilt = InputControl::LstickTilt();

    //加速度
    float add = 0.2;

    //スティックの傾きが一定以上なら加速
    if (0.2 <= Tilt) 
    {
        //X軸
        SpdX += add * InpX;
        //速度が最大速度以上なら調整する
        if (0 < InpX && MSpdX * InpX < SpdX)SpdX = MSpdX * InpX;
        if (InpX < 0 && SpdX < MSpdX * InpX)SpdX = MSpdX * InpX;

        //Y軸
        SpdY += add * InpY;
        //速度が最大速度以上なら調整する
        if (0 < InpY && MSpdY * InpY < SpdY)SpdY = MSpdY * InpY;
        if (InpY < 0 && SpdY < MSpdY * InpY)SpdY = MSpdY * InpY;
    }
    //スティックの傾きが一定以下なら減速
    else 
    {
        float absX = fabsf(SpdX);
        float absY = fabsf(SpdY);
        float total = absX + absY;

        if (SpdX < 0)
        {
            SpdX += add * (absX / total);
            if (0 < SpdX)SpdX = 0;
        }
        else if (0 < SpdX)
        {
            SpdX -= add * (absX / total);
            if (SpdX < 0)SpdX = 0;
        }

        if (SpdY < 0)
        {
            SpdY += add * (absY / total);
            if (0 < SpdY)SpdY = 0;
        }
        else if (0 < SpdY)
        {
            SpdY -= add * (absY / total);
            if (SpdY < 0)SpdY = 0;
        }
    }

    X += SpdX;
    while (X - BLOCK_SIZE / 2 < MARGIN_X)
    {
        X++;
    }

    while (SCREEN_WIDTH - MARGIN_X < X + BLOCK_SIZE / 2)
    {
        X--;
    }

    Y += SpdY;
    while (Y - BLOCK_SIZE / 2 < MARGIN_Y + 100)
    {
        Y++;
    }

    while (SCREEN_HEIGHT - MARGIN_Y < Y + BLOCK_SIZE / 2)
    {
        Y--;
    }
}

void Player::Draw() const
{
    DrawBox(X - BLOCK_SIZE / 2, Y - BLOCK_SIZE / 2, X + BLOCK_SIZE / 2, Y + BLOCK_SIZE / 2, 0x0000ff, true);

    DrawFormatString(200, 50, 0xffffff, "X : %f", InputControl::TipLeftLStick(STICKL_X));
    DrawFormatString(200, 70, 0xffffff, "Y : %f", InputControl::TipLeftLStick(STICKL_Y));

    DrawFormatString(350, 50, 0xffffff, "RAD  : %f", InputControl::LstickRad());
    DrawFormatString(350, 70, 0xffffff, "TILT : %f", InputControl::LstickTilt());

    DrawFormatString(500, 50, 0xffffff, "SPDX : %f", SpdX);
    DrawFormatString(500, 70, 0xffffff, "SPDY : %f", SpdY);
}
