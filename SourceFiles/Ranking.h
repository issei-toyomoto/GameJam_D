#pragma once
#include"AbstractScene.h"

#define RANK_MAX 5
#define NAME_MAX 10

struct RankingData
{
    int no;
    char name[10];
    int score;
};

class Ranking : public AbstractScene
{
private:

    static RankingData Data[RANK_MAX];

    //ランキングの並べ替え
    static void SortRanking();

    //ランキングデータの保存
    static void SaveRanking();

public:
    //コンストラクタ
    Ranking();

    //デストラクタ
    ~Ranking();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    //ランキングデータの更新
    static void Insert(int score, char name[NAME_MAX]);

    //ランキングデータ読み込み
    static void ReadRanking();

    //ランキングの取得の取得
    static RankingData GetData(int n) 
    {
        return Data[n]; 
    }
};

