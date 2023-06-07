#include"DrawRanking.h"
#include"main.h"
DrawRanking::DrawRanking()
{
    ranking::ranking()
        {
           /* ranking[i];*/
            i = 0;
            RANKING_MAX=10;
        }
        void ranking::Init()
}
DrawRanking::~DrawRanking()
{

}
AbstractScene* DrawRanking::Update()
{

}
void DrawRanking::Draw()const
{
    for (int i = 0; i < RANKING_MAX; i++) {
        DrawFormatString(120, 100 + (i * 30), GetColor(255, 255, 255), "%d ˆÊ@ %.1f •b", i + 1, Ranking[i]);
    }
}