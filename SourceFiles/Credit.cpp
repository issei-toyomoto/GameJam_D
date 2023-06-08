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
     // 画像読み込み
   
    // 背景表示
    DrawGraph(0, 0, img_title, TRUE);
    SetFontSize(32);
    DrawString(50, 50, "お借りした素材", GetColor(0, 255, 0));
    DrawString(50, 100, "効果音ラボ", GetColor(255, 0, 0));
    DrawString(50, 150, "いらすとや", GetColor(255, 0, 0));
    DrawString(50, 200, "DOVA-SYNDROME", GetColor(255, 0, 0));

    DrawString(50, 400, "Team-D　メンバー", GetColor(0, 255, 0));
    DrawString(50, 450, "豊元一成　下地隆翔　加藤錦　喜納司貴 仲西康生　島袋 叶望　有川 大晟", GetColor(255, 0, 0));
   /* ChangeScen();*/
    DrawString(530, 600, "Aボタンで戻る", GetColor(255, 0, 0));
}
