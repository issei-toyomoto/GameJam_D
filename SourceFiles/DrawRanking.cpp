#include"DrawRanking.h"
#include"main.h"

DrawRanking::DrawRanking()
{
    Ranking::ReadRanking();
    BackImg = LoadGraph("images/Back.png");
};

DrawRanking::~DrawRanking()
{
    // フォント削除
    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            DeleteFontToHandle(font[i][j]);
        }
    }
};

AbstractScene* DrawRanking::Update()
{
    if (InputControl::OnButton(XINPUT_BUTTON_A)|| InputControl::OnButton(XINPUT_BUTTON_B))
    {
        return new Title();
    }

    return this;
};

void DrawRanking::Draw()const 
{
    SetFontSize(64);

    DrawGraph(0, 0, BackImg, TRUE);

    for (int i = 0; i < RANK_MAX; i++) {
        DrawFormatString(120, 100 + (i * 90), GetColor(0, 0, 0), "%d 位　 %s", Ranking::GetData(i).no, Ranking::GetData(i).name);
        DrawFormatString(700, 100 + (i * 90), GetColor(0, 0, 0), "%7d", Ranking::GetData(i).score);
        /*シーン遷移*/
        DrawFormatString(120, 600, GetColor(0, 0, 0), "A/Bボタンでタイトルへ",TRUE);
    };

};