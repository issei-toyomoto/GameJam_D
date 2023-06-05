#pragma once
#include "DxLib.h"

/*マクロ定義*/
#define BUTTONS 16		//XINPUTpadのボタン数
#define STICKL_X 1		
#define STICKL_Y 2		
#define MAXL_X 32767.f  //左スティックX軸の最大値(float型)
#define MAXL_Y 32767.f  //左スティックY軸の最大値(float型)

class InputControl
{
public:
    static int key_flg;			//静的メンバ変数
    static int now_key;
    static int old_key;
    static XINPUT_STATE xinput;	//メンバ変数の初期化

public:
    InputControl()		//関数の宣言
    {
        key_flg = 0;
        now_key = 0;
        old_key = 0;
    }

    static void Update();						//更新
    static int GetKey(int key);					//キー情報取得
    static int GetKeyDown(int key);				//キー押下状態取得
    static int PressBotton(int Button);			//キー入力情報取得
    static float TipLeftLStick(short StickL);	//スティック縦操作取得
};