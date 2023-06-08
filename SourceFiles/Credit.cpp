#include "Credit.h"
#include"DxLib.h"
#include "PadInput.h"
#include "main.h"
Credit::Credit() 
{
    if ((img_title = LoadGraph("Resources/Images/title.png")) == -1) {};
}
Credit::~Credit() {

}
AbstractScene* Credit::Update() {
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;
    if (InputControl::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_ESCAPE)) {
        return new Title();
    }
    return this;
}
void Credit::Draw()const
{
 /*   DrawGraph(0, 0, GetArrayImages(title.png, 0), FALSE);*/
     // âÊëúì«Ç›çûÇ›
   
    // îwåiï\é¶
    DrawGraph(0, 0, img_title, TRUE);
    SetFontSize(64);
    DrawString(100, 100, "Ç®éÿÇËÇµÇΩëfçﬁ", GetColor(0, 255, 0));
    DrawString(100, 200, "å¯â âπÉâÉ{", GetColor(255, 0, 0));
    DrawString(100, 300, "Ç¢ÇÁÇ∑Ç∆Ç‚", GetColor(255, 0, 0));
    DrawString(100, 400, "DOVA-SYNDROME", GetColor(255, 0, 0));
   /* ChangeScen();*/
    DrawString(530, 600, "AÉ{É^ÉìÇ≈ñﬂÇÈ", GetColor(255, 0, 0));
}
