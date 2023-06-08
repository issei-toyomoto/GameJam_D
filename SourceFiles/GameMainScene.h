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

    int bgm_main; // メインBGM
    int se_select; // 画面遷移時SE
    int se_damage; // 花を刈ってしまった時のダメージSE

    int Anim = 0;   //ステージ切り替えアニメーション
    bool Clear = true;  //アニメーション中ならtrue

    bool Pause = false; //ポーズ中ならtrue

    Player player; //プレイヤー
    RunWeed** runweed;  //逃げる草
    UI ui;          //UI

    int Grass[MAP_HEIGHT][MAP_WIDTH];   //草・花の状態(0：何もない　1：草　2：花)
    int GrassTmp[MAP_HEIGHT][MAP_WIDTH];
    
    int ZeroCnt;    //草と花を取った数
    bool SaveFlower = true; //花を全部取れているならtrue
    int ItemCnt;

    int GrassSe;    //草を刈る効果音
    int FlowerSe;   //花を摘む効果音

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

class GameEffect {
private:
    static int x, y, score;
    static int minusFlg, category;
public:
    // スコア取得時のエフェクト関数
    void DrawScoreEffect(int posX, int posY, int drawScore, int minusFlg, int category) {
        SetFontSize(16);
        if (minusFlg == 1) {
            DrawFormatString(posX, posY + 20, GetColor(255, 255, 255), "-%d", drawScore);
        }
        else {
            DrawFormatString(posX, posY + 20, GetColor(255, 255, 255), "%d", drawScore);
        };
    };
};