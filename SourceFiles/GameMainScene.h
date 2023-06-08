#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "RunWeed.h"
#include "UI.h"
#include "common.h"


class GameMain : public AbstractScene {
private:
    int state;
    int score = 0;
    int Time[3];           //残り時間を記録する
    int StageNum = 1;

    int x;
    int y;

    int BackImg;    //背景画像
    int FlowerImg;  //花の画像
    int WeedImg;    //草の画像
    int AnimImg;    //ステージ切り替えアニメーション画像

    int Anim = 0;   //ステージ切り替えアニメーション
    bool Clear = true;  //アニメーション中ならtrue

    bool Pause = false; //ポーズ中ならtrue

    Player player; //プレイヤー
    RunWeed** runweed;  //逃げる草
    UI ui;          //UI

    int Grass[MAP_HEIGHT][MAP_WIDTH];   //草・花の状態(0：何もない　1：草　2：花)
    int GrassTmp[MAP_HEIGHT][MAP_WIDTH];
    
    int ZeroCnt;
    int ItemCnt;

    int GrassSe;    //草を刈る効果音

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;

    //ステージ初期化
    void SetStage(int level);

    int GetScore() { return score; }
    void SortGrass();
};