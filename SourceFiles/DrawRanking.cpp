
#include"main.h"
DrawRanking::DrawRanking() {

    Ranking::ReadRanking();

};

DrawRanking::~DrawRanking() {

};

AbstractScene* DrawRanking::Update() {
    return this;
};

void DrawRanking::Draw()const {

    for (int i = 0; i < RANK_MAX; i++) {
        DrawFormatString(120, 100 + (i * 30), GetColor(255, 255, 255), "%d 位　 %s　%7d", Ranking::GetData(i).no, Ranking::GetData(i).name, Ranking::GetData(i).score);
    };

};