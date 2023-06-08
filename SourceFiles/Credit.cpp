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
     // �摜�ǂݍ���
   
    // �w�i�\��
    DrawGraph(0, 0, img_title, TRUE);
    SetFontSize(32);
    DrawString(50, 50, "���؂肵���f��", GetColor(0, 255, 0));
    DrawString(50, 100, "���ʉ����{", GetColor(255, 0, 0));
    DrawString(50, 150, "���炷�Ƃ�", GetColor(255, 0, 0));
    DrawString(50, 200, "DOVA-SYNDROME", GetColor(255, 0, 0));

    DrawString(50, 400, "Team-D�@�����o�[", GetColor(0, 255, 0));
    DrawString(50, 450, "�L���ꐬ�@���n���ā@�����с@��[�i�M �����N���@���� ���]�@�L�� ���", GetColor(255, 0, 0));
   /* ChangeScen();*/
    DrawString(530, 600, "A�{�^���Ŗ߂�", GetColor(255, 0, 0));
}
