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

    LoadDivGraph("images/move.png", 12, 12, 1, 50, 85, Image);
    SickleIng = LoadGraph("images/kama.png");
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
    if (0.2 <= Tilt && (!Attack || (2 <= Combo && Attack <= 6)))
    {
        //歩行アニメーション開始
        Walk++;

        //角度取得
        Angle = 180 / 3.14 * Rad + 180;
        
        //攻撃方向を得る
        Way = (Angle - 22.5) / 45;
        if (Angle < 22.5 || 360 - 22.5 < Angle)Way = 7;

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
        //歩行アニメーションリセット
        Walk = 0;

        //速度の合計を取る
        float absX = fabsf(SpdX);
        float absY = fabsf(SpdY);
        float total = absX + absY;

        if (Attack) 
        {
            absX *= 3;
            absY *= 3;
        }

        //X速度を合計に対する比率に応じて減速させる
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

        //Y速度を合計に対する比率に応じて減速させる
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

    //攻撃
    if (Attack) 
    {
        Attack++;
        if (30 < Attack) 
        {
            Attack = 0;
            Combo = 0;
        }
    }

    //攻撃に移行
    if (InputControl::OnButton(XINPUT_BUTTON_B) && (Attack == 0 || 15 <= Attack))
    {
        Attack = 1;
        Combo++;

        if (0.2 < Tilt)
        {
            //角度取得
            Angle = 180 / 3.14 * Rad + 180;

            //攻撃方向を得る
            Way = (Angle - 22.5) / 45;
            if (Angle < 22.5 || 360 - 22.5 < Angle)Way = 7;
        }
    }
}

void Player::Draw() const
{
    DrawSickle();

    //プレイヤーキャラ表示
    int Panim = Walk / 8 % 4;
    if      (225 <= Angle && Angle <= 315)  DrawRotaGraph2(X, Y, 25, 60, 1, 0, Image[8 + Panim], true);
    else if (135 <= Angle && Angle <= 225)  DrawRotaGraph2(X, Y, 25, 60, 1, 0, Image[0 + Panim], true, true);
    else if (45 <= Angle && Angle <= 135)   DrawRotaGraph2(X, Y, 25, 60, 1, 0, Image[4 + Panim], true);
    else                                    DrawRotaGraph2(X, Y, 25, 60, 1, 0, Image[0 + Panim], true);

    DrawCircle(X, Y, BLOCK_SIZE * 1, 0xff9cbc, false, 3);
}

void Player::DrawSickle()const
{
    if (Attack)
    {
        double stX = 0, stY = 0;		//振りかぶる前の座標
        double finX = 0, finY = 0;		//振りかぶった後の座標
        double Dis = 0;			//体の中心からの距離
        bool Xturn = true;      //画像反転

        double finAng = 0;	//振りかぶる角度
        if (Attack <= 6)
        {
            if (Combo % 2 == 0)
            {
                finAng = 45 * (-Way + 3) + 180 - (180 / 5 * (Attack - 1));
                Xturn = false;
            }
            else finAng = 45 * (-Way + 3) + (180 / 5 * (Attack - 1));
            stX = X;
            stY = Y;
            Dis = 50;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
        else
        {
            if (Combo % 2 == 0)
            {
                finAng = 45 * (-Way + 3);
                Xturn = false;
            }
            else finAng = 45 * (-Way + 3) + 180;
            stX = X;
            stY = Y;
            Dis = 50;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
        DrawRotaGraph(finX, finY, 1, (3.14 / 180) * finAng, SickleIng, true, Xturn);
    }
}

int Player::AtkPos(char XY, double Dis) const
{
    double stX = 0, stY = 0;		//振りかぶる前の座標
    double finX = 0, finY = 0;		//振りかぶった後の座標
    bool Xturn = true;      //画像反転

    double finAng = 0;	//振りかぶる角度
    if (Attack)
    {
        if (Attack <= 6)
        {
            if (Combo % 2 == 0)
            {
                finAng = 45 * (-Way + 3) + 180 - (180 / 5 * (Attack - 1));
                Xturn = false;
            }
            else finAng = 45 * (-Way + 3) + (180 / 5 * (Attack - 1));
            stX = X;
            stY = Y;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
        else
        {
            if (Combo % 2 == 0)
            {
                finAng = 45 * (-Way + 3);
                Xturn = false;
            }
            else finAng = 45 * (-Way + 3) + 180;
            stX = X;
            stY = Y;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
    }
    else return -1;

    if (XY == 'X')return finX;
    if (XY == 'Y')return finY;

    return -1;
}
