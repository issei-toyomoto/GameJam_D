#include "PadInput.h"
#include"DxLib.h"

#include<math.h>

//関数の定義
XINPUT_STATE InputControl::xinput;
int InputControl::key_flg;
int InputControl::now_key;
int InputControl::old_key;

void InputControl::Update() //キー入力情報更新
{
    old_key = now_key;
    now_key = GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
    key_flg = now_key & ~old_key; //長押し拒否(2フレーム以上読込の拒否)
}

int InputControl::GetKey(int key) //長押し許容
{
    if (now_key & key)
    {
        return TRUE;
    }

    return FALSE;
}

int InputControl::GetKeyDown(int key) //長押し拒否 //キー押状態認識
{
    if (key_flg & key)
    {
        return TRUE;
    }

    return FALSE;
}

int InputControl::PressBotton(int Button)//ボタン入力状態認識
{
    int OnPress = xinput.Buttons[Button];

    return OnPress;
}
//スティックの傾き割合
float InputControl::TipLeftLStick(short StickL)
{
    if (StickL == STICKL_X)
    {
        float ratioL_X = xinput.ThumbLX / MAXL_X;

        //左スティックの横軸を最大値を1とした割合
        return ratioL_X;
    }
    else if (StickL == STICKL_Y)
    {
        float ratioL_Y = xinput.ThumbLY / MAXL_Y;

        //左スティックの縦軸を最大値を1とした割合
        return ratioL_Y;
    }

    return 0;
}

float InputControl::LstickRad()
{
    float L_X = xinput.ThumbLX / MAXL_X;
    float L_Y = xinput.ThumbLY / MAXL_Y;

    if (L_X == 0 && L_Y == 0)return 0;
    return (float)atan2(L_Y, L_X);
}

float InputControl::LstickTilt()
{
    float L_X = xinput.ThumbLX / MAXL_X;
    float L_Y = xinput.ThumbLY / MAXL_Y;

    L_X *= L_X;
    L_Y *= L_Y;

    if (L_X == 0 && L_Y == 0)return 0;
    return (float)sqrt(L_Y + L_X);
}