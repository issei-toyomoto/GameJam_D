#include "Credit.h"
#include"DxLib.h"
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
    return this;
}
void Credit::Draw()const
{
 /*   DrawGraph(0, 0, GetArrayImages(title.png, 0), FALSE);*/
     // �摜�ǂݍ���
   
    // �w�i�\��
    DrawGraph(0, 0, img_title, TRUE);
    DrawString(100, 100, "���؂肵���f��", GetColor(0, 255, 0));
    DrawString(100, 200, "���ʉ����{", GetColor(255, 0, 0));
    DrawString(100, 300, "���炷�Ƃ�", GetColor(255, 0, 0));
    DrawString(100, 400, "DOVA-SYNDROME", GetColor(255, 0, 0));
   /* ChangeScen();*/

    DrawString(530, 600, "A�{�^���Ŗ߂�", GetColor(255, 0, 0));
}
